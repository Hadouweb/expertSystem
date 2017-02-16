#include <RuleBase.class.hpp>
#include "Parser.class.hpp"

Parser::Parser(std::list<Node *> nodeList)
	: _nodeList(nodeList) {
	this->_currentIt = this->_nodeList.begin();
	this->makeParsing();
}

Parser::Parser(Parser const &src) {
	*this = src;
}

Parser::~Parser(void) {
	for (std::list<ParsedNode*>::iterator it = this->_parsedNodeList.begin(); it != this->_parsedNodeList.end(); ++it) {
		delete *it;
	}
	this->_parsedNodeList.clear();
}

Parser &Parser::operator=(Parser const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

Error::Error(unsigned int col, unsigned int line, std::string type)
	: col(col), line(line), type(type) {

}

void Parser::makeParsing(void) {
	std::list<Node*>::iterator & it = this->_currentIt;
	while (it != this->_nodeList.end()) {
		instrMapType::iterator it2 = this->_instrCheckerMap.find((*it)->getToken());
		if (it2 != this->_instrCheckerMap.end()) {
			this->_currentIt = it;
			(this->*it2->second)();
		} else
			it++;
	}
}

bool Parser::endLine(void) {
	std::list<Node*>::iterator & it = this->_currentIt;
	if (*it)
		;

	while (it != this->_nodeList.end() && (*it)->getToken() == TK_WHITE_SPACE)
		it++;
	if (it != this->_nodeList.end()) {
		if ((*it)->getToken() == TK_COMMENT)
			it++;
		if (it != this->_nodeList.end() && (*it)->getToken() == TK_END_LINE) {
			return true;
		}
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "end line expected");
	}
	return false;
}

bool Parser::authorizedOperator(e_tk token) {
	switch (token) {
		case TK_IMPLIE:
			return true;
		case TK_PLUS:
			return true;
		case TK_NOT:
			return true;
		case TK_OR:
			return true;
		case TK_XOR:
			return true;
		case TK_IF_AND_ONLY_IF:
			return true;
		case TK_PAR_OPEN:
			return true;
		case TK_PAR_CLOSE:
			return true;
		default:
			return false;
	}
}

void Parser::skipSpace(void) {
	std::list<Node*>::iterator & it = this->_currentIt;
	while (it != this->_nodeList.end() && (*it)->getToken() == TK_WHITE_SPACE)
		it++;
}

void Parser::tkFact(void) {
	std::list<Node*>::iterator & it = this->_currentIt;
	std::list<Node*>::iterator tmpIt = it;
	unsigned int col = (*it)->getNumCol();
	unsigned int line = (*it)->getNumLine();
	bool leftFact = false;
	bool rightFact = false;


	while (tmpIt != this->_nodeList.begin()) {
		tmpIt--;
		if ((*tmpIt)->getToken() == TK_IMPLIE ||
			(*tmpIt)->getToken() == TK_IF_AND_ONLY_IF) {
			leftFact = true;
			break;
		}
		//if ((*tmpIt)->getToken() == TK_END_LINE)
		//	break;
	}

	tmpIt = it;
	while (tmpIt != this->_nodeList.end()) {
		if ((*tmpIt)->getToken() == TK_IMPLIE ||
			(*tmpIt)->getToken() == TK_IF_AND_ONLY_IF) {
			rightFact = true;
			break;
		}
		//if ((*tmpIt)->getToken() == TK_END_LINE)
		//	break;
		tmpIt++;
	}

	this->skipSpace();
	if (it != this->_nodeList.end()) {
		if (leftFact || rightFact) {
			this->_parsedNodeList.push_back(new ParsedNode((*it)->getToken(), (*it)->getValue()));
			it++;
		} else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token");
	} else
		this->pushError(col, line, "Character expected");
}

void Parser::tkInitFact(void) {
	std::list<Node*>::iterator & it = this->_currentIt;
	std::list<Node*>::iterator tmpItPrev = std::prev(it, 1);
	it++;
	if (it != this->_nodeList.end()) {
		if ((*tmpItPrev)->getToken() == TK_END_LINE) {
			if ((*it)->getToken() == TK_FACT) {
				this->_parsedNodeList.push_back(new ParsedNode(TK_INIT_FACT, (*it)->getValue()));
				it++;
			}
			else
				this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token");
		} else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token");
	} else
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Character expected");
}

void Parser::tkQuery(void) {
	std::list<Node*>::iterator & it = this->_currentIt;
	std::list<Node*>::iterator tmpItPrev = std::prev(it, 1);
	it++;
	if (it != this->_nodeList.end()) {
		if ((*tmpItPrev)->getToken() == TK_END_LINE) {
			if ((*it)->getToken() == TK_FACT) {
				this->_parsedNodeList.push_back(new ParsedNode(TK_QUERY, (*it)->getValue()));
				it++;
			}
			else
				this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token");
		} else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token");
	} else
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Character expected");
}

void Parser::tkImplie(void) {
	std::list<Node*>::iterator & it = this->_currentIt;
	std::list<Node*>::iterator tmpIt = it;
	bool leftFact = false;
	bool rightFact = false;

	while (tmpIt != this->_nodeList.begin()) {
		tmpIt--;
		if ((*tmpIt)->getToken() == TK_FACT) {
			leftFact = true;
			break;
		} else if ((*tmpIt)->getToken() != TK_WHITE_SPACE &&
				   (*tmpIt)->getToken() != TK_PAR_CLOSE)
			break;
	}

	if (leftFact) {
		tmpIt = it;
		while (tmpIt != this->_nodeList.end()) {
			tmpIt++;
			if ((*tmpIt)->getToken() == TK_FACT) {
				rightFact = true;
				break;
			} else if ((*tmpIt)->getToken() != TK_WHITE_SPACE &&
						(*tmpIt)->getToken() != TK_NOT &&
						(*tmpIt)->getToken() != TK_PAR_OPEN)
				break;
		}
		if (rightFact) {
			this->_parsedNodeList.push_back(new ParsedNode((*it)->getToken(), (*it)->getValue()));
		} else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token");
	} else
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token");
	it++;
}

void Parser::tkPlus(void) {
	std::list<Node*>::iterator & it = this->_currentIt;
	std::list<Node*>::iterator tmpIt = it;
	bool leftFact = false;
	bool rightFact = false;

	while (tmpIt != this->_nodeList.begin()) {
		tmpIt--;
		if ((*tmpIt)->getToken() == TK_FACT) {
			leftFact = true;
			break;
		} else if ((*tmpIt)->getToken() != TK_WHITE_SPACE &&
				   (*tmpIt)->getToken() != TK_PAR_CLOSE)
			break;
	}

	if (leftFact) {
		tmpIt = it;
		while (tmpIt != this->_nodeList.end()) {
			tmpIt++;
			if ((*tmpIt)->getToken() == TK_FACT) {
				rightFact = true;
				break;
			} else if ((*tmpIt)->getToken() != TK_WHITE_SPACE &&
					   (*tmpIt)->getToken() != TK_NOT &&
					   (*tmpIt)->getToken() != TK_PAR_OPEN)
				break;
		}
		if (rightFact) {
			this->_parsedNodeList.push_back(new ParsedNode((*it)->getToken(), (*it)->getValue()));
		} else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token");
	} else
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token");
	it++;
}

void Parser::tkNot(void) {
	std::list<Node*>::iterator & it = this->_currentIt;
	std::list<Node*>::iterator tmpIt = std::next(it, 1);

	if (tmpIt != this->_nodeList.end()) {
		if ((*tmpIt)->getToken() == TK_FACT) {
			this->_parsedNodeList.push_back(new ParsedNode((*it)->getToken(), (*it)->getValue()));
		} else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token");
	} else
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Character expected");
	it++;
}

void Parser::tkOr(void) {

}

void Parser::tkXor(void) {

}

void Parser::tkIfAndOnlyIf(void) {

}

void Parser::tkParOpen(void) {

}

void Parser::tkParClose(void) {

}

std::list<Error*> Parser::getErrorList(void) const {
	return this->_errorList;
}

std::list<ParsedNode *> Parser::getParsedNodeList(void) const {
	return this->_parsedNodeList;
}

void Parser::printError(void) {
	for (std::list<Error *>::iterator it = this->_errorList.begin(); it != this->_errorList.end(); ++it) {
		Parser::SynthaxException e;
		std::cerr << e.what() << ", " << (*it)->type << " col : " << (*it)->col << " line : " << (*it)->line << std::endl;
	}
	for (std::list<Error *>::iterator it = this->_errorList.begin(); it != this->_errorList.end(); ++it) {
		delete *it;
	}
	this->_errorList.clear();
}

void Parser::pushError(unsigned int col, unsigned int line, std::string type) {
	this->_errorList.push_back(new Error(col, line, type));
}

bool Parser::isValue(Node *n) {
	return (n->getToken() == NB_TK ||
			n->getToken() == NB_TK ||
			n->getToken() == NB_TK ||
			n->getToken() == NB_TK ||
			n->getToken() == NB_TK);
}

Parser::SynthaxException::SynthaxException(void) { }

Parser::SynthaxException::SynthaxException(const Parser::SynthaxException &src) {
	*this = src;
}

Parser::SynthaxException::~SynthaxException(void) throw() { }

Parser::SynthaxException & Parser::SynthaxException::operator=(const Parser::SynthaxException &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

const char *Parser::SynthaxException::what() const throw() {
	return "Exception: Synthax Error";
}