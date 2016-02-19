/**
 *  ReyPIC – Math Source
 * ======================
 *  Loosely based on: http://www.codeproject.com/Articles/345888/How-to-write-a-simple-interpreter-in-JavaScript
 */

#include "clsMath.hpp"

using namespace std;
using namespace reypic;

// ********************************************************************************************** //

/**
 *  Class Constructor
 * ===================
 */

Math::Math() {

}

// ********************************************************************************************** //
//                                      Setters and Getters                                       //
// ********************************************************************************************** //

/**
 *  Set the Equation
 * ==================
 */

bool Math::setEquation(string_t sEquation) {

    // Append a space to make sure last character is evaluated
    m_Equation = sEquation + " ";

    bool okLexer  = eqLexer();
    bool okParser = eqParser();

    return (okLexer && okParser);
}

// ********************************************************************************************** //
//                                        Member Functions                                        //
// ********************************************************************************************** //

/**
 *  The Equation Lexer
 * ====================
 */

bool Math::eqLexer() {

    int           idCurr;
    int           idPrev  = MT_NONE;
    char          cPrev   = ' ';
    string_t      sBuffer = "";
    vector<token> vTokens;

    for(char cCurr : m_Equation) {

        // Get specific type
        idCurr = MT_NONE;
        if(isdigit(cCurr)) idCurr = MT_NUMBER;
        if(isalpha(cCurr)) idCurr = MT_WORD;
        if(ispunct(cCurr)) idCurr = MT_OPERATOR;

        // Numbers following characters are part of words
        if(idCurr == MT_NUMBER && idPrev == MT_WORD) idCurr = MT_WORD;
        // '.' is always part of a number
        if(cCurr == '.') idCurr = MT_NUMBER;
        // 'd' or 'e' following a number denotes exponent
        if((cCurr == 'd' || cCurr == 'e') && idPrev == MT_NUMBER) {
            idCurr = MT_NUMBER;
        }
        // '-' after an 'e' or 'd' that is a number, is also a part of a number
        if(cCurr == '-' && (cPrev == 'd' || cPrev == 'e') && idPrev == MT_NUMBER) {
            idCurr = MT_NUMBER;
        }
        // Check if operator is actually a separataor
        if(cCurr == '(' || cCurr == ')' || cCurr == ',') {
            idCurr = MT_SEPARATOR;
        }

        // If a new type was encountered, push the previous onto the lexer
        if(idCurr != idPrev) {
            if(idPrev != MT_NONE) {
                vTokens.push_back(token({.type=idPrev, .content=sBuffer, .value=0.0}));
            }
            sBuffer = "";
        }
        sBuffer += cCurr;

        // Set previous values for next loop
        idPrev = idCurr;
        cPrev  = cCurr;
    }

    // Clean up lexer and check for invalid entries
    idPrev = MP_NONE;
    for(auto tItem : vTokens) {

        int    idType = MP_NONE;
        double dValue = 0.0;

        switch(tItem.type) {
            case MT_OPERATOR:
                idType = validOperator(&tItem.content);
                dValue = 0.0;
                break;
            case MT_NUMBER:
                idType = validNumber(&tItem.content, &tItem.value);
                dValue = tItem.value;
                break;
            case MT_WORD:
                idType = validWord(&tItem.content);
                dValue = 0.0;
                break;
            case MT_SEPARATOR:
                idType = validSeparator(&tItem.content);
                dValue = 0.0;
                break;
        }

        if(idType == MP_INVALID || idType == idPrev) {
            printf("  Math Error: Unknown entry '%s'\n", tItem.content.c_str());
            return false;
        } else {
            m_Tokens.push_back(token({.type=idType, .content=tItem.content, .value=dValue}));
        }

        idPrev = idType;
    }

    // Echo lexer for debug
    cout << endl;
    for(auto tItem : m_Tokens) {
        cout << "  Type " << tItem.type << " : Content " << tItem.content << " : Value " << tItem.value << endl;
    }
    cout << endl;

    return true;
}

// ********************************************************************************************** //

/**
 *  The Equation Parser
 * =====================
 *  Using the Shunting-yard algorithm
 *  https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 */

bool Math::eqParser() {

    vector<token> vtOutput;
    vector<token> vtStack;

    for(auto tItem : m_Tokens) {

        switch(tItem.type) {

            case MP_NUMBER:
                vtOutput.push_back(tItem);
                break;

            case MP_VARIABLE:
                vtOutput.push_back(tItem);
                break;

            case MP_CONST:
                vtOutput.push_back(tItem);
                break;

            case MP_FUNC:
                vtStack.insert(vtStack.begin(), tItem);
                break;

            case MP_COMMA:
                break;

        }

    }

    return true;
}

// ********************************************************************************************** //

/**
 *  Function :: validOperator
 * ===========================
 *  Checks if string is a valid operator, and returns its type
 */

int Math::validOperator(string_t* pVar) {

    for(string_t sItem : m_OMath) {
        if(sItem == *pVar) {
            return MP_MATH;
        }
    }

    for(string_t sItem : m_OLogical) {
        if(sItem == *pVar) {
            return MP_LOGICAL;
        }
    }

    return MP_INVALID;
}

// ********************************************************************************************** //

/**
 *  Function :: validWord
 * =======================
 *  Checks if string is a valid word, and returns its type
 */

int Math::validWord(string_t* pVar) {

    for(string_t sItem : m_WVariable) {
        if(sItem == *pVar) {
            return MP_VARIABLE;
        }
    }

    for(string_t sItem : m_WFunc) {
        if(sItem == *pVar) {
            return MP_FUNC;
        }
    }

    for(string_t sItem : m_WConst) {
        if(sItem == *pVar) {
            return MP_CONST;
        }
    }

    return MP_INVALID;
}

// ********************************************************************************************** //

/**
 *  Function :: validNumber
 * =========================
 *  Checks if string is a valid number, and returns its type
 */

int Math::validNumber(string_t* pVar, double* pValue) {

    try {
        *pValue = stof(*pVar);
        return MP_NUMBER;
    } catch(...) {
        *pValue = 0.0;
        return MP_INVALID;
    }
}

// ********************************************************************************************** //

/**
 *  Function :: validSeparator
 * ============================
 *  Checks if string is a valid separataor, and returns its type
 */

int Math::validSeparator(string_t* pVar) {

    if(*pVar == "(") {
        return MP_LBRACK;
    }

    if(*pVar == ")") {
        return MP_RBRACK;
    }

    if(*pVar == ",") {
        return MP_COMMA;
    }

    return MP_INVALID;
}

// ********************************************************************************************** //

/**
 *  Function :: precedenceLogical
 * ===============================
 *  Returns precedence and associativity of operator
 */

void Math::precedenceLogical(string_t sOperator, int* pPrecedence, int* pAssoc) {

    if(sOperator == "&&") {
        *pPrecedence = 3;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "||") {
        *pPrecedence = 2;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "==") {
        *pPrecedence = 9;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "<") {
        *pPrecedence = 9;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == ">") {
        *pPrecedence = 9;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == ">=") {
        *pPrecedence = 9;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "<=") {
        *pPrecedence = 9;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "!=") {
        *pPrecedence = 9;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "<>") {
        *pPrecedence = 9;
        *pAssoc = ASSOC_L;
    }

    return;
}

// ********************************************************************************************** //

/**
 *  Function :: precedenceMath
 * ============================
 *  Returns precedence and associativity of operator
 */

void Math::precedenceMath(string_t sOperator, int* pPrecedence, int* pAssoc) {

    if(sOperator == "^") {
        *pPrecedence = 4;
        *pAssoc = ASSOC_R;
    } else
    if(sOperator == "*") {
        *pPrecedence = 3;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "/") {
        *pPrecedence = 3;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "+") {
        *pPrecedence = 2;
        *pAssoc = ASSOC_L;
    } else
    if(sOperator == "-") {
        *pPrecedence = 2;
        *pAssoc = ASSOC_L;
    }

    return;
}

// ********************************************************************************************** //

// End Class Math
