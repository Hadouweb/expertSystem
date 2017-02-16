#ifndef PARSED_NODE_CLASS_HPP
# define PARSED_NODE_CLASS_HPP

#include "Node.class.hpp"

class ParsedNode {
public:
	ParsedNode(e_tk pTkInstr, std::string val);
    ~ParsedNode(void);

    e_tk getToken(void) const;
    std::string getValue(void) const;

private:
	ParsedNode(ParsedNode const & src);
	ParsedNode & operator=(ParsedNode const & rhs);
	const e_tk _tk;
	std::string _value;
	ParsedNode(void);
};

std::ostream & operator<<(std::ostream & os, ParsedNode & pN);

#endif