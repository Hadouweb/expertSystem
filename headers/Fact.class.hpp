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
	std::string toString(bool withParent, bool withChild) const;
	bool getIsFactBase(void) const;
	void setIsFactBase(bool isFactBase);
	bool getIsNot(void) const;
	void setIsNot(bool isNot);
	bool getUsedRule(void) const;
	void setUsedRule(bool usedRule);
	virtual e_tk getToken(void) const;
	virtual uint8_t getValue(void) const;
	virtual void setValue(uint8_t val);
	virtual void addChild(IObject *c);
	virtual std::list<IObject *> getChild(void) const;
	virtual void setParent(IObject *p);
	virtual IObject *getParent(void) const;
	virtual void setVisited(bool val);
	virtual bool getVisited(void) const;

private:
	Fact(void);
	Fact(Fact const & src);
	Fact & operator=(Fact const & rhs);

	bool _visited;
	IObject * _parent;
	std::list<IObject*> _childList;
	const e_tk _token;
	const std::string _name;
	uint8_t _value;
	bool _isFactBase;
	bool _isNot;
	bool _usedRule;
};

std::ostream & operator<<(std::ostream & os, Fact *f);

#endif