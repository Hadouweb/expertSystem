#ifndef FACT_CLASS_HPP
# define FACT_CLASS_HPP

#include <iostream>
#include "IObject.hpp"
#include "Node.class.hpp"

class Fact : public IObject {
public:
    Fact(e_tk token, std::string name, bool value);
    virtual ~Fact(void);

	std::string getName(void) const;
	bool getValue(void) const;
	virtual e_tk getToken(void) const;
	void setValue(bool val);

private:
	Fact(void);
	Fact(Fact const & src);
	Fact & operator=(Fact const & rhs);

	const e_tk _token;
	const std::string _name;
	bool _value;
};

std::ostream & operator<<(std::ostream & os, Fact *f);

#endif