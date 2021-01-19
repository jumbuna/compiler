#include "lexer.h"
#include <stdio.h>
#include <ctype.h>

char *yyText = "";
int yyLength = 0;
int yyLineno = 0;

/**
 * Last token read
 */
static enum Token Lookahead = -1;

static enum Token lex() {
    static char buffer[256];
    static int bufferSize = 256;
    char *current;

    /* Move past current lexeme */
    current = yyText + yyLength;

    /* get Next Token */
    while(1) {
        while(!*current) {
            current = buffer;
            /* Read line from stdin into buffer */
            printf(">>> ");
            if(!fgets(buffer, bufferSize-1, stdin)) {
                *current = '\0';
                return EOI;
            }
            ++yyLineno;
            /* Skip whitespaces or empty lines */
            while(isspace(*current)) {
                ++current;
            }
        }
        for(; *current; ++current) {
            yyText = current;
            yyLength = 1;
            switch(*current) {
                case ';' : return SEMI;
                case '+' : return PLUS;
                case '*' : return TIMES;
                case '(' : return LP;
                case ')' : return RP;
                /* Skip whiteSpaces */
                case '\n':
                case '\t':
                case ' ' : break;
                default  : {
                    if(!isdigit(*current)) {
                        logError(
                            "Error Line %d: Ignoring unrecognized character %c.\n",
                         yyLineno, *current);
                        break;
                    }
                    while(isdigit(*current)) {
                        ++current;
                    }
                    yyLength = current - yyText;
                    return NUM;
                }
            }
        }
    }
}

int match(enum Token token) {
    if(Lookahead == -1) {
        Lookahead = lex();
    }
    return Lookahead == token;
}

void advance() {
    Lookahead = lex();
}

void printtoken() {
    char *tokenname;
    switch (Lookahead) {
    case EOI: tokenname = "EOI";break;
    case LP: tokenname = "LP";break;
    case RP: tokenname = "RP";break;
    case PLUS: tokenname = "PLUS";break;
    case TIMES: tokenname = "TIMES";break;
    case NUM: tokenname = "NUM";break;
    case SEMI: tokenname = "SEMI";break;
    default: tokenname = "UNKNWN";
    }
    printf("%s\n", tokenname);
}