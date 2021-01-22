# VARIABLE DECLARATION
A small parser that recognizes c variable declarations.

## Compile
```bash
$ cd VariableDeclarations
$ cmake -B build
$ cmake --build build
```

## Run
```bash
$ cd build
$ ./cdeclaration
```

> <b> NOTE: READ THE COMMENT AT THE BEGINNING OF <i>parser.c</i> TO SEE SOME OF THE LIMITATIONS PRESENT IN THE PARSER. </b>

## Examples
1.
```bash
$ ./cdeclaration
>>> int x;
>>> char volatile point;
>>> signed unsigned int v;
Parse Error: Multiple modifiers in declaration `unsigned`
>>> const volatile x;
>>> int t;
>>> double d h;
Parse error: Expected `;` on line 6
Parse Error: Declaration missing a name on line 6
>>> 
```

> Note: Valid declarations are silently accepted.

