#include "Operand.class.hpp"

Operand::Operand(e_tk token)
	: _token(token) {

}

Operand::Operand(void)
	: _token(NB_TK) {

}

Operand::~Operand(void) {

}

Operand::Operand(Operand const &src)
	: _token(src._token) {
	*this = src;
}

Operand &Operand::operator=(Operand const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

e_tk Operand::getToken(void) const {
	return this->_token;
}

std::string Operand::toString(void) const {
	switch (this->_token) {
		case TK_PLUS:
			return "+";
		case TK_OR:
			return "|";
		case TK_XOR:
			return "^";
		case TK_NOT:
			return "!";
		case TK_IMPLIE:
			return "=>";
		case TK_IF_AND_ONLY_IF:
			return "<=>";
		default:
			return "???";
	}
}

std::string Operand::getName(void) const {
	return this->toString();
}
