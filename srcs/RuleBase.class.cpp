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
	while (it != parsedList.end() && (*it)->getToken() != TK_INIT_FACT) {
		if ((*it)->getToken() == TK_END_LINE) {
			this->addRule(ruleList);
			ruleList.clear();
		} else
			ruleList.push_back(*it);
		it++;
	}
}

Operator *RuleBase::addOperator(e_tk token) {
	Operator * op = new Operator(token);
	this->_operatorList.push_back(op);
	op->indexDebug = this->_operatorList.size();
	return op;
}

std::list<ParsedNode *>::iterator RuleBase::makeNPI(
	std::list<ParsedNode *>::iterator & it,
	std::list<ParsedNode *> & nodeRuleList,
	std::list<IObject *> & objList)
{
	std::list<IObject *> stack;

	while (it != nodeRuleList.end()) {
		e_tk token = (*it)->getToken();
		if (token == TK_FACT) {
			Fact * f = FactBase::getInstance()->addFact((*it)->getValue(), false);
			objList.push_back(f);
		} else {
			Operator *op = this->addOperator(token);
			if (token == TK_PAR_OPEN)
				stack.push_front(op);
			else if (Operator::isOperator(token)) {
				if (stack.empty())
					stack.push_front(op);
				else if (stack.front()->getToken() == TK_PAR_OPEN)
					stack.push_front(op);
				else if (token < stack.front()->getToken())
					stack.push_front(op);
				else {
					objList.push_back(stack.front());
					stack.pop_front();
					stack.push_front(op);
				}
			}
			else if (token == TK_PAR_CLOSE) {
				while (!stack.empty()) {
					IObject * op = stack.front();
					if (op->getToken() == TK_PAR_OPEN)
						break;
					objList.push_back(op);
					stack.pop_front();
				}
			}
		}
		if (token == TK_IMPLIE || token == TK_IF_AND_ONLY_IF)
			break ;
		it++;
	}

	while (!stack.empty()) {
		IObject *op = stack.front();
		if (Operator::isOperator(op->getToken()))
			objList.push_back(op);
		stack.pop_front();
	}

	return it;
}


void RuleBase::addRule(std::list<ParsedNode *> & nodeRuleList) {
	std::list<ParsedNode*>::iterator it = nodeRuleList.begin();
	std::list<IObject*> premiseList;
	IObject *linkOperator;
	std::list<IObject*> conclusionList;

	// Make premise list and linkOperator
	it = makeNPI(it, nodeRuleList, premiseList);
	e_tk token = (*it)->getToken();

	/*for (std::list<IObject *>::iterator it = premiseList.begin(); it != premiseList.end(); ++it) {
		std::cout << (*it)->getName() << " " << Node::convertEnumTk((*it)->getToken()) << std::endl;
	}

	std::cout << Node::convertEnumTk(token) << std::endl;
	std::cout << std::endl;*/

	linkOperator = this->addOperator(token);
	it++;

	makeNPI(it, nodeRuleList, conclusionList);

	Rule *r = new Rule(premiseList, linkOperator, conclusionList);
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

std::list<Operator *> RuleBase::getOperator(void) const {
	return this->_operatorList;
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