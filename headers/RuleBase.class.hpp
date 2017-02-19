#ifndef RULE_BASE_CLASS_HPP
# define RULE_BASE_CLASS_HPP

#include "Rule.class.hpp"
#include "FactBase.class.hpp"
#include "ParsedNode.class.hpp"
#include "Operator.class.hpp"
#include <list>
#include <iostream>


class RuleBase {
public:
	static RuleBase * getInstance(void);

	void initRule(std::list<ParsedNode*> parsedList);
	void addRule( std::list<ParsedNode*> & nodeRuleList);
	void printAllRule(void) const;
	Rule * getRuleByConclusion(Fact * f);
	std::list<Operator *> getOperator(void) const;
	std::list<ParsedNode *>::iterator makeNPI(std::list<ParsedNode *>::iterator & it,
		std::list<ParsedNode *> & nodeRuleList,
		std::list<IObject *> & objList);

private:
	RuleBase(void);
	~RuleBase(void);
	RuleBase(RuleBase const & src);
	RuleBase & operator=(RuleBase const & rhs);
	Operator * addOperator(e_tk token);

	std::list<Operator *> _operatorList;
	std::list<Rule*> _ruleList;
	static RuleBase * _singleton;
};

#endif