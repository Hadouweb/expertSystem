#ifndef OPERAND_CLASS_HPP
# define OPERAND_CLASS_HPP

#include "IObject.hpp"
#include "Node.class.hpp"
#include <sstream>
#include <iostream>

class Operator : public IObject {
public:
	Operator(e_tk token);
    virtual ~Operator(void);

	virtual e_tk getToken(void) const;
	std::string getName(void) const;
	std::string toString(bool withParent, bool withChild) const;
	virtual uint8_t getValue(void) const;
	virtual void setValue(uint8_t val);
	virtual void addChild(IObject *c);
	virtual std::list<IObject *> getChild(void) const;
	virtual void setParent(IObject *p);
	virtual IObject *getParent(void) const;
	virtual void setVisited(bool val);
	virtual bool getVisited(void) const;

	static bool isOperator(e_tk token);
	int indexDebug;

private:
	Operator(void);
	Operator(Operator const & src);
	Operator & operator=(Operator const & rhs);

	uint8_t _value;
	bool _visited;
	IObject * _parent;
	std::list<IObject*> _childList;
	const e_tk _token;
};

#endif