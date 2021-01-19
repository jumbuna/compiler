#include "variables.h"

static char *vars[] = {"v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7"};

static int varsLen = 8;

static char **var = vars;

char *newvar() {
    if(var >= (vars+varsLen)) {
        return 0;
    }
    return *var++;
}

void freevar(char *t) {
    if(var > vars) {
        *--var = t;   
    }
}