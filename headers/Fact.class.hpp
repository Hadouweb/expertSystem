#ifndef FACT_CLASS_HPP
# define FACT_CLASS_HPP

class Fact {
public:
    Fact(void);
    Fact(Fact const & src);
    
    virtual ~Fact(void);
    
    Fact & operator=(Fact const & rhs);
};

#endif