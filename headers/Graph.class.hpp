#ifndef GRAPH_CLASS_HPP
# define GRAPH_CLASS_HPP

template <typename T>
class Graph {
public:
    Graph(void) { };
    virtual ~Graph(void) { };

    T getData(void) const {
    	return this->_data;
    };

private:
    Graph(Graph const & src) {
    	*this = src;
    };
    Graph & operator=(Graph const & rhs) {
    	if (this != &rhs) {
		}
		return *this;
    };

    T _data;
};

#endif