#ifndef OPERAND_CLASS_HPP
# define OPERAND_CLASS_HPP

#include "IObject.hpp"
#include "Node.class.hpp"

class Operator : public IObject {
public:
	Operator(e_tk token);
    virtual ~Operator(void);

	virtual e_tk getToken(void) const;
	std::string getName(void) const;
	std::string toString(void) const;
	virtual void addChild(IObject *c);
	virtual std::list<IObject *> getChild(void) const;
	static bool isOperator(e_tk token);

private:
	Operator(void);
	Operator(Operator const & src);
	Operator & operator=(Operator const & rhs);

	std::list<IObject*> _childList;
	const e_tk _token;
};

#endif