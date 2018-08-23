#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
struct Info{
    int id, visit[2], time;
};
 
struct rccmp{
    bool operator()(Info a, Info b){
        return a.id > b.id;
    }
};
 
struct rpcmp{
    bool operator()(Info a, Info b){
        if(a.time > b.time){
            return true;
        }else if(a.time == b.time){
            return a.visit[0] > b.visit[0];
        }else{ 
            return false;
        }
    }
};
 
 
int rcdesk[10], rpdesk[10]; //time resource
int initlist[1001]; //customer arrive time
Info rclist[10], rplist[10]; //current desk info
priority_queue<Info, vector<Info>, rccmp> rcwq, rctq; //recept desk wait queue
priority_queue<Info, vector<Info>, rpcmp> rpwq, rptq; //repair desk wait queue
 
int ans = 0;
int n, m, k, A, B;
 
void simulate(){
    int time = 0, complete = 0;
    Info clear = {0,0,0,0};
	//1. repair, 2. recept, 3. repair wait queue, 4. recept wait queue
    while(1){
        for(int i = 1; i<= k; i++){
            if(time == initlist[i]){
                Info ni = {i, {0,0}, 0};
                rcwq.push(ni);
            }
        }
 
        for(int i = 1; i <= m; i++){
            if(rplist[i].time > 0){
                rplist[i].time -= 1;
                if(rplist[i].time == 0){
                    complete++;
                    rplist[i] = clear;
                }
            }
        }
 
        if(complete == k) break;
 
        for(int i = 1; i <= n; i++){
            if(rclist[i].time > 0){
                rclist[i].time -= 1;
                if(rclist[i].time == 0){
                    Info ni = rclist[i];
                    ni.time = time;
                    rpwq.push(ni);
                    rclist[i] = clear;
                }
            }
        }
 
        for(int i = 1; i <= m; i++){
            if(rplist[i].time == clear.time && rpwq.size() > 0){
                Info ni = rpwq.top(); rpwq.pop();
                if(ni.visit[0] == A && i == B){
                    ans += ni.id;
                }
                ni.visit[1] = i;
                ni.time = rpdesk[i];
                rplist[i] = ni;
 
            }
        }
 
        for(int i = 1; i <= n; i++){
            if(rclist[i].time == clear.time && rcwq.size() > 0){
                Info ni = rcwq.top(); rcwq.pop();
                ni.time = rcdesk[i];
                ni.visit[0] = i;
                rclist[i] = ni;
            }
        }
 
        time++;        
    }
}
 
int main(){
    int t;
    scanf("%d", &t);
    for(int tc= 1; tc <= t; tc++){
        ans = 0;
        memset(rcdesk, 0, sizeof(rcdesk));
        memset(rpdesk, 0, sizeof(rpdesk));
        memset(rclist, 0, sizeof(rclist));
        memset(rplist, 0, sizeof(rplist));
        scanf("%d %d %d %d %d", &n, &m, &k, &A, &B);
        for(int i=1; i <= n; i++) scanf("%d", rcdesk + i);
        for(int i=1; i <= m; i++) scanf("%d", rpdesk + i);
        for(int i = 1; i <= k; i++) scanf("%d", initlist + i);
        simulate();
        if(ans ==0) ans = -1;
        printf("#%d %d\n", tc, ans);
    }
    return 0;
}
