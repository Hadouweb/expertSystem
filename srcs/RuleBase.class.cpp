#include <Operand.class.hpp>
#include "RuleBase.class.hpp"

RuleBase::RuleBase(std::list<ParsedNode *> parsedList) {
	std::list<ParsedNode*>::iterator it = parsedList.begin();
	std::list<ParsedNode*> ruleList;

	if (it != parsedList.end() && (*it)->getToken() == TK_END_LINE)
		it++;
	while (it != parsedList.end()) {
		if ((*it)->getToken() == TK_END_LINE) {
			this->addRule(ruleList);
			ruleList.clear();
		} else
			ruleList.push_back(*it);
		it++;
	}
}

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

void RuleBase::addRule(std::list<ParsedNode *> & nodeRuleList) {
	std::list<ParsedNode*>::iterator it = nodeRuleList.begin();
	std::list<IObject*> objList;

	while (it != nodeRuleList.end()) {
		e_tk token = (*it)->getToken();
		switch (token) {
			case TK_FACT: {
				Fact * f = FactBase::getInstance()->addFact((*it)->getValue(), false);
				objList.push_back(f);
			}
		}
		it++;
	}
}
