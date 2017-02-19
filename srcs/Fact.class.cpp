#include <Node.class.hpp>
#include "Fact.class.hpp"

Fact::Fact(e_tk token, std::string name, uint8_t value)
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

uint8_t Fact::getValue(void) const {
	return this->_value;
}

void Fact::setValue(uint8_t val) {
	this->_value = val;
}

e_tk Fact::getToken(void) const {
	return this->_token;
}

std::string Fact::toString(void) const {
	std::stringstream ss;
	ss << "Name: " << this->getName() << " | Value " << static_cast<int>(this->getValue());
	return ss.str();
}

void Fact::addChild(IObject *c) {
	c->setParent(this);
	this->_childList.push_back(c);
}

std::list<IObject *> Fact::getChild(void) const {
	return this->_childList;
}

void Fact::setParent(IObject *p) {
	this->_parent = p;
}

IObject *Fact::getParent(void) const {
	return this->_parent;
}

std::ostream &operator<<(std::ostream &os, Fact *f) {
	os << "Name: " << f->getName() << " | Value " << static_cast<int>(f->getValue());
	return os;
}