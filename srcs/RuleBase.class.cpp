#include "RuleBase.class.hpp"

RuleBase::RuleBase(void) {

}

RuleBase::RuleBase(RuleBase const &src) {
	*this = src;
}

RuleBase::~RuleBase(void) {

}

RuleBase &RuleBase::operator=(RuleBase const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

void RuleBase::addRule(std::list<Node *> & nodeRuleList) {
	if (nodeRuleList.size())
		;
	for (std::list<Node*>::iterator it = nodeRuleList.begin(); it != nodeRuleList.end(); ++it) {
		std::cout << **it << std::endl;
	}
	std::cout << "TODO ADD RULE" << std::endl;
	// Construct string
	// new Rule;
	// this->_ruleList.push
}

RuleBase * RuleBase::_singleton = NULL;