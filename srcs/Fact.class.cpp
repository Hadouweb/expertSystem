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

std::string Fact::toString(bool withParent, bool withChild) const {
	std::stringstream ss;
	if (withParent && this->getParent())
		ss << "\t" << "Parent: " << this->getParent()->toString(false, false) << std::endl;
	ss << "Name: " << this->getName() << " Value " << static_cast<int>(this->getValue());
	ss << " isFactBase: " << this->getIsFactBase() << std::endl;
	if (withChild) {
		std::list<IObject*> child = this->getChild();
		for (std::list<IObject *>::const_iterator itC = child.begin();
			itC != child.end(); ++itC) {
			ss << "\t" << "Child: " << (*itC)->toString(false, false) << std::endl;
		}
	}

	return ss.str();
}

void Fact::addChild(IObject *c) {
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

void Fact::setVisited(bool val) {
	this->_visited = val;
}

bool Fact::getVisited(void) const {
	return this->_visited;
}

bool Fact::getIsFactBase() const {
	return this->_isFactBase;
}

void Fact::setIsFactBase(bool isFactBase) {
	this->_isFactBase = isFactBase;
}

std::ostream &operator<<(std::ostream &os, Fact *f) {
	os << "Name: " << f->getName() << " | Value " << static_cast<int>(f->getValue());
	return os;
}