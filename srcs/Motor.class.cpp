#include "Motor.class.hpp"

Motor::Motor(std::list<ParsedNode *> parsedList)
	: _parsedList(parsedList) {

	this->g = new Graph();
	this->_rDB = RuleBase::getInstance();
	this->_rDB->initRule(this->_parsedList);

	this->_fDB = FactBase::getInstance();
	this->_fDB->initFact(parsedList);

	this->initQueryFact();

	//this->_fDB->printFactBase();
	std::cout << std::endl;
	//this->_rDB->printAllRule();

	if (Parser::errorList.size() > 0) {
		Parser::printError();
		exit(1);
	}

	std::cout << "*********************************************" << std::endl;
	this->searchQuery();
}

Motor::~Motor(void) { }

Motor::Motor(void) { }

Motor::Motor(Motor const &src) {
	*this = src;
}

Motor &Motor::operator=(Motor const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

void Motor::initQueryFact(void) {
	bool findQueryFact = false;

	for (std::list<ParsedNode *>::iterator it = this->_parsedList.begin();
		it != this->_parsedList.end(); ++it) {
		if ((*it)->getToken() == TK_QUERY) {
			findQueryFact = true;
			std::string val = (*it)->getValue();
			for (std::string::iterator itFact = val.begin(); itFact != val.end(); ++itFact) {
				std::string s(1, *itFact);
				Fact *f = FactBase::getInstance()->getFactByName(s);
				this->_queryFactList.push_back(f);
			}
		}
	}

	if (!findQueryFact) {
		Error * e = new Error(0, 0, "Token ? is expected at the end");
		e->pos = false;
		Parser::pushError(e);
	}
}

void Motor::printQueryFact(void) {
	std::cout << std::endl;
	std::cout << "Query:" << std::endl;
	for (std::list<Fact*>::iterator it = this->_queryFactList.begin();
		it != this->_queryFactList.end(); ++it) {
		std::cout << "\t" << *it << std::endl;
	}
}

void Motor::searchQuery(void) {
	for (std::list<Fact*>::iterator it = this->_queryFactList.begin();
		 it != this->_queryFactList.end(); ++it) {
		this->makeGraph(*it);
	}
}

void Motor::pushOnGraph(IObject *q, Rule *r,
	std::list<IObject*>::reverse_iterator & it,
	std::list<IObject*> & premiseList,
	std::list<IObject*> & stack)
{
	while (it != premiseList.rend()) {
		e_tk token = (*it)->getToken();
		if (Operator::isOperator(token)) {
			IObject *obj = *it;
			stack.push_front(*it);
			g->addLink(q, *it);
			it++;
			this->pushOnGraph(obj, r, it, premiseList, stack);
		} else if (token == TK_FACT) {
			IObject * io = stack.front();
			if (io && io->getChild().size() < 1)
				g->addLink(io, *it);
			else if (io && io->getToken() != TK_NOT && io->getChild().size() < 2)
				g->addLink(io, *it);
			else if (io) {
				stack.pop_front();
				g->addLink(stack.front(), *it);
			} else
				g->addLink(q, *it);
			this->findRule(*it);
			it++;
		}
	}
}

void Motor::findRule(IObject * q) {
	Rule * r = NULL;
	if (q->getToken() == TK_FACT) {
		while (42) {
			r = this->_rDB->getRuleByConclusion(static_cast<Fact *>(q));
			if (r != NULL) {
				std::list<IObject *> premiseList = r->getPremiseList();
				std::list<IObject *>::reverse_iterator it = premiseList.rbegin();
				std::list<IObject *> stack;
				this->pushOnGraph(q, r, it, premiseList, stack);
			} else
				break ;
		}
	}
}

void Motor::makeGraph(Fact * q) {
	std::cout << "*********************************************" << std::endl;
	std::cout << "Make Graph for query: (" << q << ")" << std::endl;
	this->findRule(q);
	//this->printAllObject(true, true);
	this->g->exploreDFS(q);
}

void Motor::printAllObject(bool withParent, bool withChild) const {
	std::cout << std::endl;
	std::map<std::string, Fact *> factMap = this->_fDB->getAllFact();
	std::cout << "AllFact: " << std::endl << std::endl;
	for (std::map<std::string, Fact*>::const_iterator it = factMap.begin(); it != factMap.end(); ++it) {
		std::cout << (*it).second->toString(withParent, withChild) << std::endl;
	}

	std::list<Operator *> opList = this->_rDB->getOperator();
	std::cout << "AllOperator: " << std::endl << std::endl;
	for (std::list<Operator *>::const_iterator it = opList.begin(); it != opList.end(); ++it) {
		if (Operator::isOperator((*it)->getToken())) {
			std::cout << (*it)->toString(withParent, withChild) << std::endl;
		}
	}
}