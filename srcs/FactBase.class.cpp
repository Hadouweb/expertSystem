#include "FactBase.class.hpp"

FactBase::FactBase(void) {

}

FactBase::FactBase(FactBase const &src) {
	*this = src;
}

FactBase::~FactBase(void) {

}

FactBase &FactBase::operator=(FactBase const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

FactBase *FactBase::getInstance(void) {
	if (_singleton == NULL)
		_singleton = new FactBase();
	return _singleton;
}

void FactBase::initFact(std::list<ParsedNode *> parsedList) {
	for (std::list<ParsedNode *>::iterator it = parsedList.begin(); it != parsedList.end(); ++it) {
		if ((*it)->getToken() == TK_INIT_FACT) {
			std::string val = (*it)->getValue();
			for (std::string::iterator itFact = val.begin(); itFact != val.end(); ++itFact) {
				std::string s(1, *itFact);
				this->addFact(s, true);
			}
		}
	}
}

Fact *FactBase::addFact(std::string name, bool value) {
	std::map<std::string, Fact*>::iterator it = this->_factMap.find(name);
	Fact * f;
	if (it == this->_factMap.end()) {
		f = new Fact(TK_FACT, name, value);
		this->_factMap.insert(std::pair<std::string, Fact*>(name, f));
	} else {
		f = (*it).second;
		f->setValue(value);
	}
	return f;
}

Fact *FactBase::getFactByName(std::string name) {
	std::map<std::string, Fact*>::iterator it = this->_factMap.find(name);
	Fact * f;
	if (it == this->_factMap.end()) {
		f = new Fact(TK_FACT, name, false);
		this->_factMap.insert(std::pair<std::string, Fact*>(name, f));
	} else {
		f = (*it).second;
	}
	return f;
}

void FactBase::printFactBase(void) const {
	std::cout << "FactBase:" << std::endl;
	for (std::map<std::string, Fact*>::const_iterator it = this->_factMap.begin(); it != this->_factMap.end(); ++it) {
		std::cout << "\t" << (*it).second << std::endl;
	}
}

FactBase * FactBase::_singleton = NULL;