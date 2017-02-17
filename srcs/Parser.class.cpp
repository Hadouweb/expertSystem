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
		} else {
			if ((*it)->getToken() == TK_END_LINE)
				this->_parsedNodeList.push_back(new ParsedNode((*it)->getToken(), (*it)->getValue()));
			it++;
		}
	}
}

bool Parser::authorizedOperator(e_tk token) {
	switch (token) {
		case TK_PLUS:
			return true;
		case TK_OR:
			return true;
		case TK_XOR:
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
	bool opMod = false;

	while (tmpIt != this->_nodeList.begin()) {
		tmpIt--;
		if (this->authorizedOperator((*tmpIt)->getToken()))
			opMod = true;
		if ((*tmpIt)->getToken() == TK_FACT) {
			if (opMod == true)
				opMod = false;
			else
				break;
		}
		if ((*tmpIt)->getToken() == TK_IMPLIE ||
			(*tmpIt)->getToken() == TK_IF_AND_ONLY_IF) {
			leftFact = true;
			break;
		}
		if ((*tmpIt)->getToken() == TK_END_LINE)
			break;
	}

	tmpIt = it;
	opMod = true;
	while (tmpIt != this->_nodeList.end()) {
		if (this->authorizedOperator((*tmpIt)->getToken()))
			opMod = true;
		if ((*tmpIt)->getToken() == TK_FACT) {
			if (opMod == true)
				opMod = false;
			else
				break;
		}
		if ((*tmpIt)->getToken() == TK_IMPLIE ||
			(*tmpIt)->getToken() == TK_IF_AND_ONLY_IF) {
			rightFact = true;
			break;
		}
		if ((*tmpIt)->getToken() == TK_END_LINE)
			break;
		tmpIt++;
	}

	this->skipSpace();
	if (it != this->_nodeList.end()) {
		if (leftFact || rightFact) {
			this->_parsedNodeList.push_back(new ParsedNode((*it)->getToken(), (*it)->getValue()));
		} else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from Fact");
	} else
		this->pushError(col, line, "Character expected from Fact");
	it++;
}

void Parser::tkInitFact(void) {
	std::list<Node*>::iterator & it = this->_currentIt;
	std::list<Node*>::iterator tmpItPrev = std::prev(it, 1);
	it++;
	if (it != this->_nodeList.end()) {
		if ((*tmpItPrev)->getToken() == TK_END_LINE) {
			if ((*it)->getToken() == TK_FACT) {
				while (it != this->_nodeList.end() && (*it)->getToken() == TK_FACT) {
					this->_parsedNodeList.push_back(new ParsedNode(TK_INIT_FACT, (*it)->getValue()));
					it++;
				}
			}
			else
				this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from InitFact");
		} else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from InitFact");
	} else
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Character expected from InitFact");
}

void Parser::tkQuery(void) {
	std::list<Node*>::iterator & it = this->_currentIt;
	std::list<Node*>::iterator tmpItPrev = std::prev(it, 1);
	it++;
	if (it != this->_nodeList.end()) {
		if ((*tmpItPrev)->getToken() == TK_END_LINE) {
			if ((*it)->getToken() == TK_FACT) {
				while (it != this->_nodeList.end() && (*it)->getToken() == TK_FACT) {
					this->_parsedNodeList.push_back(new ParsedNode(TK_QUERY, (*it)->getValue()));
					it++;
				}
			}
			else
				this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from Query");
		} else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from Query");
	} else
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Character expected from Query");
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
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from Implie");
	} else
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from Implie");
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
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from Plus");
	} else
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from Plus");
	it++;
}

void Parser::tkNot(void) {
	std::list<Node*>::iterator & it = this->_currentIt;
	std::list<Node*>::iterator tmpIt = std::next(it, 1);

	if (tmpIt != this->_nodeList.end()) {
		if ((*tmpIt)->getToken() == TK_FACT) {
			this->_parsedNodeList.push_back(new ParsedNode((*it)->getToken(), (*it)->getValue()));
		} else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from Not");
	} else
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Character expected from Not");
	it++;
}

void Parser::tkOr(void) {
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
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from Or");
	} else
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from Or");
	it++;
}

void Parser::tkXor(void) {
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
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from Xor");
	} else
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from Xor");
	it++;
}

void Parser::tkIfAndOnlyIf(void) {
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
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from IfAndOnlyIf");
	} else
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Unexpected token from IfAndOnlyIf");
	it++;
}

void Parser::tkParOpen(void) {
	std::list<Node*>::iterator & it = this->_currentIt;
	std::list<Node*>::iterator tmpIt = it;
	unsigned int count = 0;
	bool rightFact = false;
	bool rightParClose = false;

	while (tmpIt != this->_nodeList.end()) {
		if ((*tmpIt)->getToken() == TK_FACT) {
			rightFact = true;
		}
		if ((*tmpIt)->getToken() == TK_PAR_OPEN)
			count++;
		if ((*tmpIt)->getToken() == TK_PAR_CLOSE) {
			count--;
			if (count == 0)
				rightParClose = true;
		}
		if ((*tmpIt)->getToken() == TK_END_LINE ||
			(*tmpIt)->getToken() == TK_IMPLIE ||
			(*tmpIt)->getToken() == TK_IF_AND_ONLY_IF)
			break;
		tmpIt++;
	}

	if (rightFact && rightParClose) {
		this->_parsedNodeList.push_back(new ParsedNode((*it)->getToken(), (*it)->getValue()));
	} else
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Character expected from ParOpen");
	it++;
}

void Parser::tkParClose(void) {
	std::list<Node*>::iterator & it = this->_currentIt;
	std::list<Node*>::iterator tmpIt = it;
	unsigned int count = 1;
	bool rightFact = false;
	bool rightParOpen = false;

	while (tmpIt != this->_nodeList.begin()) {
		tmpIt--;
		if ((*tmpIt)->getToken() == TK_FACT) {
			rightFact = true;
		}
		if ((*tmpIt)->getToken() == TK_PAR_CLOSE)
			count++;
		if ((*tmpIt)->getToken() == TK_PAR_OPEN) {
			count--;
			if (count == 0)
				rightParOpen = true;
		}
		if ((*tmpIt)->getToken() == TK_END_LINE ||
			(*tmpIt)->getToken() == TK_IMPLIE ||
			(*tmpIt)->getToken() == TK_IF_AND_ONLY_IF)
			break;
	}

	if (rightFact && rightParOpen) {
		this->_parsedNodeList.push_back(new ParsedNode((*it)->getToken(), (*it)->getValue()));
	} else
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "Character expected from ParClose");
	it++;
}

void Parser::reduceList(void) {
	e_tk prevToken = NB_TK;
	std::list<ParsedNode *>::iterator prevIt;

	for (std::list<ParsedNode *>::iterator it = this->_parsedNodeList.begin(); it != this->_parsedNodeList.end(); ++it) {
		if ((*it)->getToken() == prevToken) {
			(*prevIt)->addValue((*it)->getValue());
			this->_parsedNodeList.erase(it);
		} else
			prevIt = it;
		prevToken = (*it)->getToken();
	}
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