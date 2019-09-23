#include<bits/stdc++.h>
using namespace std;
#include"DataType.h"
#include"Function.h"
#include"question1.h"
#include"question2try.h"
#include"question2.h"
//测试问题1(1)
inline void test11(){
    srand(time(0));
    int err=0;
    for(int i=0;i<10000;++i){
        StarMap s1,s2,s3,ret;
        double a1,a2,a3;
        makep1(s1,s2,s3,a1,a2,a3,ret);
        StarMap ans=calp11(s1,s2,s3,a1,a2,a3,f1);
        if(i<5){
            printf("i=%d\n",i);
            printf("s1:");s1.printfx();
            printf("s2:");s2.printfx();
            printf("s3:");s3.printfx();
            printf("a1=%f a2=%f a3=%f f=%f\n",a1,a2,a3,f1);
            printf("correct answer:");ret.printfx();
            printf("calculate answer:");ans.printfx();
        }
        if(fabs(ans.ew-ret.ew)>1e-9||fabs(ans.ns-ret.ns)>1e-9)++err;
    }
    printf("...\n...\n...\n\ntest:1000 error:%d\n\n\n",err);
}
//测试问题1(2)
inline void test12(){
    srand(time(0));
    int err=0;
    for(int i=0;i<10000;++i){
        StarMap s1,s2,s3,ret;
        double a1,a2,a3;
        makep1(s1,s2,s3,a1,a2,a3,ret);
        StarMap ans=calp12(s1,s2,s3,a1,a2,a3);
        if(i<5){
            printf("i=%d\n",i);
            printf("s1:");s1.printfx();
            printf("s2:");s2.printfx();
            printf("s3:");s3.printfx();
            printf("a1=%f a2=%f a3=%f\n",a1,a2,a3);
            printf("correct answer:");ret.printfx();
            printf("calculate answer:");ans.printfx();
        }
        if(fabs(ans.ew-ret.ew)>1e-9||fabs(ans.ns-ret.ns)>1e-9)++err;
    }
    printf("...\n...\n...\n\ntest:10000 error:%d\n\n\n",err);
}
//测试问题2
inline void test2(int ch){
    for(int id=1;id<=8;++id){
        printf("id=%d\n",id);
        if(ch==1)calp2try1(xt[id],cxt[id],id<7?f1:f2);
        else if(ch==2)calp2try2(xt[id],cxt[id],id<7?f1:f2);
        else if(ch==3)calp2try3(xt[id],cxt[id],id<7?f1:f2);
        else calp2(xt[id],cxt[id],id);
    }
}
int main(){
    printf("loading data...\n");
    read_map();
    read_xt();
    printf("load finish.\n");
    printf("initializing...\n");
    init1();
    printf("initialize finish.\n");
    while(1){
        printf("please choose a function:\n1.problem 1 (1) test\n2.problem 1 (2) test\n3.problem 2 result\n4.problem 2 other way try 1\n5.problem 2 other way try 2\n6.problem 2 other way try 3\n7.exit\n>");
        string inp;
        cin>>inp;
        if(inp==string("1")){system("cls");test11();system("pause");}
        else if(inp==string("2")){system("cls");test12();system("pause");}
        else if(inp==string("3")){system("cls");test2(4);system("pause");}
        else if(inp==string("4")){system("cls");test2(1);system("pause");}
        else if(inp==string("5")){system("cls");test2(2);system("pause");}
        else if(inp==string("6")){system("cls");test2(3);system("pause");}
        else if(inp==string("7"))break;
        system("cls");
    }
    return 0;
}
