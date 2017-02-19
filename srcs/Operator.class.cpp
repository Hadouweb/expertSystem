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

std::string Operator::toString(void) const {
	std::string indexStrDebug = std::to_string(this->indexDebug);
	switch (this->_token) {
		case TK_PLUS:
			return "+" + indexStrDebug;
		case TK_OR:
			return "|" + indexStrDebug;
		case TK_XOR:
			return "^" + indexStrDebug;
		case TK_NOT:
			return "!" + indexStrDebug;
		case TK_IMPLIE:
			return "=>" + indexStrDebug;
		case TK_IF_AND_ONLY_IF:
			return "<=>" + indexStrDebug;
		default:
			return "???";
	}
}

std::string Operator::getName(void) const {
	return this->toString();
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
