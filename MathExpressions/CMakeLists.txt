cmake_minimum_required(VERSION 3.0)

project(ExpressionCompiler
        VERSION 1.0
        DESCRIPTION "Minimal compiler that recognizes mathematical expressions"
        LANGUAGES C
)

add_executable(expressions main.c lexer.c parser.c variables.c)