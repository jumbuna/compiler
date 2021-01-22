cmake_minimum_required(VERSION 3.0)

project(Declaration
        VERSION 1.0
        DESCRIPTION "A small parser that recognizes c variable declarations"
        LANGUAGES C
)

add_executable(cdeclaration parser.c)