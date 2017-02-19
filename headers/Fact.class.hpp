#ifndef FACT_CLASS_HPP
# define FACT_CLASS_HPP

#include <iostream>
#include <sstream>
#include <list>
#include "IObject.hpp"
#include "Node.class.hpp"

class Fact : public IObject {
public:
    Fact(e_tk token, std::string name, uint8_t value);
    virtual ~Fact(void);

	std::string getName(void) const;
	uint8_t getValue(void) const;
	virtual e_tk getToken(void) const;
	void setValue(uint8_t val);
	std::string toString(void) const;
	virtual void addChild(IObject *c);
	virtual std::list<IObject *> getChild(void) const;
	virtual void setParent(IObject *p);
	virtual IObject *getParent(void) const;

private:
	Fact(void);
	Fact(Fact const & src);
	Fact & operator=(Fact const & rhs);

	IObject * _parent;
	std::list<IObject*> _childList;
	const e_tk _token;
	const std::string _name;
	uint8_t _value;
};

std::ostream & operator<<(std::ostream & os, Fact *f);

#endif