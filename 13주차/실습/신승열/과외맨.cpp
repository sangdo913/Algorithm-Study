#include <cstdio>
#include <limits.h>
#include <vector>
#include <queue>
#define MAX 500
enum {UPLEFT=0, UPRIGHT=1, RIGHT=2, DOWNRIGHT=3, DOWNLEFT=4, LEFT=5};
using namespace std;
typedef struct {
    int left, right;
    int row;
}Tile;
int n,map_size;
Tile map[MAX*MAX-MAX/2+1];
int check[MAX*MAX-MAX/2+1];
int min_cost;
int max_idx;
int dir[6];

void init_virables(){
    dir[UPLEFT] = -n;
    dir[UPRIGHT] = -n+1;
    dir[RIGHT] = 1;
    dir[DOWNRIGHT] = n;
    dir[DOWNLEFT] =  n-1;
    dir[LEFT] = -1;
    map_size=n*n-n/2;
    for(int i=1; i<=map_size; i++)
        check[i] = -1;
}
bool is_range(int idx){
    return (idx>=1&&idx<=map_size);
}
bool can_go(int direction, int cur_idx){
    int next_idx = cur_idx+dir[direction];
    if(is_range(next_idx)){
        int cur_row = map[cur_idx].row;
        int next_row = map[next_idx].row;
        if(direction==UPLEFT)
            return(map[cur_idx].left==map[next_idx].right&&cur_row-1==next_row);
        else if(direction==UPRIGHT)
            return(map[cur_idx].right==map[next_idx].left&&cur_row-1==next_row);
        else if(direction==RIGHT)
            return (map[cur_idx].right==map[next_idx].left&&cur_row==next_row);
        else if(direction==DOWNRIGHT)
            return (map[cur_idx].right==map[next_idx].left&&cur_row+1==next_row);
        else if(direction==DOWNLEFT)
            return (map[cur_idx].left==map[next_idx].right&&cur_row+1==next_row);
        else if(direction==LEFT)
            return (map[cur_idx].left==map[next_idx].right&&cur_row==next_row);
        else // 잘못 사용한 경우
            return false;
        
    }
    else return false;
    
}
int cal_row(int idx){
    int row=-1;
    while(idx>0){
        idx-=n;
        row++;
        if(idx<=0) return row;
        idx-=(n-1);
        row++;
    }
    return row;
}
void bfs(){
    queue<pair<int,int>> q;
    q.push(make_pair(1, 1));
    check[1] = 1;
    max_idx=1;
    min_cost=1;
    
    while(!q.empty()){
        int cur_idx = q.front().first;
        int depth=q.front().second+1;
        q.pop();
        
        for(int i=0; i<6; i++){
            int next_idx = cur_idx+dir[i];
            if(can_go(i,cur_idx)&&check[next_idx]==-1){
                q.push(make_pair(next_idx,depth));
                check[next_idx]=cur_idx;
                if(next_idx>max_idx){
                    max_idx=next_idx;
                    min_cost=depth;
                }
            }
        }
    }
}

void print_output(){
    printf("%d\n",min_cost);
    vector<int> v;
    int cur_idx = max_idx;
    v.push_back(cur_idx);
    while(cur_idx!=1){
        v.push_back(check[cur_idx]);
        cur_idx=check[cur_idx];
    }
    
    while(!v.empty()){
        printf("%d ",v.back());
        v.pop_back();
    }
    printf("\n");
}

int main(void){
    scanf("%d",&n);
    init_virables();
    for(int i=1; i<=map_size; i++){
        int tmp_left, tmp_right;
        scanf("%d %d",&tmp_left,&tmp_right);
        map[i].left = tmp_left;
        map[i].right = tmp_right;
        map[i].row = cal_row(i);
    }
    bfs();
    print_output();
    return 0;
}

