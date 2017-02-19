#include <Operator.class.hpp>
#include "Rule.class.hpp"

Rule::Rule(std::list<IObject *> premiseList, IObject *linkOperand,
		   std::list<IObject *> conclusionList)
		: 	_premiseList(premiseList),
			_linkOperand(linkOperand),
			_conclusionList(conclusionList) {
	this->used = false;
}

Rule::Rule(void) {

}

Rule::Rule(Rule const &src) {
	*this = src;
}

Rule::~Rule(void) {

}

Rule &Rule::operator=(Rule const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

std::list<IObject *> Rule::getPremiseList(void) const {
	return this->_premiseList;
}

IObject *Rule::getLinkOperand(void) const {
	return this->_linkOperand;
}

std::list<IObject *> Rule::getConclusionList(void) const {
	return this->_conclusionList;
}

std::ostream &operator<<(std::ostream &os, Rule *r) {
	os << "Premise: " << std::endl;
	std::list<IObject*> p = r->getPremiseList();
	for (std::list<IObject*>::iterator it = p.begin(); it != p.end(); ++it)
		os << "\t" << (*it)->toString() << std::endl;

	os << "Link: " << std::endl;
	os << "\t" << r->getLinkOperand()->toString() << std::endl;

	os << "Conclusion: " << std::endl;
	std::list<IObject*> c = r->getConclusionList();
	for (std::list<IObject*>::iterator it = c.begin(); it != c.end(); ++it)
		os << "\t" << (*it)->toString() << std::endl;

	return os;
}
