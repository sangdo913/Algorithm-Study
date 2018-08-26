//
//  main.cpp
//  baek뱀
//
//  Created by ShinSeungYeol on 2018. 8. 21..
//  Copyright © 2018년 ShinSeungYeol. All rights reserved.
//

#include <cstdio>
using namespace std;

enum {NORTH=0, EAST=1,SOUTH=2,LEFT=3};
enum {NOTHING=0, APPLE=1, SNAKE=2};
int n,k,l; //n: 맵 사이즈, k: 사과 개수, l: 방향 전환 개수
int map[102][102]; //0: 아무 것도 없음, 1: 사과 있음, 2: 뱀이 있음,
int ins[100][2]; // i번째 명령, [i][0]: 인스트럭션이 수행될 시간, [i][1]: 방향 0일 경우 왼쪽, 1일 경우 오른쪽
int dir_pos[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int past_dir[102][102]; // 다음 꼬리는 그 꼬리 위치에서 갔던 방향과 일치하니까

int rotate(int dir, int c ){ //dir: 지금 현재 뱀이 보는 방향, c: 인스트럭션 0일 경우 왼쪽, 1일 경우 오른쪽
    if(c==0)
        return (dir+3)%4;
    else if(c==1)
        return (dir+1)%4;
    else
        return -1; // 잘못 사용한 경우
}
bool is_range(int r, int c){
    return(r>=1&&r<=n&&c>=1&&c<=n);
}

int simulate(){
    int end_time=0, dir=EAST, cur_r=1, cur_c=1, ins_idx=0;
    int tail_r=1, tail_c=1;
    map[cur_r][cur_c] = SNAKE;
    while(true){
        if(end_time==ins[ins_idx][0])
            dir=rotate(dir,ins[ins_idx++][1]);
        end_time++;
        
        int next_r = cur_r+dir_pos[dir][0];
        int next_c = cur_c+dir_pos[dir][1];
        
        
        if(is_range(next_r, next_c)){
            past_dir[cur_r][cur_c] = dir;
            
            if(map[next_r][next_c]==NOTHING){ //가려는 곳에 아무 것도 없는 경우
                map[tail_r][tail_c] = NOTHING;
                int tmpr= tail_r, tmpc= tail_c;
                tail_r = tail_r+dir_pos[past_dir[tmpr][tmpc]][0];
                tail_c = tail_c+dir_pos[past_dir[tmpr][tmpc]][1];
            }// tail이 바뀌는 원리는 그 전에 그 지점에서 이동한 방향과 꼬리가 이동해야 하는 방향이 일치함
            
            
            else if(map[next_r][next_c]==SNAKE)//가려는 곳에 뱀이 있는 경우
                return end_time;
            
            map[next_r][next_c] = SNAKE;
            cur_r = next_r;
            cur_c = next_c;
        }
        else{
            return end_time;
        }
        
        
    }
    
}


int main(int argc, const char * argv[]) {
    scanf("%d",&n);
    scanf("%d",&k);
    for(int i=0; i<100; i++)
        ins[i][0]=-2;
    for(int i=0; i<k; i++){
        int r,c;
        scanf("%d %d",&r,&c);
        map[r][c] = APPLE;
    }
    scanf("%d",&l);
    for(int i=0; i<l; i++){
        int t;
        char c;
        scanf("%d %c",&t,&c);
        ins[i][0] = t;
        if(c=='L') ins[i][1] = 0;
        else ins[i][1] = 1;
    }
    printf("%d\n",simulate());
    return 0;
}
