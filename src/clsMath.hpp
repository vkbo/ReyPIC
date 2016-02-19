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

    void setVariables(vstring_t);
    bool setEquation(string_t);

   /**
    * Methods
    */

    bool Eval(vdouble_t, double*);

   /**
    * Properties
    */

private:

   /**
    * Structs
    */

    struct token {
        int      type;
        string_t content;
        double   value;
    };

   /**
    * Member Functions
    */

    bool eqLexer();
    bool eqParser();

    int  validOperator(string_t*);
    int  validWord(string_t*);
    int  validNumber(string_t*, double*);
    int  validSeparator(string_t*);

    void precedenceLogical(string_t, int*, int*);
    void precedenceMath(string_t, int*, int*);

    bool evalVariable(string_t, vdouble_t*, double*);
    bool evalConstant(string_t, double*);
    bool evalFunction(string_t, vdouble_t*, double*);
    bool evalLogical(string_t, vdouble_t*, double*);
    bool evalMath(string_t, vdouble_t*, double*);

   /**
    * Member Variables
    */

    const vstring_t    m_WFunc     = {"sin","cos","tan","exp","log","abs","mod","if"};
    const vstring_t    m_WConst    = {"pi"};
    const vstring_t    m_OLogical  = {"&&","||","==","<",">",">=","<=","!=","<>"};
    const vstring_t    m_OMath     = {"+","-","*","/","^"};

    string_t           m_Equation;
    vstring_t          m_WVariable;
    std::vector<token> m_Tokens;
    std::vector<token> m_ParseTree;

};

} // End NameSpace

#endif
