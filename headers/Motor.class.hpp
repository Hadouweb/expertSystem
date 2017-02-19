#ifndef MOTOR_CLASS_HPP
# define MOTOR_CLASS_HPP

#include <list>
#include "ParsedNode.class.hpp"
#include "FactBase.class.hpp"
#include "RuleBase.class.hpp"
#include "Graph.class.hpp"

class Motor {
public:
	Motor(std::list<ParsedNode*> parsedList);
    ~Motor(void);

	void initQueryFact(void);
	void printQueryFact(void);

	void searchQuery(void);
	void makeGraph(Fact * q);

	void pushOnGraph(IObject *f, Rule *r,
		std::list<IObject*>::reverse_iterator & it,
		std::list<IObject*> & premiseList,
		std::list<IObject*> & stack);
	void findRule(IObject * f);

	void printAllObject(bool withParent, bool withChild) const;

private:
	Motor(void);
	Motor(Motor const & src);
	Motor & operator=(Motor const & rhs);

	Graph *g;
	std::list<ParsedNode*> _parsedList;
	std::list<Fact*> _queryFactList;
	FactBase * _fDB;
	RuleBase * _rDB;
};

#endif