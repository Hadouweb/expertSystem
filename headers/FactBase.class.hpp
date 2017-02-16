#ifndef FACT_BASE_CLASS_HPP
# define FACT_BASE_CLASS_HPP

#include <list>
#include <map>
#include <iostream>
#include "ParsedNode.class.hpp"
#include "Fact.class.hpp"

class FactBase {
public:
	static FactBase * getInstance(void);
    virtual ~FactBase(void);

	void initFact(std::list<ParsedNode*> parsedList);
	Fact * addFact(std::string name, bool value);
	void printFactBase(void) const;

private:
	FactBase(void);
	FactBase(FactBase const & src);
	FactBase & operator=(FactBase const & rhs);

	std::map<std::string, Fact*> _factMap;
	static FactBase * _singleton;
};

FactBase * FactBase::_singleton = NULL;

#endif