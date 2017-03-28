#include <iostream>
#include "Lexer.class.hpp"
#include "Parser.class.hpp"
#include "Motor.class.hpp"

int		main(int ac, char **av) {
	Lexer * l;

	if (ac > 1)
		l = new Lexer(av[1]);
	else {
		std::cerr << "Usage: " << av[0] << " file" << std::endl;
		exit(1);
	}

	std::list<Node*> nodeList = l->getNodeList();
	std::list<Node*> errorList = l->getErrorList();

	if (errorList.size() > 0) {
		l->printError();
		exit(1);
	}

	// DEBUG

	//for (std::list<Node*>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
	//	std::cout << *(*it) << std::endl;
	//}
	//std::cout << "Size List : " << nodeList.size() << std::endl;

	std::cout << std::endl;

	Parser p(nodeList);

	p.reduceList();

	std::list<ParsedNode*> parsedListParser = p.getParsedNodeList();

	if (Parser::errorList.size() > 0) {
		p.printError();
		exit(1);
	}

	// DEBUG
	//for (std::list<ParsedNode*>::iterator it = parsedListParser.begin(); it != parsedListParser.end(); ++it) {
	//	std::cout << *(*it) << std::endl;
	//}

	Motor m(parsedListParser);


	return 0;
}