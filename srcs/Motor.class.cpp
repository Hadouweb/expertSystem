#include <list>
#include "Motor.class.hpp"

Motor::Motor(std::list<ParsedNode *> parsedList)
	: _parsedList(parsedList) {

	this->_rDB = new RuleBase(this->_parsedList);

	this->_fDB = FactBase::getInstance();
	this->_fDB->initFact(parsedList);
	this->_fDB->printFactBase();
}

Motor::~Motor(void) { }

Motor::Motor(void) { }

Motor::Motor(Motor const &src) {
	*this = src;
}

Motor &Motor::operator=(Motor const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}
