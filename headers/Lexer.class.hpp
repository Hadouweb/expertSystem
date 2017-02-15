#ifndef LEXER_HPP
# define LEXER_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <sstream>
#include <algorithm>
#include "Node.class.hpp"

class Node;

enum	e_sts {
	STS_ACCEPT,
	STS_REJECT,
	STS_HUNGRY,
};

struct Status {
	e_sts prev;
	e_sts curr;
};

class Lexer {
public:
    Lexer(void);
    Lexer(std::string fileName);

    ~Lexer(void);
	std::list<Node*> getNodeList(void) const;
	std::list<Node*> getErrorList(void) const;
	void printError(void);

	static std::string convertStsEnum(enum e_sts sts);

private:
	Lexer(Lexer const & src);
	Lexer & operator=(Lexer const & rhs);
	void forEachLine(std::istream & is);
	bool forEachChar(std::string & line, unsigned int numLine);
	void updateStatus(void);
	enum e_tk pushToken(unsigned int line, unsigned int col);
	void pushError(unsigned int line, unsigned int col);
	bool matchToken(const char c);
	e_tk getTokenFound(void);

	e_sts tkFact(const char c, const uint8_t index);
	e_sts tkInitFact(const char c, const uint8_t index);
	e_sts tkQuery(const char c, const uint8_t index);
	e_sts tkImplie(const char c, const uint8_t index);
	e_sts tkPlus(const char c, const uint8_t index);
	e_sts tkNot(const char c, const uint8_t index);
	e_sts tkOr(const char c, const uint8_t index);
	e_sts tkIfAndOnlyIf(const char c, const uint8_t index);
	e_sts tkXor(const char c, const uint8_t index);
	e_sts tkParOpen(const char c, const uint8_t index);
	e_sts tkParClose(const char c, const uint8_t index);
	e_sts tkComment(const char c, const uint8_t index);
	e_sts tkEndLine(const char c, const uint8_t index);
	e_sts tkWhiteSpace(const char c, const uint8_t index);

	std::list<Node*> _nodeList;
	std::list<Node*> _errorList;

	typedef std::vector<e_sts (Lexer::*)(const char c, const uint8_t index)> tkVectorType;
	tkVectorType _tk = {
		&Lexer::tkFact,
		&Lexer::tkInitFact,
		&Lexer::tkQuery,
		&Lexer::tkImplie,
		&Lexer::tkIfAndOnlyIf,
		&Lexer::tkPlus,
		&Lexer::tkNot,
		&Lexer::tkOr,
		&Lexer::tkXor,
		&Lexer::tkParOpen,
		&Lexer::tkParClose,
		&Lexer::tkComment,
		&Lexer::tkEndLine,
		&Lexer::tkWhiteSpace,
	};

	class UnknownTokenException : public std::exception {
		public:
			UnknownTokenException(void);
			~UnknownTokenException(void) throw();
			virtual const char* what() const throw();
		private:
			UnknownTokenException(UnknownTokenException const & src);
			UnknownTokenException & operator=(UnknownTokenException const & rhs);
	};

	void printStatus(void);

	std::vector<Status> _status;
	std::vector<uint8_t> _state;
	std::vector<std::string> _chunk;
	bool _modeCin;
};

std::ostream & operator<<(std::ostream & os, Status & s);

#endif