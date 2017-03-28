#include "Operator.class.hpp"

Operator::Operator(e_tk token)
	: _token(token) {

}

Operator::Operator(void)
	: _token(NB_TK) {

}

Operator::~Operator(void) {

}

Operator::Operator(Operator const &src)
	: _token(src._token) {
	*this = src;
}

Operator &Operator::operator=(Operator const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

e_tk Operator::getToken(void) const {
	return this->_token;
}

uint8_t Operator::getValue(void) const {
	return this->_value;
}

void Operator::setValue(uint8_t val) {
	this->_value = val;
}

std::string Operator::toString(bool withParent, bool withChild) const {
	std::stringstream ss;

	std::string indexStrDebug = std::to_string(this->indexDebug);
	if (withParent && this->getParent())
		ss << "\tParent: " << this->getParent()->toString(false, false) << std::endl;
	switch (this->_token) {
		case TK_PLUS:
			ss << "Name: " << "[+]" << indexStrDebug;
			break;
		case TK_OR:
			ss << "Name: " << "[|]" << indexStrDebug;
			break;
		case TK_XOR:
			ss << "Name: " << "[^]" << indexStrDebug;
			break;
		case TK_NOT:
			ss << "Name: " << "[!]" << indexStrDebug;
			break;
		case TK_IMPLIE:
			ss << "Name: " << "[=>]" << indexStrDebug;
			break;
		default:
			ss << "Name: " << "???" << std::endl;
	}
	ss << " Value " << static_cast<int>(this->getValue());
	if (withChild) {
		ss << std::endl;
		std::list<IObject*> child = this->getChild();
		for (std::list<IObject *>::const_iterator itC = child.begin();
			itC != child.end(); ++itC) {
			ss << "\tChild: " << (*itC)->toString(false, false) << std::endl;
		}
	}

	return ss.str();
}

std::string Operator::getName(void) const {
	return this->toString(false, false);
}

void Operator::addChild(IObject *c) {
	this->_childList.push_back(c);
}

std::list<IObject *> Operator::getChild(void) const {
	return this->_childList;
}

bool Operator::isOperator(e_tk token) {
	switch(token) {
		case TK_PLUS:
			return true;
		case TK_OR:
			return true;
		case TK_XOR:
			return true;
		case TK_NOT:
			return true;
		default:
			return false;
	}
}

void Operator::setParent(IObject *p) {
	this->_parent = p;
}

IObject *Operator::getParent(void) const {
	return this->_parent;
}

void Operator::setVisited(bool val) {
	this->_visited = val;
}

bool Operator::getVisited(void) const {
	return this->_visited;
}
