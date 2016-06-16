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
#define MP_CONST     3
#define MP_FUNC      4
#define MP_LOGICAL   5
#define MP_MATH      6
#define MP_LBRACK    7
#define MP_RBRACK    8
#define MP_COMMA     9
#define MP_END       10

#define ASSOC_L      1
#define ASSOC_R      2

#define EVAL_TRUE    1.0
#define EVAL_FALSE   0.0

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

    bool setVariables(vstring_t);
    bool setEquation(string_t);

   /**
    * Methods
    */

    bool Eval(vdouble_t, double_t*);

   /**
    * Properties
    */

private:

   /**
    * Structs
    */

    struct token {
        value_t  type;
        string_t content;
        double_t value;
    };

   /**
    * Member Functions
    */

    bool    eqLexer();
    bool    eqParser();

    value_t validOperator(string_t*);
    value_t validWord(string_t*);
    value_t validNumber(string_t*, double_t*);
    value_t validSeparator(string_t*);

    void    precedenceLogical(string_t, int32_t*, int32_t*);
    void    precedenceMath(string_t, int32_t*, int32_t*);

    bool    evalVariable(string_t, vdouble_t*, double_t*);
    bool    evalConstant(string_t, double_t*);
    bool    evalFunction(string_t, vdouble_t*, double_t*);
    bool    evalLogical(string_t, vdouble_t*, double_t*);
    bool    evalMath(string_t, vdouble_t*, double_t*);

   /**
    * Member Variables
    */

    bool               m_Parsed    = false;

    const vstring_t    m_WFunc     = {"sin","cos","tan","exp","log","abs","mod","if"};
    const vstring_t    m_WConst    = {"pi"};
    const vstring_t    m_OLogical  = {"&&","||","==","<",">",">=","<=","!=","<>"};
    const vstring_t    m_OMath     = {"+","-","*","/","^","_"};

    string_t           m_Equation;
    vstring_t          m_WVariable;
    std::vector<token> m_Tokens;
    std::vector<token> m_ParseTree;

};

} // End NameSpace

#endif
