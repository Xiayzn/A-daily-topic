//字符集合
//7.24_48_2


#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

int main()
{
    string str;
    while(cin>>str){
        vector<int> flag(55, 0);
        vector<char> res;
        for(int i = 0; i < str.length(); i++){
            if(isupper(str[i])){
                if(!flag[str[i] - 'A' + 26]){
                    flag[str[i] - 'A' + 26] = 1;
                    res.push_back(str[i]);
                }
            }
            else if(islower(str[i])){
                if(!flag[str[i] - 'a']){
                    flag[str[i] - 'a'] = 1;
                    res.push_back(str[i]);
                }
            }
        }
        for(int i = 0; i < res.size(); i++){
            cout << res[i];
        }
        cout << endl;
    }
    return 0;
}
