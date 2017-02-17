#include "Motor.class.hpp"

Motor::Motor(std::list<ParsedNode *> parsedList)
	: _parsedList(parsedList) {

	this->_rDB = RuleBase::getInstance();
	this->_rDB->initRule(this->_parsedList);
	this->_rDB->printAllRule();

	this->_fDB = FactBase::getInstance();
	this->_fDB->initFact(parsedList);
	this->_fDB->printFactBase();

	this->initQueryFact();
	this->printQueryFact();

	std::cout << "*********************************************" << std::endl;
	this->searchQuery();
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

void Motor::initQueryFact(void) {
	for (std::list<ParsedNode *>::iterator it = this->_parsedList.begin();
		it != this->_parsedList.end(); ++it) {
		if ((*it)->getToken() == TK_QUERY) {
			std::string val = (*it)->getValue();
			for (std::string::iterator itFact = val.begin(); itFact != val.end(); ++itFact) {
				std::string s(1, *itFact);
				Fact *f = FactBase::getInstance()->getFactByName(s);
				this->_queryFactList.push_back(f);
			}
		}
	}
}

void Motor::printQueryFact(void) {
	std::cout << std::endl;
	std::cout << "Query:" << std::endl;
	for (std::list<Fact*>::iterator it = this->_queryFactList.begin();
		it != this->_queryFactList.end(); ++it) {
		std::cout << "\t" << *it << std::endl;
	}
}

void Motor::searchQuery(void) {
	for (std::list<Fact*>::iterator it = this->_queryFactList.begin();
		 it != this->_queryFactList.end(); ++it) {
		this->makeGraph(*it);
	}
}

void Motor::makeGraph(Fact * q) {
	std::cout << "*********************************************" << std::endl;
	std::cout << "Make Graph for query: (" << q << ")" << std::endl;
	Rule * r = this->_rDB->getRuleByConclusion(q);
	std::cout << r << std::endl;

	std::list<IObject*> premise = r->getPremiseList();
	for (std::list<IObject*>::iterator it = premise.begin(); it != premise.end(); it++) {
		Rule * r = this->_rDB->getRuleByConclusion(static_cast<Fact*>(*it));
		std::cout << r << std::endl;
	}
}