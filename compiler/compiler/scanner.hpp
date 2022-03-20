//
//  scanner.hpp
//  compiler
//
//  Created by 杨可 on 2022/3/10.
//

#ifndef scanner_hpp
#define scanner_hpp

#include <iostream>
#include <string>
static char rwtable[32][10] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
    };

static char odtable[36][5] = {
    "+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
    "!=", ";", "(", ")", "^", ",", "\"", "\'", "#", "&",
    "&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
    "}", "\\", ".", "\?", ":", "!"
};

static char itable[1000][50] = { "" };//标识符表

// 查找保留字
int IsRw(char rwtable[][10], char s[]);

// 判断是否为字符
bool IsLetter(char letter);

// 判断是否为数字
bool IsDigit(char digit);

// 编译预处理，取出无用的字符和注释
void filterResource(char r[], int code_pointer);

void Scanner(int &flag, char initial_program[], char token[], int &code_pointer);

#endif /* scanner_hpp */
