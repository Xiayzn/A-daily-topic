/*
[编程|20分] 在字符串中找出连续最长的数字串
时间限制：C/C++ 1秒，其他语言 2秒
空间限制：C/C++ 32768K，其他语言 65536K
64bit IO Format: %lld
本题可使用本地IDE编码，不做跳出限制，编码后请点击“保存并调试”按钮进行代码提交。
题目描述
样例输出
输出123058789，函数返回值9
输出54761，函数返回值5
 
接口说明
函数原型：
   unsignedint Continumax(char** pOutputstr,  char* intputstr)
输入参数：
   char* intputstr  输入字符串；
输出参数：
   char** pOutputstr: 连续最长的数字串，如果连续最长的数字串的长度为0，应该返回空字符串；如果输入字符串是空，也应该返回空字符串；  
返回值：
  连续最长的数字串的长度
 
输入描述:
输入一个字符串。

输出描述:
输出字符串中最长的数字字符串和它的长度。如果有相同长度的串，则要一块儿输出，但是长度还是一串的长度

示例1
输入
abcd12345ed125ss123058789

输出
123058789,9
*/

#include <iostream>
#include <string>
using namespace std;
int main()
{  
    string str;
    while( cin>>str )
    {
        int i;
        int max = 0;
        string ss;
        string out;
        for(i = 0; i < str.size(); i++)
        {
            if(str[i] >= '0' &&str[i] <= '9')
            {
                ss += str[i];
                while(str[i+1] >= '0' &&str[i+1] <= '9')
                {
                    i++;
                    ss += str[i];
                }
                if(ss.size() > max)
                {
                    max = ss.size();
                    out = ss;                  
                }
                else if(ss.size() == max)
                    out += ss;
            }
            ss.clear();           
        }
        cout<<out<<','<<max<<endl;       
    }
    return 0;
}

//C语言写法
#include<stdio.h>
#include<string.h>
int main()
{
    char str[1000];
    int b[1000]={0};
    int i,j,k,len,cnt=0,cnt0=0,max=0;
    while(scanf("%s",&str)!=EOF)
    {
        cnt=0,cnt0=0,max=0,j=0;
        len=strlen(str);
        for(i=0;i<len;)
        {
            if((str[i]>='0')&&(str[i]<='9'))
            {
                while((str[i]>='0')&&(str[i]<='9'))
                {
                    cnt++;
                    i++;
                }
                if(cnt>max)
                    max=cnt;           
            }
            else
            {
                cnt=0;
                i++;
            }
        }
        for(i=0;i<len;)
        {
            if((str[i]>='0')&&(str[i]<='9'))
            {
                while((str[i]>='0')&&(str[i]<='9'))
                {
                    cnt0++;
                    i++;
                }
                if(cnt0==max)
                    b[j++]=i-max;  
            }
            else
            {
                cnt0=0;
                i++;
            }              
        }
        for(k=0;k<j;k++)
            for(i=b[k];i<b[k]+max;i++)
                printf("%c",str[i]);               
        printf(",");
        printf("%d\n",max);
    }
    return 0;
}
