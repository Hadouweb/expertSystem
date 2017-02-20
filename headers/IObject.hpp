#ifndef IOBJECT_HPP
# define IOBJECT_HPP

#include "Node.class.hpp"
#include <list>

class IObject {
public:
	virtual e_tk getToken(void) const = 0;
	virtual std::string getName(void) const = 0;
	virtual std::string toString(bool withParent, bool withChild) const = 0;
	virtual uint8_t getValue(void) const = 0;
	virtual void setValue(uint8_t val) = 0;
	virtual void addChild(IObject* c) = 0;
	virtual void setParent(IObject* p) = 0;
	virtual void setVisited(bool val) = 0;
	virtual bool getVisited(void) const = 0;
	virtual std::list<IObject*> getChild(void) const = 0;
	virtual IObject * getParent(void) const = 0;

	virtual ~IObject(void) { };
};

#endif