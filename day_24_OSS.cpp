//无线OSS————高精度整数加法

#include<string>
#include<iostream>
using namespace std;

//字符串加法
string add(string num1, string num2){
    string res = "";
    if(num1.size() > num2.size())
        num2 = string(num1.size() - num2.size(), '0') + num2;
    else
        num1 = string(num2.size() - num1.size(), '0') + num1;//去掉前导后补齐两个字符串
    
    int carry = 0;
    for(int i = num1.size() - 1; i >= 0; i--){
        char temp = (num1[i] - '0' + num2[i] - '0' + carry) % 10 + '0';
        res = temp + res;
        carry = (num1[i] - '0' + num2[i] - '0' + carry) / 10;
    }
    if(carry)
        res = '1' + res;
    return res;
}

//减法，主函数处理后保证结果是正数
string sub(string num1, string num2){
    string res = "";
    int borrow = 0;
    int i =num1.size() - 1;
    
    for( ; i >= 0; i--){
        int op1 = (num1[i] - borrow >= num2[i]) ? (num1[i] - borrow - '0') : (10 + num1[i] - borrow - '0');
        int op2 = num2[i] - '0';
        char temp = op1 - op2 + '0';
        res = temp + res;
        borrow = num1[i] - borrow<num2[i];
    }
    
    while(res[++i] == '0');//去掉前导0
    res = res.substr(i);
    return res;
}

int main(){
    string num1;
    string num2;
    
    while(cin >> num1 >> num2){
        if(isdigit(num1[0]) && isdigit(num2[0]))
            cout << add(num1, num2) << endl;
        else if(!isdigit(num1[0]) && !isdigit(num2[0])){
            num1 = num1.substr(1);
            num2 = num2.substr(1);
            cout << "-" + add(num1, num2) << endl;
        }
        else if(isdigit(num1[0]) && !isdigit(num2[0])){
            //一正一负时先去掉前导-，然后补齐再比较操作数的大小
            num2 = num2.substr(1);
            
            if(num1.size() > num2.size())
                num2 = string(num1.size() - num2.size(), '0') + num2;//取代哦前导后补齐两个字符串
            else
                num1 = string(num2.size() - num1.size(), '0') + num1;//由于要判断num1,num2的大小，所有要先补齐再判断
            
            if(num1 > num2)
                cout << sub(num1, num2) << endl;//如123，-57 ，去掉前导 -  然后调用减法函数
            else
                cout << '-' + sub(num2, num1) <<endl;//如23， -157，去掉前导 -,交换位置后调用减法函数再加上前导 -
        }
        else{
            num1 = num1.substr(1);
            
            if(num1.size() > num2.size())
                num2 = string(num1.size() - num2.size(), '0') + num2;
            else
                num1 = string(num2.size() - num1.size(), '0') + num1;//去掉前导后补齐两个字符串
            
            if(num1 > num2)
                cout << '-' + sub(num1, num2) << endl;//如/-123,57
            else
                cout << sub(num2, num1) <<endl;//如 -23,157
        }
    }
}
