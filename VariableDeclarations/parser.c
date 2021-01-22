#include <string.h>
#include <stdio.h>
#include <ctype.h>

/**
 * A SMALL PASER THAT RECOGNIZES C VARIABLE DECLARATIONS.
 *
 * LIMITATIONS:
 * - restrict Qualifier is not supported.
 * - duplicate qualifiers are allowed.
 * - Only supports int, char, short, long, double & float types.
 * - Assignment not supported.
 *
 * @author jumbuna
 * ©2021
 */

/** Tokens */
enum Token {
    MODIFIER, /* signed, unsigned */
    QUALIFIER, /* volatile, const */
    DATATYPE, /* int, char, short, long, double & float */
    IDENTIFIER, /* variable name*/
    EOI, /* End of input*/
    SEMI, /* ; */
};

/** Lexeme of last token scanned */
char *yytext = "";
/** Length of yytext */
int yylen = 0;
/** Current line being processed */
int yyline = 0;

/** Determine the token a lexeme belongs to */
static enum Token stringstoken(char *lexeme) {
    /* The complexity of this routine can be reduced to linear if we use
     * a TRIE/RADIX TREE instead of strcmp
     */
    if(!strcmp("signed", lexeme) || !strcmp("unsigned", lexeme)) return MODIFIER;
    
    if(!strcmp("volatile", lexeme) || !strcmp("const", lexeme)) return QUALIFIER;

    if(
        !strcmp("int", lexeme) ||
        !strcmp("float", lexeme) ||
        !strcmp("char", lexeme) ||
        !strcmp("double", lexeme) ||
        !strcmp("short", lexeme) ||
        !strcmp("long", lexeme)
    ) return DATATYPE;

    return IDENTIFIER;
}

/** Lexer */
static enum Token lex() {
    /* Line buffer */
    static char buffer[128];
    /* Lookahead character */
    char *current;
    /* Skip past current lexeme */
    current = yytext + yylen;
    while(1) {
        if(!*current) {
            /*  Get line from stdin */
            printf(">>> ");
            current = buffer;
            if(fgets(buffer, 128, stdin) == 0) {
                current = 0;
                return EOI;
            }
            /* One more line read */
            ++yyline;
        }
        /* Skip white spaces/blank lines */
        while(isspace(*current)) {
            ++current;
        }
        /* Scan for next token */
        for(; *current; current++) {
            /* Minimum lenght of a lexeme */
            yylen = 1;
            yytext = current;
            switch(*current) {
                case ';' : return SEMI;
                case '\n' :
                case '\t' :
                case ' ' : break;
                default: {
                    /* All Token lexemes start with an alphabet. An identifier may also
                       start with an underscore
                    */
                    if(!isalpha(*current) || *current != '_') {
                        printf("Lexer error: Unexpected character `%c` on line %d\n", *current, yyline);
                        /* Mimic C's error highlighting
                         *  int error%;
                         *  ~~~~~~~~~^
                         */
                        printf("\t%s\n", buffer);
                        printf("\t");
                        char *temp = buffer;
                        while(temp != current) {
                            printf("~");
                            temp++;
                        }
                        printf("^\n");
                        break;
                    }
                    yytext = current;
                    /* An identifier's lexeme may have digits */
                    while(isalnum(*current) || *current == '_') {
                        ++current;
                    }
                    yylen = current-yytext;
                    char temp = *current;
                    /* Temporary termination */
                    *current = 0;
                    /* id | modifier| qualifier | type */
                    enum Token t = stringstoken(yytext);
                    /* Restore */
                    *current = temp;
                    return t;
                }
            }
        }
    }
}
/** Last token scanned */
enum Token Lookahead = -1;

/** Update Lookahead with next token */
void advance() {
    Lookahead = lex();
}

/** Given Token matches Lookahead*/
_Bool match(enum Token t) {
    if(Lookahead == -1) {
        advance();
    }
    return Lookahead == t;
}

/** Parse a declaration */
void declaration() {
    /* set to true if modifier is found */
    _Bool foundmodifier;
    /* intialized to false for a single declaration */
    foundmodifier = 0;
    /* Qualifiers/modifiers/datatype appear before identifier */
    while(match(QUALIFIER) || match(MODIFIER) || match(DATATYPE)) {
        if(match(MODIFIER)) {
            !foundmodifier ? foundmodifier = 1 :
                printf("Parse Error: Multiple modifiers in declaration `%.*s`\n", yylen, yytext);
        }
        advance();
    }
    /* Next token should be identifier */
    if(!match(IDENTIFIER)) {
        printf("Parse Error: Declaration missing a name on line %d\n", yyline);
    }
    advance();
}

/** Main parser routine */
void parser() {
    while(!match(EOI)) {
        /* get a declaration */
        declaration();
        if(!match(SEMI)) {
            printf("Parse error: Expected `;` on line %d\n", yyline);
        }
        advance();
    }
}

int main() {
    parser();
}