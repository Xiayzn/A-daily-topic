/*
[编程|20分] 地下迷宫
时间限制：C/C++ 1秒，其他语言 2秒
空间限制：C/C++ 32768K，其他语言 65536K
64bit IO Format: %lld
本题可使用本地IDE编码，不做跳出限制，编码后请点击“保存并调试”按钮进行代码提交。

题目描述
小青蛙有一天不小心落入了一个地下迷宫,小青蛙希望用自己仅剩的体力值P跳出这个地下迷宫。
为了让问题简单,假设这是一个n*m的格子迷宫,迷宫每个位置为0或者1,0代表这个位置有障碍物,小青蛙达到不了这个位置;1代表小青蛙可以达到的位置。
小青蛙初始在(0,0)位置,地下迷宫的出口在(0,m-1)(保证这两个位置都是1,并且保证一定有起点到终点可达的路径),
小青蛙在迷宫中水平移动一个单位距离需要消耗1点体力值,向上爬一个单位距离需要消耗3个单位的体力值,向下移动不消耗体力值,
当小青蛙的体力值等于0的时候还没有到达出口,小青蛙将无法逃离迷宫。现在需要你帮助小青蛙计算出能否用仅剩的体力值跳出迷宫(即达到(0,m-1)位置)。

输入描述:
输入包括n+1行:
 第一行为三个整数n,m(3 <= m,n <= 10),P(1 <= P <= 100)
 接下来的n行:
 每行m个0或者1,以空格分隔
 
输出描述:
如果能逃离迷宫,则输出一行体力消耗最小的路径,输出格式见样例所示;如果不能逃离迷宫,则输出"Can not escape!"。 测试数据保证答案唯一

示例1
输入
4 4 10 1 0 0 1 1 1 0 1 0 1 1 1 0 0 1 1

输出
[0,0],[1,0],[1,1],[2,1],[2,2],[2,3],[1,3],[0,3]
*/

//方法一
#include<iostream>
#include<fstream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<cstdlib>
#include<sstream>
#include<cctype>
#include<set>
#include<queue>
#include<stack>
#include<vector>
#include <iterator>
#include <utility> //std::pair
using namespace std;
typedef long long LL;

int n,m,p,ma[12][12],vis[12][12];
int dis[4][2]={0,1,1,0,0,-1,-1,0};
struct pos
{
    int x,y,step;
    friend bool operator<( pos x1, pos x2){
        return x1.step>x2.step;   //优先队列
    }
};
stack<pos> ANS;
bool check(int a, int b){
    if(a<n&&a>=0&&b<m&&b>=0&&!vis[a][b]&&ma[a][b])
        return 1;
    return 0;
}
int BFS(int si,int sj){
    struct pos p,next;
    p.x=si,p.y=sj,p.step=0;
    priority_queue<pos>Q;
    vis[si][sj]=1;
    Q.push(p);
    while(!Q.empty()){
        p=Q.top();
        Q.pop();
        ANS.push(p);//记录访问过的点
        if(p.x==0&&p.y==m-1)
        {
            return p.step;
        }
        for(int i=0;i<4;i++)
        {
            next =p;
            next.x+=dis[i][0];
            next.y+=dis[i][1];
            if(check(next.x,next.y)){
                next.step = p.step+1;
                vis[next.x][next.y] = 1;
                Q.push(next);
            }
        }
    }
    return -1;
}
int main()
{
    cin>>n>>m>>p;
    for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
        cin>>ma[i][j];
    int flag=BFS(0,0);
    if(flag!=-1)
    {
        // 如果有能走到终点，计算消耗的体力，并记录最短路径
        stack<pos> ans; //记录最短路径
        ans.push(ANS.top());
        int si=ANS.top().x;
        int sj=ANS.top().y;
        ANS.pop();
        flag--;
        int sum=0;
        while(!ANS.empty()){
            //从终点到起点开始记录最短路径，如果步数对应，并且能一步走到，即使路径上的一个点
            if(abs(ANS.top().x-si)+abs(ANS.top().y-sj)==1&&ANS.top().step==flag){
                //计算消耗的体力sum
                if(ANS.top().x==si){
                    sum++;
                }
                else if(ANS.top().x-si==1){
                    sum+=3;
                }
                si=ANS.top().x;
                sj=ANS.top().y;
                flag--;
                ans.push(ANS.top());
            }
            ANS.pop();
        }
        //所需体力小于所给体力就能走到终点
        if(sum<=p){
            cout<<"["<<ans.top().x<<","<<ans.top().y<<"]";
            ans.pop();
            while(!ans.empty()){
                cout<<",";
                cout<<"["<<ans.top().x<<","<<ans.top().y<<"]";
                ans.pop();
            }
            cout<<endl;
        }
        else cout<<"Can not escape!"<<endl;
    }
    else cout<<"Can not escape!"<<endl;
    return 0;
}



//方法二
#include<iostream>
#include<queue>
#include<vector>
#include<string>

using namespace std;

void ShowPath(const vector<pair<int, int>>& path)
{
    int len=path.size();
    for(int i=0; i<len-1; i++){
        cout<<"["<<path[i].first<<","<<path[i].second<<"],";
    }
    cout<<"["<<path[len-1].first<<","<<path[len-1].second<<"]";
}

int up=3;
int down=0;
int horizon=1;

int main()
{
    int n,m,P;
    while(cin>>n>>m>>P){
        vector<vector<int>> maze(n, vector<int>(m, 0));
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                cin>>maze[i][j];
            }
        }

        vector<pair<int, int>> best_path;
        int minP = P+1;
        queue<vector<int>> q;
        queue<vector<pair<int, int>>> path_q;
        // {x, y, p, from_direction}
        // from_direction:up-0, left-1, right-2, down-3
        q.push({0, 0, 0, 0});
        path_q.push({ {0, 0} });

        while(!q.empty()){
            // 取出最先加到队列的坐标
            vector<int> node = q.front();
            vector<pair<int, int>> current_path = path_q.front();
            q.pop();
            path_q.pop();

            // 判断当前点是否是终点，记录最佳路径
            if(node[0]==0 && node[1]==m-1 && node[2]<=P){
                if(node[2]<minP){
                    best_path = current_path;
                    minP = node[2];
                }
                continue;
            }
            // 判断当前是否还有体力
            if(node[2]>=P) continue;

            // 向下走一步
            if(node[0]+1<n && node[3]!=3){
                if(maze[node[0]+1][node[1]]==1){
                    q.push({node[0]+1, node[1], node[2]+down, 0});
                    current_path.push_back({node[0]+1, node[1]});
                    path_q.push(current_path);
                    current_path.pop_back();
                }
            }
            // 向右走一步
            if(node[1]+1<m && node[3]!=2){
                if(maze[node[0]][node[1]+1]==1){
                    q.push({node[0], node[1]+1, node[2]+horizon, 1});
                    current_path.push_back({node[0], node[1]+1});
                    path_q.push(current_path);
                    current_path.pop_back();
                }
            }
            // 向左走一步
            if(node[1]-1>=0 && node[3]!=1){
                if(maze[node[0]][node[1]-1]==1){
                    q.push({node[0], node[1]-1, node[2]+horizon, 2});
                    current_path.push_back({node[0], node[1]-1});
                    path_q.push(current_path);
                    current_path.pop_back();
                }
            }
            // 向上走一步
            if(node[0]-1>=0 && node[3]!=0){
                if(maze[node[0]-1][node[1]]==1){
                    q.push({node[0]-1, node[1], node[2]+up, 3});
                    current_path.push_back({node[0]-1, node[1]});
                    path_q.push(current_path);
                    current_path.pop_back();
                }
            }
        }
        if(best_path.empty()){
            cout<<"Can not escape!"<<endl;
        }
        else{
            ShowPath(best_path);
        }
    }
    return 0;
}
