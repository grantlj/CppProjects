
//IFNDEF DEFINE ENDIF 是一种用作flag的宏定义，为了防止出现多重include，
//我们要实现判断一下有没有include过。
//IFNDEF：如果没有定义过MYSWAP_H_，那么定义MYSWAP_H_，MYSWAP_H_的内容为以下的代码片段。
//模板类的申明和实现目前只支持在同一个文件中！！！！！！！！
#ifndef MYSWAP_H_
#define MYSWAP_H_

void myswap(int& a, int& b);


#endif