#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
#define MAX_VALUE   (1000000000)
struct Point{
    int x, y, wait, time, stair; 
};
struct Stair{
    int x, y, time, cnt;
};

vector<Point> hlist; //human list
vector<Stair> slist; // stair list
int ans = MAX_VALUE;

int abs(int a){return a>=0 ? a:-a;}
int getd(Point a, Stair b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void simulate(){
    int time = 1;
    int qidx = -1;
    int hsize = hlist.size();
    int ssize = slist.size();
    int complete = 0; 


	//1. godown, 2. check if anyone can go down 3. process people who arrived stairs.

    while(1){
		//1
        for(int i = 0; i < hsize; i++){
            Point *pos = &hlist[i];
            if(pos->time > 0){
                pos->time--;
                if(pos->time == 0){
                    slist[pos->stair].cnt--;
                    pos->wait = 2;
                    complete++;
                }
            }
        }

        if(complete == hsize) break;
		//2
        for(int i = 0; i < hsize; i++){
            if(slist[hlist[i].stair].cnt < 3 && hlist[i].wait == 1){
                hlist[i].time = slist[hlist[i].stair].time;
                hlist[i].wait = 0;
                slist[hlist[i].stair].cnt++;
            }
        }        
		//3
        for(int i = 0; i < hsize; i++){
            int d = getd(hlist[i], slist[hlist[i].stair]);
            if(d == time){
                hlist[i].wait = 1;
            }
        }
        time++;
        
    }
    if(ans > time) ans = time;
}

void dfs(int idx, int size){
    if(idx >= size){
        vector<Point> th = hlist;
        vector<Stair> ts = slist;
        simulate();
        hlist = th;
        slist = ts;
        return;
    }
    int ssize = slist.size();
    for(int i = 0; i < ssize; i++){
        Point npos = hlist[idx];
        npos.stair = i;
        hlist[idx] = npos;
        dfs(idx+1, size);
    }
}

int n, t;
int main(){
    freopen("input.txt", "r", stdin);
    scanf("%d", &t);
    for(int tc = 1; tc <= t; tc++){
        slist.clear();
        hlist.clear();
        ans = MAX_VALUE;
        scanf("%d", &n);
        for(int y = 0; y < n; y++){
            for(int x = 0; x < n; x++){
                int v;
                scanf("%d", &v);
                if(v == 1){
                    Point pos = {x,y,-1, -1, -1};
                    hlist.push_back(pos);
                }else if(v > 1){
                    Stair stair = {x,y,v, 0};
                    slist.push_back(stair);    
                }
            }
        }
        int hsize = hlist.size();
        dfs(0, hsize);
        printf("#%d %d\n", tc, ans);
    }
    return 0;
}
