#include "Lexer.class.hpp"

Lexer::Lexer(void)
	: _status(NB_TK, { STS_HUNGRY, STS_REJECT } ), _chunk(NB_TK) {
	this->forEachLine(std::cin);
}

Lexer::Lexer(std::string fileName)
	: _status(NB_TK, { STS_HUNGRY, STS_REJECT } ), _chunk(NB_TK) {
	std::ifstream ifs(fileName);
	if (!ifs.good()) {
		std::cerr << "File not found" << std::endl;
		exit(1);
	}
	this->forEachLine(ifs);
}

Lexer::Lexer(const Lexer &src) {
	*this = src;
}

Lexer::~Lexer(void) {
	for (std::list<Node*>::iterator it = this->_nodeList.begin(); it != this->_nodeList.end(); ++it) {
		delete *it;
	}
	this->_nodeList.clear();
}

Lexer &Lexer::operator=(const Lexer &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

std::list<Node*> Lexer::getNodeList(void) const {
	return this->_nodeList;
}


std::list<Node *> Lexer::getErrorList(void) const {
	return this->_errorList;
}

#define TOKEN_DEFINE_1(funcName, str) \
e_sts Lexer::funcName(const char c, const uint8_t index) { \
	unsigned int s = this->_chunk[index].length(); \
	switch(s) { \
		case 0: return c == str[0] ? (this->_chunk[index] = c, STS_ACCEPT) : ( STS_REJECT); \
		case 1: return  STS_REJECT; \
		default: abort(); \
	} \
}

#define TOKEN_DEFINE_2(funcName, str) \
e_sts Lexer::funcName(const char c, const uint8_t index) { \
	unsigned int s = this->_chunk[index].length(); \
	switch(s) { \
		case 0: return c == str[0] ? (this->_chunk[index] = c, STS_HUNGRY) : ( STS_REJECT); \
		case 1: return c == str[1] ? (this->_chunk[index] += c, STS_ACCEPT) : ( STS_REJECT); \
		case 2: return  STS_REJECT; \
		default: abort(); \
	} \
}

#define TOKEN_DEFINE_3(funcName, str) \
e_sts Lexer::funcName(const char c, const uint8_t index) { \
	unsigned int s = this->_chunk[index].length(); \
	switch(s) { \
		case 0: return c == str[0] ? (this->_chunk[index] = c, STS_HUNGRY) : (STS_REJECT); \
		case 1: return c == str[1] ? (this->_chunk[index] += c, STS_HUNGRY) : (STS_REJECT); \
		case 2: return c == str[2] ? (this->_chunk[index] += c, STS_ACCEPT) : (STS_REJECT); \
		case 3: return STS_REJECT; \
		default: abort(); \
	} \
}

TOKEN_DEFINE_1(tkInitFact, "=");
TOKEN_DEFINE_1(tkQuery, "?");
TOKEN_DEFINE_2(tkImplie, "=>");
TOKEN_DEFINE_1(tkPlus, "+");
TOKEN_DEFINE_1(tkNot, "!");
TOKEN_DEFINE_1(tkOr, "|");
TOKEN_DEFINE_1(tkXor, "^");
TOKEN_DEFINE_1(tkParOpen, "(");
TOKEN_DEFINE_1(tkParClose, ")");
TOKEN_DEFINE_1(tkComment, "#");
TOKEN_DEFINE_1(tkEndLine, "\n");

e_sts Lexer::tkFact(const char c, const uint8_t index) {
	if (this->_chunk[index].length() == 0 && c >= 'A' && c <= 'Z') {
		this->_chunk[index] = c;
		return STS_ACCEPT;
	}
	return STS_REJECT;
}

e_sts Lexer::tkWhiteSpace(const char c, const uint8_t index) {
	if (c == '\t' || c == ' ') {
		this->_chunk[index] += c;
		return STS_ACCEPT;
	}
	return STS_REJECT;
}

void Lexer::updateStatus(void) {
	for (int i = 0; i < NB_TK; i++) {
		this->_status[i].prev = this->_status[i].curr;
	}
}

bool Lexer::matchToken(const char c) {
	uint8_t i = 0;
	bool find = false;
	//std::cout << "HERE10" << std::endl;
	for (tkVectorType::iterator it = this->_tk.begin(); it != this->_tk.end(); ++it) {
		if (this->_status[i].prev != STS_REJECT)
			this->_status[i].curr = (this->**it)(c, i);
		if (this->_status[i].curr != STS_REJECT) {
			find = true;
		}
		i++;
	}
	//std::cout << "HERE11" << std::endl;
	//std::cout << "[" << c << "]" << std::endl;
	//this->printStatus();
	return find;
}

e_tk Lexer::getTokenFound(void) {
	e_tk tk = NB_TK;
	for (int i = 0; i < NB_TK; i++) {
		if (this->_status[i].prev == STS_ACCEPT) {
			tk = static_cast<e_tk>(i);
		} else
			this->_chunk[i].clear();
		this->_status[i].prev = STS_HUNGRY;
		this->_status[i].curr = STS_REJECT;
	}
	return tk;
}

enum e_tk Lexer::pushToken(unsigned int line, unsigned int col) {
	e_tk token = getTokenFound();
	int index = static_cast<int>(token);
	if (token != NB_TK && token != TK_COMMENT)
		this->_nodeList.push_back(new Node(token, this->_chunk[index], line, col));
	return token;
}

void Lexer::pushError(unsigned int line, unsigned int col) {
	e_tk token = getTokenFound();
	this->_errorList.push_back(new Node(token, "", line, col));
}

void Lexer::forEachLine(std::istream & is) {
	std::string line;
	unsigned int numLine = 0;

	while (getline(is, line)) {
		this->_nodeList.push_back(new Node(TK_END_LINE, "", numLine, line.length()));
		if (this->forEachChar(line, numLine) == true)
			break ;
		numLine++;
	}
}

e_tk Lexer::findCaracter(char c, unsigned int numCol, unsigned int numLine, bool reCheck) {
	//std::cout << "|" << c << "| " << std::endl;
	//this->printStatus();
	//std::cout << std::endl;
	if (matchToken(c)) {
		this->updateStatus();
	} else {
		e_tk token = this->pushToken(numLine, numCol);
		if (token == TK_COMMENT)
			return TK_COMMENT;
		if (token == NB_TK) {
			if (reCheck == false)
				this->findCaracter(c, numCol, numLine, true); 	// Last check token exemple <=>B
			else
				this->pushError(numLine, numCol);
		} else
			this->findCaracter(c, numCol, numLine, false); 		// Check current token after match previous exemple A<=>

		return token;
	}
	return NB_TK;
}

bool Lexer::forEachChar(std::string & line, unsigned int numLine) {
	unsigned int tmpCol = 0;
	unsigned int numCol = 0;
	std::string::iterator it = line.begin();

	while (it != line.end()) {
		e_tk token = findCaracter(*it, numCol, numLine, false);
		if (token != NB_TK)
			numCol = tmpCol;
		if (token == TK_COMMENT)
			return false;
		it++;
		tmpCol++;
	}
	this->pushToken(numLine, numCol);
	return false;
}

Lexer::UnknownTokenException::UnknownTokenException(void) { }

Lexer::UnknownTokenException::UnknownTokenException(const Lexer::UnknownTokenException &src) {
	*this = src;
}

Lexer::UnknownTokenException::~UnknownTokenException(void) throw() { }

Lexer::UnknownTokenException & Lexer::UnknownTokenException::operator=(const Lexer::UnknownTokenException &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

const char *Lexer::UnknownTokenException::what() const throw() {
	return "Unknown Token Exception";
}

void Lexer::printError(void) {
	for (std::list<Node *>::iterator it = this->_errorList.begin(); it != this->_errorList.end(); ++it) {
		Lexer::UnknownTokenException e;
		e.what();
		std::cerr << e.what() << ", col: " << (*it)->getNumCol() << " line: " << (*it)->getNumLine() << std::endl;
		delete *it;
	}
	this->_errorList.clear();
}


std::string Lexer::convertStsEnum(enum e_sts sts) {
	switch(sts) {
		case STS_ACCEPT:
			return "STS_ACCEPT";
		case STS_REJECT:
			return "STS_REJECT";
		case STS_HUNGRY:
			return "STS_HUNGRY";
	}
}

void Lexer::printStatus(void) {
	for(int i = 0; i < NB_TK; i++) {
		e_tk tk = static_cast<e_tk>(i);
		std::cout << std::setw(25) <<Node::convertEnumTk(tk) << " |";
		std::cout << this->_chunk[i] << "| ";
		std::cout << this->_status[i];
	}
}

std::ostream &operator<<(std::ostream &os, Status &s) {
	os << "prev: " << Lexer::convertStsEnum(s.prev);
	os << " | curr: " << Lexer::convertStsEnum(s.curr) << std::endl;
	return os;
}
