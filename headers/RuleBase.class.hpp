#ifndef RULE_BASE_CLASS_HPP
# define RULE_BASE_CLASS_HPP

#include "Rule.class.hpp"
#include "FactBase.class.hpp"
#include "ParsedNode.class.hpp"
#include "Operand.class.hpp"
#include <list>
#include <iostream>


class RuleBase {
public:
	static RuleBase * getInstance(void);

	void initRule(std::list<ParsedNode*> parsedList);
	void addRule(std::list<ParsedNode*> & nodeRuleList);
	void printAllRule(void) const;
	Rule * getRuleByConclusion(Fact * f);

private:
	RuleBase(void);
	~RuleBase(void);
	RuleBase(RuleBase const & src);
	RuleBase & operator=(RuleBase const & rhs);
	Operand * addOperand(e_tk token);

	std::map<e_tk, Operand *> _operandMap;
	std::list<Rule*> _ruleList;
	static RuleBase * _singleton;
};

#endif