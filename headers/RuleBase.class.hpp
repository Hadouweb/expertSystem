#ifndef RULE_BASE_CLASS_HPP
# define RULE_BASE_CLASS_HPP

#include "Rule.class.hpp"
#include "Node.class.hpp"
#include <list>
#include <iostream>


class RuleBase {
public:
	static RuleBase * getInstance() {
		if (_singleton == NULL) {
			_singleton = new RuleBase();
		}
		return _singleton;
	}

	void addRule(std::list<Node*> & nodeRuleList);

private:
	RuleBase(void);
	~RuleBase(void);
	RuleBase(RuleBase const & src);
	RuleBase & operator=(RuleBase const & rhs);

	static RuleBase *_singleton;
	std::list<Rule> _ruleList;
};

#endif