#include <ParsedNode.class.hpp>

ParsedNode::ParsedNode(e_tk pTkInstr, e_tk pTkValue, std::string val)
	: _tkInstr(pTkInstr), _tkValue(pTkValue), _value(val) {

}

ParsedNode::ParsedNode(void)
	: _tkInstr(NB_TK), _tkValue(NB_TK), _value("") {

}

ParsedNode::ParsedNode(const ParsedNode &src)
	: _tkInstr(src._tkInstr), _tkValue(src._tkValue), _value(src._value) {
	*this = src;
}

ParsedNode::~ParsedNode(void) { }

ParsedNode &ParsedNode::operator=(const ParsedNode &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

e_tk ParsedNode::getTkInstr(void) const {
	return this->_tkInstr;
}

e_tk ParsedNode::getTkValue(void) const {
	return this->_tkValue;
}

std::string ParsedNode::getValue(void) const {
	return this->_value;
}

std::ostream &operator<<(std::ostream &os, ParsedNode &pN) {
	os << Node::convertEnumTk(pN.getTkInstr()) << std::endl;
	if (pN.getTkValue() != NB_TK) {
		os << "\t" << Node::convertEnumTk(pN.getTkValue()) << std::endl;
		os << "\t" << pN.getValue() << std::endl;
	}
	return os;
}
