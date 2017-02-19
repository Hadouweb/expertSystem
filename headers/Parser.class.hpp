#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP

#include <vector>
#include <iostream>
#include <list>
#include <map>
#include "Node.class.hpp"
#include "ParsedNode.class.hpp"

struct Error {
	Error(unsigned int col, unsigned int line, std::string type);
	unsigned int col;
	unsigned int line;
	bool pos;
	std::string type;
};

class Parser {
public:
    Parser(std::list<Node *> nodeList);

    ~Parser(void);

    void makeParsing(void);
	std::list<ParsedNode*> getParsedNodeList(void) const;
	void reduceList(void);

	static std::list<Error*> errorList;
	static void pushError(unsigned int col, unsigned int line, std::string type);
	static void pushError(Error * e);
	static void printError(void);

private:
	Parser(Parser const & src);
	Parser & operator=(Parser const & rhs);
	bool authorizedOperator(e_tk token);
	void skipSpace(void);

	void tkFact(void);
	void tkInitFact(void);
	void tkQuery(void);
	void tkImplie(void);
	void tkPlus(void);
	void tkNot(void);
	void tkOr(void);
	void tkXor(void);
	void tkIfAndOnlyIf(void);
	void tkParOpen(void);
	void tkParClose(void);

	typedef std::map<e_tk, void (Parser::*)(void) > instrMapType;

	instrMapType _instrCheckerMap = {
    	{TK_FACT, 			&Parser::tkFact},
		{TK_INIT_FACT, 		&Parser::tkInitFact},
		{TK_QUERY, 			&Parser::tkQuery},
		{TK_IMPLIE, 		&Parser::tkImplie},
		{TK_PLUS, 			&Parser::tkPlus},
		{TK_NOT, 			&Parser::tkNot},
		{TK_OR, 			&Parser::tkOr},
		{TK_XOR, 			&Parser::tkXor},
		{TK_IF_AND_ONLY_IF, &Parser::tkIfAndOnlyIf},
		{TK_PAR_OPEN, 		&Parser::tkParOpen},
		{TK_PAR_CLOSE, 		&Parser::tkParClose},
    };

	class SynthaxException : public std::exception {
		public:
			SynthaxException(void);
			~SynthaxException(void) throw();
			virtual const char* what() const throw();
		private:
			SynthaxException(SynthaxException const & src);
			SynthaxException & operator=(SynthaxException const & rhs);
	};

	std::list<Node *> _nodeList;
	std::list<Node *>::iterator _currentIt;
	std::list<ParsedNode*> _parsedNodeList;
};

#endif