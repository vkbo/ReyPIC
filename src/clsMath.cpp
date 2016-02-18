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

    bool okLexer = eqLexer();
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
    for(auto lxItem : vTokens) {

        int    idType = MP_NONE;
        double dValue = 0.0;

        switch(lxItem.type) {
            case MT_OPERATOR:
                idType = validOperator(&lxItem.content);
                dValue = 0.0;
                break;
            case MT_NUMBER:
                idType = validNumber(&lxItem.content, &lxItem.value);
                dValue = lxItem.value;
                break;
            case MT_WORD:
                idType = validWord(&lxItem.content);
                dValue = 0.0;
                break;
            case MT_SEPARATOR:
                idType = validSeparator(&lxItem.content);
                dValue = 0.0;
                break;
        }

        if(idType == MP_INVALID || idType == idPrev) {
            printf("  Math Error: Unknown entry '%s'\n", lxItem.content.c_str());
            return false;
        } else {
            m_Tokens.push_back(token({.type=idType, .content=lxItem.content, .value=dValue}));
        }

        idPrev = idType;
    }

    // Echo lexer for debug
    cout << endl;
    for(auto lxItem : m_Tokens) {
        cout << "  Type " << lxItem.type << " : Content " << lxItem.content << " : Value " << lxItem.value << endl;
    }
    cout << endl;

    return true;
}

// ********************************************************************************************** //

/**
 *  The Equation Parser
 * =====================
 */

bool Math::eqParser() {

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

// End Class Math
