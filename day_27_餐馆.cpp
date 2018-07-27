/*
[编程|20分] 餐馆
时间限制：C/C++ 1秒，其他语言 2秒
空间限制：C/C++ 65536K，其他语言 131072K
64bit IO Format: %lld
本题可使用本地IDE编码，不做跳出限制，编码后请点击“保存并调试”按钮进行代码提交。

题目描述
某餐馆有n张桌子，每张桌子有一个参数：a 可容纳的最大人数； 
有m批客人，每批客人有两个参数:b人数，c预计消费金额。 
在不允许拼桌的情况下，请实现一个算法选择其中一部分客人，使得总预计消费金额最大

输入描述:
输入包括m+2行。 第一行两个整数n(1 <= n <= 50000),m(1 <= m <= 50000) 第二行为n个参数a,
即每个桌子可容纳的最大人数,以空格分隔,范围均在32位int范围内。 接下来m行，每行两个参数b,c。
分别表示第i批客人的人数和预计消费金额,以空格分隔,范围均在32位int范围内。

输出描述:
输出一个整数,表示最大的总预计消费金额

示例1
输入
3 5 2 4 2 1 3 3 5 3 7 5 9 1 10

输出
20
*/

/*
方法1.

链接：https://www.nowcoder.com/questionTerminal/d2cced737eb54a3aa550f53bb3cc19d0
来源：牛客网
*/

/*
思路：优先选消费额度大的客人安排就餐
对客人按照消费额度排序（大->小）
对桌子按照容量排序（大->小）
选取当前消费额度最大客人：
1.如果没有桌子可用，结束；
2.如果人数过多无法安排，跳过；
3.如果可安排，则找到最合适的桌位，可就餐的桌位中容量最小的；
  3.1向这批客人收费；
  3.2将桌子从可用资源中删除；
直到没有桌子可用或所有客人全部安排
*/
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
int main()
{
    int n, m, b, c;
    int num;
    vector<int> desk;//可用桌子资源的容量
    vector<pair<int, int>> customer;//预计消费，人数
    cin >> n >> m;
    while(n--)//输入桌子容量
    {
        cin >> num;
        desk.push_back(num);
    }
    //对桌子容量从大到小排序
    sort(desk.begin(), desk.end());
    reverse(desk.begin(), desk.end());
    vector<bool> flag(desk.size(), false);
    while(m--)
    {
        cin >> b >> c;
        customer.push_back(make_pair(c, b));
    }
    //对顾客按消费额度从大到小排序
    sort(customer.begin(), customer.end());
    reverse(customer.begin(), customer.end());
     
    long long ret = 0;//必须是long long，int会溢出
    for(int it = 0; it < customer.size(); ++it)
    {
        if(desk.size() == 0)//没有可用的桌子了
            break;
        int consumeMoney = customer[it].first;
        int countOfPeople = customer[it].second;
        if(desk[0] < countOfPeople)//最大的桌子也容不下这批客人
            continue;
        int i = 0;
        while(i < desk.size() && desk[i] >= countOfPeople)//找到可以容纳这批客人的最小桌子
            ++i;//i为第一个不可容纳的桌子，则i-1位这批客人的最佳桌位
        ret = ret + consumeMoney;//收入增加
        desk.erase(desk.begin() + i - 1);//桌子从可用资源中删除
    }
    cout << ret << endl;
}


/*
方法2

链接：https://www.nowcoder.com/questionTerminal/d2cced737eb54a3aa550f53bb3cc19d0

来源：牛客网

这个使用multiset特点来进行使用的，用low_bound直接来寻找第一个大于等于val值的下标
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
 
struct guest {
    int num;
    int money;
};
bool cmp(guest a, guest b) {
    if (a.money == b.money) {
        return a.num < b.num;
    }
    return a.money > b.money;
}
int main() {
    using namespace std;
    int n, m;
    while (cin >> n >> m) {
        multiset<int> desk;
        vector<guest> people(m);
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int temp;
            cin >> temp;
            desk.insert(temp);
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            people[i].num = a;
            people[i].money = b;
        }
        sort(people.begin(), people.end(), cmp);
        for (int i = 0; i < m; i++) {
            if (desk.empty()) {
                break;
            }
            if (people[i].num <= *desk.rbegin()) {
                ans += people[i].money;
                desk.erase(desk.lower_bound(people[i].num));
            }
        }
        cout << ans << endl;
    }
    return 0;
}
