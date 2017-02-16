#ifndef RULE_CLASS_HPP
# define RULE_CLASS_HPP

class Rule {
public:
    Rule(void);
    Rule(Rule const & src);
    
    virtual ~Rule(void);
    
    Rule & operator=(Rule const & rhs);
};

#endif