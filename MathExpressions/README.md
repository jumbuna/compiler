# Math Expressions

A simple compiler that recognizes and generates intermediate code for  simple mathematical expression containing the sum and product operations.

## compile
```bash
$ cd MathExpressions
$ cmake -B build
$ cmake --build build
```
## Run
```bash
$ build/expressions
```

## Example
1.
```bash
$ build/expressions
>>> 1+2;
v0 = 1
v1 = 2
v0 += v1
```
2.
```bash
$ build/expressions
>>> 1+2*3*5*6+8+(2*9+10);
v0 = 1
v1 = 2
v2 = 3
v3 = 5
v4 = 6
v3 *= v4
v2 *= v3
v1 *= v2
v2 = 8
v4 = 2
v5 = 9
v4 *= v5
v5 = 10
v4 += v5
v2 += v3
v1 += v2
v0 += v1
```
3.
```bash
$ build/expressions
>>> 1+2*(7;
v0 = 1
v1 = 2
v3 = 7
Error line 5: Missing closing `)`.
```

