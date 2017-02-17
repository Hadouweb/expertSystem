#ifndef OPERAND_CLASS_HPP
# define OPERAND_CLASS_HPP

#include "IObject.hpp"
#include "Node.class.hpp"

class Operand : public IObject {
public:
	Operand(e_tk token);
    virtual ~Operand(void);

	virtual e_tk getToken(void) const;
	std::string getName(void) const;
	std::string toString(void) const;

private:
	Operand(void);
	Operand(Operand const & src);
	Operand & operator=(Operand const & rhs);

	const e_tk _token;
};

#endif