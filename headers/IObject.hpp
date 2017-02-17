#ifndef IOBJECT_HPP
# define IOBJECT_HPP

#include "Node.class.hpp"

class IObject {
public:
	virtual e_tk getToken(void) const = 0;
	virtual std::string toString(void) const = 0;

	virtual ~IObject(void) { };
};

#endif