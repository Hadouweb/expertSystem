#ifndef FACT_BASE_CLASS_HPP
# define FACT_BASE_CLASS_HPP

class FactBase {
public:
    FactBase(void);
    FactBase(FactBase const & src);
    
    virtual ~FactBase(void);
    
    FactBase & operator=(FactBase const & rhs);
};

#endif