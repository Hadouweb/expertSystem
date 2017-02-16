#ifndef RULE_BASE_CLASS_HPP
# define RULE_BASE_CLASS_HPP

#include "Rule.class.hpp"
#include "FactBase.class.hpp"
#include "ParsedNode.class.hpp"
#include <list>
#include <iostream>


class RuleBase {
public:
	RuleBase(std::list<ParsedNode*> parsedList);
	void addRule(std::list<ParsedNode*> & nodeRuleList);

private:
	RuleBase(void);
	~RuleBase(void);
	RuleBase(RuleBase const & src);
	RuleBase & operator=(RuleBase const & rhs);

	std::list<Rule> _ruleList;
};

#endif