#ifndef GRAPH_CLASS_HPP
# define GRAPH_CLASS_HPP

#include "IObject.hpp"
#include <iostream>
#include <map>
#include <list>

class Graph {
public:
	Graph(void);
	virtual ~Graph(void);

	void addLink(IObject * parent, IObject * child);
	void printAllNode(void) const;
	std::map<int, IObject*> getObjectMap(void) const;
	void exploreDFS(IObject * node);

private:
	Graph(Graph const & src);
	Graph & operator=(Graph const & rhs);

	typedef std::map<int, IObject*> defSet;
	defSet _dataSet;
};


#endif