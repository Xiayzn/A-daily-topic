//只有自测通过，没有通过所有的用例


#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main(){
    string str;
    getline(cin, str);
    //每次统计的数字的个数
    int maxCount = 0;
    //存储每个连续的字符串
    vector<string> v;
    for(int i = 0; i < str.length(); i++){
        int count = 0;
        //找到有数字出现的地方
        while(!isdigit(str[i]) && i < str.length()){
            i++;
        }
        //找到连续数字字符串的开始位置
        int begin = i;
        while(isdigit(str[i]) && i < str.length()){
            count++;
            i++;
        }
        v.push_back(str.substr(begin, count));
        i--;
        if(count > maxCount){
            maxCount = count;
        }
    }
    
    //找到字符串最长的那个vector
    string result = "";
    for(vector<string>::iterator it = v.begin(); it != v.end(); it++){
        if(((string) * it).length() > result.length()){
            result = *it;
        }
    }
    if(result != ""){
        cout << result << "," << maxCount << endl;
    }
    else{
        cout << "0" << endl;
    }
    return 0;
}
