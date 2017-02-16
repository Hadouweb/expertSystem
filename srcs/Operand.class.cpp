#include <Node.class.hpp>
#include "Operand.class.hpp"

Operand::Operand(e_tk token)
	: _token(token) {

}

Operand::Operand(void) {

}

Operand::~Operand(void) {

}

Operand::Operand(Operand const &src) {
	*this = src;
}

Operand &Operand::operator=(Operand const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

e_tk Operand::getToken(void) const {
	return this->getToken();
}
