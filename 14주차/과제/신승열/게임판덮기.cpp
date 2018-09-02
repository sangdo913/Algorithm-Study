//
//  main.cpp
//  algospot게임판덮기
//
//  Created by ShinSeungYeol on 2018. 9. 1..
//  Copyright © 2018년 ShinSeungYeol. All rights reserved.
//

#include <cstdio>
enum {BLACK, WHITE};
enum {NORTH,EAST,SOUTH,WEST};
using namespace std;

int map[20][20];
int h,w; //map size height, width
int num_of_white=0;
int whites[50][2]; // white
bool check[20][20]; //white칸 선택했는지 아닌지
int res;
int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int shape[4][2]={{NORTH,EAST},{EAST,SOUTH},{SOUTH,WEST},{WEST,NORTH}};

bool is_range(int r, int c){
    return (r>=0&&r<h&&c>=0&&c<w);
}
void input_data(){
    scanf("%d %d",&h,&w);
    char a[21];
    for(int i=0; i<h; i++){
        scanf("%s",a);
        for(int j=0; j<w; j++){
            if(a[j]=='#') map[i][j] = BLACK;
            else{
                map[i][j] = WHITE;
                whites[num_of_white][0] = i;
                whites[num_of_white++][1] = j;
            }
        }
    }
    
}
bool is_shape(int next_r[],int next_c[]){
    
    return(is_range(next_r[0],next_c[0])&&is_range(next_r[1], next_c[1])&&map[next_r[0]][next_c[0]]==WHITE&&map[next_r[1]][next_c[1]]==WHITE&&!check[next_r[0]][next_c[0]]&&!check[next_r[1]][next_c[1]]);
    
    
}
void brute_force(int sn,int idx){
    if(sn==num_of_white){
        res++;
        return;
    }
    if(idx>=num_of_white)
        return;
    int cur_r = whites[idx][0];
    int cur_c = whites[idx][1];
    if(map[cur_r][cur_c]){
        brute_force(sn, idx+1);
        return;
    }
    for(int i=0; i<4; i++){
            int next_r[2] = {cur_r+dir[shape[i][0]][0],cur_r+dir[shape[i][1]][0]};
            int next_c[2] = {cur_c+dir[shape[i][0]][1],cur_c+dir[shape[i][1]][1]};
            if(is_shape(next_r, next_c)){
                check[cur_r][cur_c]=true;
                check[next_r[0]][next_c[0]] = true;
                check[next_r[1]][next_c[1]] = true;
                brute_force(sn+3, idx+1);
                check[cur_r][cur_c]=false;
                check[next_r[0]][next_c[0]] = false;
                check[next_r[1]][next_c[1]] = false;
            }
    }
    brute_force(sn, idx+1);
}
void init_value(){
    num_of_white=0;
    res=0;
}


int main(int argc, const char * argv[]) {
    int testcase = 0;
    scanf("%d",&testcase);
    for(int z=0; z<testcase; z++){
        input_data();

        brute_force(0,0);
        printf("%d\n",res);
        init_value();
        
    }
}
