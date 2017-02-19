#ifndef IOBJECT_HPP
# define IOBJECT_HPP

#include "Node.class.hpp"
#include <list>

class IObject {
public:
	virtual e_tk getToken(void) const = 0;
	virtual std::string getName(void) const = 0;
	virtual std::string toString(void) const = 0;
	virtual void addChild(IObject* c) = 0;
	virtual std::list<IObject*> getChild(void) const = 0;

	virtual ~IObject(void) { };
};

#endif