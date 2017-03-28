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
	if (child && parent) {
		child->setParent(parent);
		parent->addChild(child);
	}
}

void Graph::printAllNode(void) const {
	for (defSet::const_iterator it = this->_dataSet.begin(); it != this->_dataSet.end(); ++it) {
		std::cout << (*it).second << std::endl;
	}
}

std::map<int, IObject*> Graph::getObjectMap(void) const {
	return this->_dataSet;
}

void Graph::execOp(IObject *curr, IObject *a, IObject *b) {
	//std::cout << "# " << curr->toString(false, false) << std::endl;
	switch(curr->getToken()) {
		case TK_PLUS: {
			if (a->getValue() == 1 && b->getValue() == 1)
				curr->setValue(1);
			break;
		}
		case TK_OR: {
			if (a->getValue() == 1 || b->getValue() == 1)
				curr->setValue(1);
			break;
		}
		case TK_XOR: {
			if (a->getValue() == 1 ^ b->getValue() == 1)
				curr->setValue(1);
			break;
		}
		case TK_FACT: {
			curr->setValue(a->getValue());
			Fact *f = static_cast<Fact*>(curr);
			if (f->getIsNot()) {
				if (f->getValue() == 0)
					f->setValue(1);
				else if (f->getValue() == 1)
					f->setValue(0);
			}
			break;
		}
		case TK_NOT: {
			if (a->getValue() == 0)
				curr->setValue(1);
			if (a->getValue() == 1)
				curr->setValue(0);
			break;
		}
		default:
			return;
	}
}

void Graph::exploreDFS(IObject *node) {
	node->setVisited(true);
	std::list<IObject *> childList = node->getChild();
	for (std::list<IObject *>::iterator it = childList.begin(); it != childList.end(); ++it) {
		if (!(*it)->getVisited())
			this->exploreDFS(*it);
	}
	if (node->getToken() == TK_PLUS ||
		node->getToken() == TK_OR ||
		node->getToken() == TK_XOR) {
		std::list<IObject *>::iterator itA = childList.begin();
		std::list<IObject *>::iterator itB = std::next(itA, 1);
		this->execOp(node, *itA, *itB);
	}
	else if (node->getToken() == TK_FACT) {
		for (std::list<IObject *>::iterator it = childList.begin(); it != childList.end(); ++it) {
			//std::cout << "* " << (*it)->toString(false, false) << std::endl;
			this->execOp(node, *it, NULL);
			if (node->getValue() == 1)
				break;
		}
	}
	else if (node->getToken() == TK_NOT) {
		std::list<IObject *>::iterator itA = childList.begin();
		this->execOp(node, *itA, NULL);
	}
	std::cout << node->toString(true, true) << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
}