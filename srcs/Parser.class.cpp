#include "Parser.class.hpp"

Parser::Parser(std::list<Node *> nodeList)
	: _nodeList(nodeList) {
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
	for (std::list<Node*>::iterator it = this->_nodeList.begin(); it != this->_nodeList.end(); ++it) {
		instrMapType::iterator it2 = this->_instrCheckerMap.find((*it)->getToken());
		if (it2 != this->_instrCheckerMap.end()) {
			this->_currentIt = it;
			(this->*it2->second)();
		}
	}
}

bool Parser::endLine(void) {
	std::list<Node*>::iterator & it = this->_currentIt;
	if (*it)
		;

	/*while (it != this->_nodeList.end() && (*it)->getToken() == TK_WHITE_SPACE)
		it++;
	if (it != this->_nodeList.end()) {
		if ((*it)->getToken() == TK_COMMENT)
			it++;
		if (it != this->_nodeList.end() && (*it)->getToken() == TK_END_LINE) {
			return true;
		}
		this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "end line expected");
	}*/
	return false;
}

void Parser::parseInstrPush(void) {
	std::list<Node*>::iterator & it = this->_currentIt;

	unsigned int col = (*it)->getNumCol();
	unsigned int line = (*it)->getNumLine();
	bool valid = false;

	it++;
	if (it != this->_nodeList.end()) {
		if ((*it)->getToken() == TK_WHITE_SPACE)
			it++;
		else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "space expected");
	} else
		this->pushError(col, line, "space expected");

	if (it != this->_nodeList.end()) {
		col = (*it)->getNumCol();
		line = (*it)->getNumLine();
		if (this->isValue(*it)) {
			valid = true;
		} else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "value type expected");
	} else
		this->pushError(col, line, "value type expected");

	if (valid) {
		this->_parsedNodeList.push_back(new ParsedNode(NB_TK, (*it)->getToken(), (*it)->getValue()));
		it++;
		this->endLine();
	} else
		this->pushError(col, line, "value type expected");
}

void Parser::parseInstrAssert(void) {
	std::list<Node*>::iterator & it = this->_currentIt;

	unsigned int col = (*it)->getNumCol();
	unsigned int line = (*it)->getNumLine();
	bool valid = false;

	it++;
	if (it != this->_nodeList.end()) {
		if ((*it)->getToken() == TK_WHITE_SPACE)
			it++;
		else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "space expected");
	} else
		this->pushError(col, line, "space expected");

	if (it != this->_nodeList.end()) {
		col = (*it)->getNumCol();
		line = (*it)->getNumLine();
		if (this->isValue(*it)) {
			valid = true;
		} else
			this->pushError((*it)->getNumCol(), (*it)->getNumLine(), "value type expected");
	} else
		this->pushError(col, line, "value type expected");

	if (valid) {
		this->_parsedNodeList.push_back(new ParsedNode(NB_TK, (*it)->getToken(), (*it)->getValue()));
		this->_currentIt++;
		this->endLine();
	} else
		this->pushError(col, line, "value type expected");
}

void Parser::parseInstrPop(void) {
	this->_parsedNodeList.push_back(new ParsedNode(NB_TK, NB_TK, ""));
	this->_currentIt++;
	this->endLine();
}

void Parser::parseInstrDump(void) {
	this->_parsedNodeList.push_back(new ParsedNode(NB_TK, NB_TK, ""));
	this->_currentIt++;
	this->endLine();
}

void Parser::parseInstrAdd(void) {
	this->_parsedNodeList.push_back(new ParsedNode(NB_TK, NB_TK, ""));
	this->_currentIt++;
	this->endLine();
}

void Parser::parseInstrSub(void) {
	this->_parsedNodeList.push_back(new ParsedNode(NB_TK, NB_TK, ""));
	this->_currentIt++;
	this->endLine();
}

void Parser::parseInstrMul(void) {
	this->_parsedNodeList.push_back(new ParsedNode(NB_TK, NB_TK, ""));
	this->_currentIt++;
	this->endLine();
}

void Parser::parseInstrDiv(void) {
	this->_parsedNodeList.push_back(new ParsedNode(NB_TK, NB_TK, ""));
	this->_currentIt++;
	this->endLine();
}

void Parser::parseInstrMod(void) {
	this->_parsedNodeList.push_back(new ParsedNode(NB_TK, NB_TK, ""));
	this->_currentIt++;
	this->endLine();
}

void Parser::parseInstrPrint(void) {
	this->_parsedNodeList.push_back(new ParsedNode(NB_TK, NB_TK, ""));
	this->_currentIt++;
	this->endLine();
}

void Parser::parseInstrExit(void) {
	this->_parsedNodeList.push_back(new ParsedNode(NB_TK, NB_TK, ""));
	this->_currentIt++;
	this->endLine();
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