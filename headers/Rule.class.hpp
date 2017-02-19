#ifndef RULE_CLASS_HPP
# define RULE_CLASS_HPP

#include <list>
#include <iostream>
#include "IObject.hpp"

class Rule {
public:
	Rule(	std::list<IObject*> premiseList,
			IObject *linkOperand,
			std::list<IObject*> conclusionList);
    virtual ~Rule(void);
	std::list<IObject*> getPremiseList(void) const;
	IObject* getLinkOperand(void) const;
	std::list<IObject*> getConclusionList(void) const;

	bool used;

private:
	Rule(void);
	Rule(Rule const & src);
	Rule & operator=(Rule const & rhs);

	std::list<IObject*> _premiseList;
	IObject *_linkOperand;
	std::list<IObject*> _conclusionList;
};

std::ostream & operator<<(std::ostream & os, Rule *r);

#endif