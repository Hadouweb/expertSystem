#include "Node.class.hpp"

Node::Node(void) { }

Node::Node(e_tk tk, std::string val, unsigned int numLine, unsigned int numCol)
	: _token(tk), _value(val), _numLine(numLine), _numCol(numCol) {

}

Node::Node(Node const &src) {
	*this = src;
}

Node::~Node(void) { }

Node &Node::operator=(Node const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

std::string Node::convertEnumTk(e_tk e) {
	switch (e) {
		case TK_FACT:
			return "TK_FACT";
		case TK_INIT_FACT:
			return "TK_INIT_FACT";
		case TK_QUERY:
			return "TK_QUERY";
		case TK_IMPLIE:
			return "TK_IMPLIE";
		case TK_PLUS:
			return "TK_PLUS";
		case TK_NOT:
			return "TK_NOT";
		case TK_OR:
			return "TK_OR";
		case TK_XOR:
			return "TK_XOR";
		case TK_PAR_OPEN:
			return "TK_PAR_OPEN";
		case TK_PAR_CLOSE:
			return "TK_PAR_CLOSE";
		case TK_COMMENT:
			return "TK_COMMENT";
		case TK_END_LINE:
			return "TK_END_LINE";
		case TK_WHITE_SPACE:
			return "TK_WHITE_SPACE";
		case NB_TK:
			return "NB_TK";
	}
	return "NULL";
}

e_tk Node::getToken(void) const {
	return this->_token;
}

unsigned int Node::getNumLine() const {
	return this->_numLine;
}

unsigned int Node::getNumCol() const {
	return this->_numCol;
}

std::string Node::getValue() const {
	return this->_value;
}

std::ostream &operator<<(std::ostream &os, Node &n) {
	os << Node::convertEnumTk(n.getToken()) << " |" << n.getValue() << "| col : " << n.getNumCol() << " line : " << n.getNumLine();
	return os;
}
