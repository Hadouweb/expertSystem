#include <ParsedNode.class.hpp>

ParsedNode::ParsedNode(e_tk pTkInstr, std::string val)
	: _tk(pTkInstr), _value(val) {

}

ParsedNode::ParsedNode(void)
	: _tk(NB_TK),  _value("") {

}

ParsedNode::ParsedNode(const ParsedNode &src)
	: _tk(src._tk), _value(src._value) {
	*this = src;
}

ParsedNode::~ParsedNode(void) { }

ParsedNode &ParsedNode::operator=(const ParsedNode &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

e_tk ParsedNode::getToken(void) const {
	return this->_tk;
}

std::string ParsedNode::getValue(void) const {
	return this->_value;
}

std::ostream &operator<<(std::ostream &os, ParsedNode &pN) {
	os << Node::convertEnumTk(pN.getToken()) << " value: |";
	os << pN.getValue() << "|" << std::endl;
	return os;
}
