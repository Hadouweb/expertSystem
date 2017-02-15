#include <iostream>
#include <regex>
#include "Lexer.class.hpp"
#include "Parser.class.hpp"

int		main(int ac, char **av) {
	Lexer * l;

	if (ac > 1)
		l = new Lexer(av[1]);
	else
		l = new Lexer();

	std::list<Node*> nodeList = l->getNodeList();
	std::list<Node*> errorList = l->getErrorList();

	if (errorList.size() > 0) {
		l->printError();
		//exit(1);
	}

	// DEBUG

	for (std::list<Node*>::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
		std::cout << *(*it);
	}




	return 0;
}


/*int 	main(int ac, char **av) {
	if (ac > 1 && av[1])
		;
	else
		;

	std::ifstream ifs(av[1]);
	if (!ifs.good()) {
		std::cerr << "File not found" << std::endl;
		exit(1);
	}

	std::regex INIT_FACT("=[A-Z]?");
	std::regex IMPLIE("<=>");

	std::string line;
	while (getline(ifs, line)) {
		std::smatch match;
		std::cout << "|" << line << "|" << std::endl;
		if (std::regex_search(line, match, IMPLIE)) {
			std::cout << "IMPLIE: |" << match[0] << "|" << std::endl;
			std::string result = std::regex_replace(line, IMPLIE, "");
			std::cout << "|" << result << "|" << std::endl;
		}
		std::cout << std::endl;
	}

	return 0;
}*/