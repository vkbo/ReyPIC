/**
 * ReyPIC – Math Header
 */

#ifndef CLASS_MATH
#define CLASS_MATH

// Class-specific macros
#define MT_NONE      0
#define MT_OPERATOR  1
#define MT_NUMBER    2
#define MT_WORD      3
#define MT_SEPARATOR 4

#define MP_INVALID  -1
#define MP_NONE      0
#define MP_NUMBER    1
#define MP_VARIABLE  2
#define MP_FUNC      3
#define MP_CONST     4
#define MP_LOGICAL   5
#define MP_MATH      6
#define MP_LBRACK    7
#define MP_RBRACK    8
#define MP_COMMA     9

// Includes
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
    * Member Functions
    */

    int validOperator(string_t*);
    int validWord(string_t*);
    int validNumber(string_t*, double*);
    int validSeparator(string_t*);

   /**
    * Member Variables
    */

    vstring_t          m_WVariable = {"x1","x2","x3"};
    const vstring_t    m_WFunc     = {"sin","cos","tan","exp","abs","mod","if"};
    const vstring_t    m_WConst    = {"pi"};
    const vstring_t    m_OLogical  = {"&&","||","==","<",">",">=","<=","!=","<>"};
    const vstring_t    m_OMath     = {"+","-","*","/","^"};

    string_t           m_Equation  = "";
    std::vector<lexer> m_Lexer;

};

} // End NameSpace

#endif
