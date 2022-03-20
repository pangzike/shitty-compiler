//
//  main.cpp
//  compiler
//
//  Created by 杨可 on 2022/3/3.
//

#include <iostream>
#include "scanner.hpp"

using namespace std;
int main(int argc, const char * argv[]) {
    //打开一个文件，读取其中的源程序
    char initial_project[10000];
    char token[20] = { 0 };
    int flag = -1, i;//初始化
    
    int code_pointer = 0;//源程序指针
    FILE *file_in, *file_out;
    
    //打开源程序
    if ((file_in = fopen("/Users/yangke/Desktop/shitty-compiler/compiler/compiler/rc.c", "r")) == NULL)
    {
        cout << "this file cannot be opened.\n";
        exit(0);
    }
    initial_project[code_pointer] = fgetc(file_in);
    
    while (initial_project[code_pointer] != EOF)
    {//将源程序读入resourceProject[]数组
        code_pointer++;
        initial_project[code_pointer] = fgetc(file_in);
    }

    fclose(file_in);
    cout << endl << "源程序为:" << endl;
    cout << initial_project << endl;
    //对源程序进行过滤
    filterResource(initial_project, code_pointer);
    cout << endl << "过滤之后的程序:" << endl;
    cout << initial_project << endl;
    code_pointer = 0;//从头开始读
    
    if ((file_out = fopen("/Users/yangke/Desktop/shitty-compiler/compiler/compiler/out.txt", "w+")) == NULL)
    {//打开记录文件
        cout << "this file cannot be opened.\n";
        exit(0);
    }
    while (flag != 0)
    {
        //启动扫描
        Scanner(flag, initial_project, token, code_pointer);
        if (flag == 100)
        {//标识符
            for (i = 0; i<1000; i++)
            {//插入标识符表中
                if (strcmp(itable[i], token) == 0)
                {//已在表中
                    break;
                }
                if (strcmp(itable[i], "") == 0)
                {//查找空间
                    strcpy(itable[i], token);
                    break;
                }
            }
            printf("(标识符  ,%s)\n", token);
            fprintf(file_out, "(标识符   ,%s)\n", token);
        }
        else if (flag >= 1 && flag <= 32)
        {//保留字
            printf("(%s   ,  --)\n", rwtable[flag - 1]);
            fprintf(file_out, "(%s   ,  --)\n", rwtable[flag - 1]);
        }
        else if (flag == 99)
        {//const 常数
            printf("(常数   ,   %s)\n", token);
            fprintf(file_out, "(常数   ,   %s)\n", token);
        }
        else if (flag >= 33 && flag <= 68)
        {
            printf("(%s   ,   --)\n", odtable[flag - 33]);
            fprintf(file_out, "(%s   ,   --)\n", odtable[flag - 33]);
        }
    }
    for (i = 0; i<100; i++)
    {//插入标识符表中
        if( 0 == strcmp(itable[i] , ""))
            break;
        printf("第%d个标识符：  %s\n", i + 1, itable[i]);
//        fprintf(file_out, "第%d个标识符：  %s\n", i + 1, itable[i]);
    }
    fclose(file_out);
    return 0;
}
