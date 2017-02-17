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

void RuleBase::initRule(std::list<ParsedNode *> parsedList) {
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

Operand *RuleBase::addOperand(e_tk token) {
	std::map<e_tk, Operand*>::iterator it = this->_operandMap.find(token);
	Operand *op;
	if (it == this->_operandMap.end()) {
		op = new Operand(token);
		this->_operandMap.insert(std::pair<e_tk, Operand*>(token, op));
	} else
		op = (*it).second;
	return op;
}

void RuleBase::addRule(std::list<ParsedNode *> & nodeRuleList) {
	std::list<ParsedNode*>::iterator it = nodeRuleList.begin();
	std::list<IObject*> premiseList;
	IObject *linkOperand;
	std::list<IObject*> conclusionList;

	// Make premise list and linkOperand
	while (it != nodeRuleList.end()) {
		e_tk token = (*it)->getToken();
		if (token == TK_FACT) {
			Fact * f = FactBase::getInstance()->addFact((*it)->getValue(), false);
			premiseList.push_back(f);
		}
		else if (token == TK_PLUS || token == TK_OR || token == TK_XOR || token == TK_NOT) {
			Operand *op = this->addOperand(token);
			premiseList.push_back(op);
		}
		else if (token == TK_IMPLIE || token == TK_IF_AND_ONLY_IF) {
			linkOperand = this->addOperand(token);
			it++;
			break ;
		}
		it++;
	}

	// Make conclusion list
	while (it != nodeRuleList.end()) {
		e_tk token = (*it)->getToken();
		if (token == TK_FACT) {
			Fact * f = FactBase::getInstance()->addFact((*it)->getValue(), false);
			conclusionList.push_back(f);
		}
		else if (token == TK_PLUS || token == TK_OR || token == TK_XOR || token == TK_NOT) {
			Operand *op = this->addOperand(token);
			conclusionList.push_back(op);
		}
		it++;
	}

	Rule *r = new Rule(premiseList, linkOperand, conclusionList);
	this->_ruleList.push_back(r);
}

Rule *RuleBase::getRuleByConclusion(Fact *f) {
	for (std::list<Rule *>::reverse_iterator itR = this->_ruleList.rbegin();
		itR != this->_ruleList.rend(); ++itR) {
		if ((*itR)->used == false) {
			std::list<IObject*> cList = (*itR)->getConclusionList();
			for (std::list<IObject *>::iterator itC = cList.begin(); itC != cList.end(); ++itC) {
				if ((*itC)->getName() == f->getName())
					return *itR;
			}
		}
	}
	return NULL;
}

RuleBase *RuleBase::getInstance(void) {
	if (_singleton == NULL) {
		_singleton = new RuleBase();
	}
	return _singleton;
}

void RuleBase::printAllRule(void) const {
	for (std::list<Rule*>::const_iterator it = this->_ruleList.begin(); it != this->_ruleList.end(); ++it) {
		std::cout << *it << std::endl;
	}
}

RuleBase * RuleBase::_singleton = NULL;