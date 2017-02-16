#ifndef MOTOR_CLASS_HPP
# define MOTOR_CLASS_HPP

#include "ParsedNode.class.hpp"
#include "FactBase.class.hpp"
#include "RuleBase.class.hpp"

class Motor {
public:
	Motor(std::list<ParsedNode*> parsedList);
    ~Motor(void);

private:
	Motor(void);
	Motor(Motor const & src);
	Motor & operator=(Motor const & rhs);

	std::list<ParsedNode*> _parsedList;
	FactBase * _fDB;
	RuleBase * _rDB;
};

#endif