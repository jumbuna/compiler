#include "parser.h"
#include "lexer.h"
#include "variables.h"
#include <stdio.h>

char *expression(void);
char *expressionprime(void);
char *factor(void);
char *term(void);
char *termprime(void);

/**
 * Statement ::= <Expression> ; <Statement>
 */
void statements(void) {
    /* results of an expression */
    char *tempvar;
    while(!match(EOI)) {
        /* Read An expression */
        tempvar = expression();
        /* Multiple expressions are separated by semicolon */
        if(match(SEMI)) {
            advance();
        } else {
            logError("Error line %d: Expected `;`.\n", yyLineno);
        }
        freevar(tempvar);
    }
}

/**
 * Expression ::= <Term> <ExpressionPrime>
 */
char *expression() {
    char *tempvar1, *tempvar2;
    tempvar1 = term();
    tempvar2 = expressionprime();
    if(tempvar2 != NULL) {
        printf("%s += %s\n", tempvar1, tempvar2);
        freevar(tempvar2);
    }
    return tempvar1;
}

/**
 * ExpressionPrime ::= + <Term> <ExpressionPrime>
 */
char *expressionprime() {
    char *tempvar = NULL;
    if(match(PLUS)) {
        advance();
        char *tempvar2;
        tempvar = term();
        tempvar2 = expressionprime();
        if(tempvar2 != NULL) {
            printf("%s += %s\n", tempvar, tempvar2);
            freevar(tempvar2);
        }
    }
    return tempvar;
}

/**
 * Term ::= <Factor> <TermPrime>
 */
char *term() {
    char *tempvar, *tempvar2;
    tempvar = factor();
    tempvar2 = termprime();
    if(tempvar2 != NULL) {
        printf("%s *= %s\n", tempvar, tempvar2);
        freevar(tempvar2);
    }
    return tempvar;
}

/**
 * Factor ::= (<Expression>)
 * Factor ::= <Number>
 */
char *factor() {
    char *tempvar;
    if(match(LP)) {
        advance();
        tempvar = expression();
        if(!match(RP)) {
            logError("Error line %d: Missing closing `)`.\n", yyLineno);
        }
        advance();
    } else if(match(NUM)) {
        tempvar = newvar();
        if(tempvar == NULL) {
        logError("Expression is too complex\n");
        return NULL;
    }
        printf("%s = %.*s\n", tempvar, yyLength, yyText);
        advance();
    } else {
        logError("Error line %d: Unexpected character `%c`.\n", yyLineno, *yyText);
        advance();
    }
    return tempvar;
}

/**
 * TermPrime ::= * <Factor> <TermPrime>
 */
char *termprime() {
    char *tempvar = NULL;
    if(match(TIMES)) {
        advance();
        tempvar = factor();
        char *tempvar2;
        tempvar2 = termprime();
        if(tempvar2 != NULL) {
            printf("%s *= %s\n", tempvar, tempvar2);
            freevar(tempvar2);
        }
    }
    return tempvar;
}