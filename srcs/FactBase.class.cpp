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
	bool findInitFact = false;
	for (std::list<ParsedNode *>::iterator it = parsedList.begin(); it != parsedList.end(); ++it) {
		if ((*it)->getToken() == TK_INIT_FACT) {
			findInitFact = true;
			std::string val = (*it)->getValue();
			for (std::string::iterator itFact = val.begin(); itFact != val.end(); ++itFact) {
				std::string s(1, *itFact);
				if (s.compare("=") == 0)
					continue ;
				this->addFact(s, 1);
			}
		}
	}

	if (!findInitFact) {
		Error * e = new Error(0, 0, "Token = is expected at the end");
		e->pos = false;
		Parser::pushError(e);
	}
}

Fact *FactBase::addFact(std::string name, uint8_t value) {
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

std::map<std::string, Fact *> FactBase::getAllFact(void) const {
	return this->_factMap;
}

void FactBase::printAllFact(void) const {
	std::cout << "FactBase:" << std::endl;
	for (std::map<std::string, Fact*>::const_iterator it = this->_factMap.begin(); it != this->_factMap.end(); ++it) {
		std::cout << "\t" << (*it).second << std::endl;
	}
}

FactBase * FactBase::_singleton = NULL;