#include <Node.class.hpp>
#include "Fact.class.hpp"

Fact::Fact(e_tk token, std::string name, bool value)
	: _token(token), _name(name), _value(value) {

}

Fact::Fact(void)
	: _token(NB_TK) {

}

Fact::Fact(Fact const &src)
	: _token(src._token) {
	*this = src;
}

Fact::~Fact(void) {

}

Fact &Fact::operator=(Fact const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

std::string Fact::getName(void) const {
	return this->_name;
}

bool Fact::getValue(void) const {
	return this->_value;
}

void Fact::setValue(bool val) {
	this->_value = val;
}

e_tk Fact::getToken(void) const {
	return this->_token;
}

std::string Fact::toString(void) const {
	std::stringstream ss;
	ss << "Name: " << this->getName() << " | Value " << std::boolalpha << this->getValue();
	return ss.str();
}

std::ostream &operator<<(std::ostream &os, Fact *f) {
	os << "Name: " << f->getName() << " | Value " << std::boolalpha << f->getValue();
	return os;
}