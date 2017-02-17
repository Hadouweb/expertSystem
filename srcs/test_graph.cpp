#include "Graph.class.hpp"
#include <iostream>
#include <vector>

std::string getRandName(const int len) {
	std::string name;
	static const char alphanum[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (int i = 0; i < len; ++i) {
		name += alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	return name;
}

class Data {
public:
	Data(void) {
		this->_nb = rand() % 100;
		this->_name = getRandName(3);
	}
	~Data(void) { }

	int getNb(void) const {
		return this->_nb;
	}

	std::string getName(void) const {
		return this->_name;
	}

private:
	int _nb;
	std::string _name;
};

std::ostream & operator<<(std::ostream & os, Data d) {
	os << "[" << d.getName() << " " << d.getNb() << "\t]";
	return os;
}

int 	main(void) {
	std::vector<Data> dataVector(20);
	for (int i = 0; i < 20; i++) {
		std::cout << dataVector[i] << std::endl;
	}

	return 0;
}