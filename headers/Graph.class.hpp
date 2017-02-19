#ifndef GRAPH_CLASS_HPP
# define GRAPH_CLASS_HPP

#include "IObject.hpp"
#include <iostream>
#include <map>

class Graph {
public:
	Graph(void);
	virtual ~Graph(void);

	void addLink(IObject * a, IObject * b);
	void printAllNode(void) const;
	std::map<int, IObject*> getObjectMap(void) const;

private:
	Graph(Graph const & src);
	Graph & operator=(Graph const & rhs);

	typedef std::map<int, IObject*> defSet;
	defSet _dataSet;
};


#endif