//
//  scanner.cpp
//  compiler
//
//  Created by 杨可 on 2022/3/10.
//

#include "scanner.hpp"

using namespace std;

int IsRw(char rwtable[][10], char s[])
{
    for (int i = 0; i < 32; i++)
    {
        if (strcmp(rwtable[i], s) == 0)
        {//若成功查找，则返回种别码
            return i + 1;//返回种别码
        }
    }
    return -1;//否则返回-1，代表查找不成功，即为标识符
}

bool IsLetter(char l)
{
    if ((l >= 'a'&&l <= 'z') || (l >= 'A'&&l <= 'Z')|| l=='_')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool IsDigit(char d)
{
    if (d >= '0'&&d <= '9')
    {
        return true;
    }
    else
    {
        return false;
    }
}

void filterResource(char r[], int code_pointer)
{
    char tempString[10000];
    int count = 0;
    for (int i = 0; i <= code_pointer; i++)
    {
        if (r[i] == '/'&&r[i + 1] == '/')
        {//若为单行注释“//”,则去除注释后面的东西，直至遇到回车换行
            for(;r[i] != '\n';i++);
        }
        if (r[i] == '/'&&r[i + 1] == '*')
        {//若为多行注释“/* 。。。*/”则去除该内容
            for(i = i+2;r[i] != '*' || r[i + 1] != '/';i++ )
            {
                if (r[i] == EOF)
                {
                    cout << "注释出错，没有找到 */，程序结束！！！\n";
                    exit(0);
                }
            }
            i += 2;//跨过“*/”
        }
        if (r[i] != '\n'&&r[i] != '\t'&&r[i] != '\v'&&r[i] != '\r')
        {//若出现无用字符，则过滤；否则加载
            tempString[count++] = r[i];
        }
    }
    tempString[count] = '\0';
    strcpy(r, tempString);//产生净化之后的源程序
}



void Scanner(int &flag, char initial_program[], char token[], int &code_pointer)
{//根据DFA的状态转换图设计
    int i, count = 0;//count用来做token[]的指示器，收集有用字符
    char ch;//当前字符
    ch = initial_program[code_pointer];
    while (ch == ' ')
    {//过滤空格，防止程序因识别不了空格而结束
        code_pointer++;
        ch = initial_program[code_pointer];
    }
    for (i = 0; i<20; i++)
    {//每次收集前先清零
        token[i] = '\0';
    }
    if (IsLetter(initial_program[code_pointer]))
    {//开头为字母
        token[count++] = initial_program[code_pointer];//收集
        code_pointer++;//下移
        while (IsLetter(initial_program[code_pointer]) || IsDigit(initial_program[code_pointer]))
        {//后跟字母或数字
            token[count++] = initial_program[code_pointer];//收集
            code_pointer++;//下移
        }//多读了一个字符既是下次将要开始的指针位置
        token[count] = '\0';
        flag = IsRw(rwtable, token);//查表找到种别码
        if (flag == -1)
        {//若不是保留字则是标识符
            flag = 100;//标识符种别码
        }
        return;
    }
    else if (IsDigit(initial_program[code_pointer]))
    {//首字符为数字
        while (IsDigit(initial_program[code_pointer]))
        {//后跟数字
            token[count++] = initial_program[code_pointer];//收集
            code_pointer++;
        }//多读了一个字符既是下次将要开始的指针位置
        token[count] = '\0';
        flag = 99;//常数种别码
    }
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ';' || ch == '(' || ch == ')' || ch == '^'|| ch == ',' || ch == '\"' || ch == '\'' || ch == '~' || ch == '#' || ch == '%' || ch == '['|| ch == ']' || ch == '{' || ch == '}' || ch == '\\' || ch == '.' || ch == '\?' || ch == ':')
    {//若为运算符或者界符，查表得到结果
        token[0] = initial_program[code_pointer];
        token[1] = '\0';//形成单字符串
        for (i = 0; i<36; i++)
        {//查运算符界符表
            if (strcmp(token, odtable[i]) == 0)
            {
                flag = 33 + i;//获得种别码，使用了一点技巧，使之呈线性映射
                break;//查到即推出
            }
        }
        code_pointer++;//指针下移，为下一扫描做准备
        return;
    }
    else  if (initial_program[code_pointer] == '<')
    {// 是<<=,<<
        code_pointer++;//后移，超前搜索
        if (initial_program[code_pointer] == '=')
        {
            flag = 38;
        }
        else if (initial_program[code_pointer] == '<')
        {//左移
            code_pointer--;
            flag = 58;
        }
        else
        {
            code_pointer--;
            flag = 37;
        }
        code_pointer++;//指针下移
        return;
    }
    else  if (initial_program[code_pointer] == '>')
    {//>,>=,>>
        code_pointer++;
        if (initial_program[code_pointer] == '=')
        {
            flag = 40;
        }
        else if (initial_program[code_pointer] == '>')
        {
            flag = 59;
        }
        else
        {
            code_pointer--;
            flag = 39;
        }
        code_pointer++;
        return;
    }
    else  if (initial_program[code_pointer] == '=')
    {//=.==
        code_pointer++;
        if (initial_program[code_pointer] == '=')
        {
            flag = 42;
        }
        else
        {
            code_pointer--;
            flag = 41;
        }
        code_pointer++;
        return;
    }
    else  if (initial_program[code_pointer] == '!')
    {//!,!=
        code_pointer++;
        if (initial_program[code_pointer] == '=')
        {
            flag = 43;
        }
        else
        {
            flag = 68;
            code_pointer--;
        }
        code_pointer++;
        return;
    }
    else  if (initial_program[code_pointer] == '&')
    {//&,&&
        code_pointer++;
        if (initial_program[code_pointer] == '&')
        {
            flag = 53;
        }
        else
        {
            code_pointer--;
            flag = 52;
        }
        code_pointer++;
        return;
    }
    else  if (initial_program[code_pointer] == '|')
    {//|,||
        code_pointer++;
        if (initial_program[code_pointer] == '|')
        {
            flag = 55;
        }
        else
        {
            code_pointer--;
            flag = 54;
        }
        code_pointer++;
        return;
    }
    else  if (initial_program[code_pointer] == EOF)
    {//结束符
        flag = 0;//种别码为0
    }
    else
    {//不能被以上词法分析识别，则出错。
        printf("error：there is no exist %c \n", ch);
        exit(0);
    }
}
