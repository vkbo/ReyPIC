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

    int           idCurr;
    int           idPrev  = MT_NONE;
    char          cPrev   = ' ';
    string_t      sBuffer = "";
    vector<lexer> vLexer;

    sEquation += " "; // Append a space to make sure last character is evaluated

    for(char cCurr : sEquation) {

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

        // If a new type was encountered, push the previous onto the lexer
        if(idCurr != idPrev) {
            if(idPrev != MT_NONE) {
                vLexer.push_back(lexer({.type=idPrev, .content=sBuffer, .value=0.0}));
            }
            sBuffer = "";
        }
        sBuffer += cCurr;

        // Set previous values for next loop
        idPrev = idCurr;
        cPrev  = cCurr;
    }

    // Clean up lexer and check for invalid entries
    for(auto lxItem : vLexer) {

        int    idType = MP_NONE;
        double dValue = 0.0;

        switch(lxItem.type) {
            case MT_OPERATOR:
                idType = validOperator(&lxItem.content);
                dValue = 0.0;
                break;
            case MT_WORD:
                idType = validWord(&lxItem.content);
                dValue = 0.0;
                break;
        }

        if(idType == MP_INVALID) {
            cout << "  Type Error" << endl;
        } else {
            m_Lexer.push_back(lexer({.type=idType, .content=lxItem.content, .value=dValue}));
        }
    }

    // Echo lexer for debug
    cout << endl;
    for(auto lxItem : m_Lexer) {
        cout << "  Type " << lxItem.type << " : Content " << lxItem.content << endl;
    }
    cout << endl;

    return true;
}

// ********************************************************************************************** //
//                                        Member Functions                                        //
// ********************************************************************************************** //

/**
 *  Function :: validOperator
 * ===========================
 *  Checks if string is a valid operator, and returns its type
 */

int Math::validOperator(string_t* sVar) {

    for(string_t sItem : m_OMath) {
        if(sItem == *sVar) {
            return MP_O_MATH;
        }
    }

    if(*sVar == "(") {
        return MP_O_LBRACK;
    }

    if(*sVar == ")") {
        return MP_O_RBRACK;
    }

    for(string_t sItem : m_OLogical) {
        if(sItem == *sVar) {
            return MP_O_LOGICAL;
        }
    }

    if(*sVar == ",") {
        return MP_O_SEPARATOR;
    }

    return MP_INVALID;
}

// ********************************************************************************************** //

/**
 *  Function :: validWord
 * =======================
 *  Checks if string is a valid word, and returns its type
 */

int Math::validWord(string_t* sVar) {

    for(string_t sItem : m_WVariable) {
        if(sItem == *sVar) {
            return MP_W_VARIABLE;
        }
    }

    for(string_t sItem : m_WFunc) {
        if(sItem == *sVar) {
            return MP_W_FUNC;
        }
    }

    for(string_t sItem : m_WConst) {
        if(sItem == *sVar) {
            return MP_W_CONST;
        }
    }

    if(*sVar == "if") {
        return MP_W_IF;
    }

    return MP_INVALID;
}

// ********************************************************************************************** //

// End Class Math
