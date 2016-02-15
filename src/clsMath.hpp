/**
 * ReyPIC – Math Header
 */

#ifndef CLASS_MATH
#define CLASS_MATH

// Class-specific macros
#define MT_NONE     0
#define MT_OPERATOR 1
#define MT_NUMBER   2
#define MT_WORD     3

#include "config.hpp"
#include <cctype>

namespace reypic {

class Math {

public:

   /**
    * Constructor/Destructor
    */

    Math();
    ~Math() {};

   /**
    * Setters/Getters
    */

    bool setEquation(string_t);

   /**
    * Methods
    */
    
    double Eval(vstring_t, vdouble_t);

   /**
    * Properties
    */

private:

   /**
    * Structs
    */
    
    struct lexer {
        int      type;
        string_t content;
        double   value;
    };

   /**
    * Member Variables
    */
    
    string_t           m_Equation = "";
    std::vector<lexer> m_Lexer;

};

} // End NameSpace

#endif
