#include "Graph.class.hpp"

Graph::Graph(void) {

}

Graph::~Graph(void) {

}

Graph::Graph(Graph const & src) {
	*this = src;
}

Graph & Graph::operator=(Graph const & rhs) {
	if (this != &rhs) {
	}
	return *this;
}

void Graph::addLink(IObject * parent, IObject * child) {
	child->setParent(parent);
	parent->addChild(child);
}

void Graph::printAllNode(void) const {
	for (defSet::const_iterator it = this->_dataSet.begin(); it != this->_dataSet.end(); ++it) {
		std::cout << (*it).second << std::endl;
	}
}

std::map<int, IObject*> Graph::getObjectMap(void) const {
	return this->_dataSet;
}

void Graph::exploreDFS(IObject *node) {
	node->setVisited(true);
	std::list<IObject *> childList = node->getChild();
	for (std::list<IObject *>::iterator it = childList.begin(); it != childList.end(); ++it) {
		if (!(*it)->getVisited())
			this->exploreDFS(*it);
	}
	if (node->getToken() == TK_PLUS) {
		std::list<IObject *>::iterator itA = childList.begin();
		std::list<IObject *>::iterator itB = std::next(itA, 1);

		if ((*itA)->getValue() == 1 && (*itB)->getValue() == 1)
			node->setValue(1);
	}
	else if (node->getToken() == TK_OR) {
		std::list<IObject *>::iterator itA = childList.begin();
		std::list<IObject *>::iterator itB = std::next(itA, 1);

		if ((*itA)->getValue() == 1 || (*itB)->getValue() == 1)
			node->setValue(1);
	}
	else if (node->getToken() == TK_XOR) {
		std::list<IObject *>::iterator itA = childList.begin();
		std::list<IObject *>::iterator itB = std::next(itA, 1);

		if ((*itA)->getValue() == 1 ^ (*itB)->getValue() == 1)
			node->setValue(1);
	}
	else if (node->getToken() == TK_FACT) {
		for (std::list<IObject *>::iterator it = childList.begin(); it != childList.end(); ++it) {
			node->setValue((*it)->getValue());
		}
	}
	std::cout << node->toString(true, false) << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
}