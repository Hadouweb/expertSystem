#include "Graph.class.hpp"

Graph::Graph(void) {

}

Graph::~Graph(void) {

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


Graph::Graph(Graph const & src) {
	*this = src;
}

Graph & Graph::operator=(Graph const & rhs) {
	if (this != &rhs) {
	}
	return *this;
}
