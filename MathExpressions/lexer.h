#include <stdio.h>

/* Log Errors */
#define logError(...) \
    fprintf(stderr, __VA_ARGS__);

/**
 * Token Set
 */
enum Token {
    EOI,    /* 0 */
    SEMI,   /* ; */
    PLUS,   /* + */
    TIMES,  /* * */
    NUM,    /*   */
    LP,     /* ( */
    RP,     /* ) */
};

/**
 * Return boolean value indicating whether the given
 * Token matches the last token identified.
 */
extern int match(enum Token);

/**
 * Get Next Token from Input stream 
 */
extern void advance();

/**
 * Current Token's lexeme
 */
extern char *yyText;

/**
 * Length of yyText
 */
extern int yyLength;

/**
 * Current line in the input stream
 */
extern int yyLineno;

/**
 * Print Current token as a string
 */
extern void printtoken();