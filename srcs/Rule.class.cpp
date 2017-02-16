#include "Rule.class.hpp"

Rule::Rule(void) {

}

Rule::Rule(Rule const &src) {
	*this = src;
}

Rule::~Rule(void) {

}

Rule &Rule::operator=(Rule const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}
