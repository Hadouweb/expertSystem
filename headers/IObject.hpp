#ifndef IOBJECT_HPP
# define IOBJECT_HPP

class IObject {
public:
	virtual e_tk getToken(void) const = 0;
	virtual ~IObject();
};

#endif