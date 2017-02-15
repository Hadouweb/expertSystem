#ifndef NODE_CLASS_HPP
# define NODE_CLASS_HPP

#include <iomanip>

enum e_tk {
	TK_FACT,
	TK_INIT_FACT,
	TK_QUERY,
	TK_IMPLIE,
	TK_PLUS,
	TK_NOT,
	TK_OR,
	TK_XOR,
	TK_IF_AND_ONLY_IF,
	TK_PAR_OPEN,
	TK_PAR_CLOSE,
	TK_COMMENT,
	TK_END_LINE,
	TK_WHITE_SPACE,
	NB_TK,
};


class Node {
public:
	Node(e_tk tk, std::string val, unsigned int numLine, unsigned int numCol);
    ~Node(void);

	static std::string convertEnumTk(e_tk e);

	e_tk getToken(void) const;
	unsigned int getNumLine() const;
	unsigned int getNumCol() const;
	std::string getValue() const;

private:
	Node(void);
	Node & operator=(Node const & rhs);
	Node(Node const & src);
	e_tk _token;
	std::string _value;
	unsigned int _numLine;
	unsigned int _numCol;
};

std::ostream & operator<<(std::ostream & os, Node & n);

#endif