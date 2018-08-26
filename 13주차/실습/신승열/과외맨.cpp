//
//  main.cpp
//  baek과외맨
//
//  Created by ShinSeungYeol on 2018. 8. 26..
//  Copyright © 2018년 ShinSeungYeol. All rights reserved.
//

#include <cstdio>
#include <limits.h>
using namespace std;

enum {EAST=0,SOUTH=1};

typedef struct{
    int left,right;
}Tile;

int n;
Tile map[2251];
int path_array[2251];
int correct_path_array[2251];
int map_size;
int end_point=1; // 가장 멀리 간 지점 index
int path_length= INT_MAX;


bool can_go(int id,int dir){
    if(dir==EAST)
        return (id+1<=map_size&&map[id].right==map[id+1].left);
    else if(dir==SOUTH)
        return (id+n<=map_size&&map[id].right==map[id+n].left);
    return false;
}
void simulation(int cur_id,int path){ // cur_id 현재 지점
    if(can_go(cur_id, EAST)){
        path_array[path] = cur_id+1;
        simulation(cur_id+1,path+1);
    }
    if(can_go(cur_id,SOUTH)){
        path_array[path] = cur_id+n;
        simulation(cur_id+n,path+1);
    }
    if(!can_go(cur_id,EAST)&&!can_go(cur_id,SOUTH)){
        if(end_point<cur_id){
            end_point = cur_id;
            path_length = path;
            for(int i=0; i<path_length; i++){
                correct_path_array[i] = path_array[i];
            }
        }
        else if(end_point==cur_id){
            if(path_length>path){
                path_length=path;
                for(int i=0; i<path_length; i++){
                    correct_path_array[i] = path_array[i];
                }
            }
        }
    }
    
}



int main(int argc, const char * argv[]) {
    scanf("%d",&n);
    map_size = n*n-n/2;
    for(int i=1; i<=map_size; i++){
        int left,right;
        scanf("%d %d",&left,&right);
        map[i].left = left;
        map[i].right = right;
    }
    path_array[0] = 1;
    simulation(1,1);
    printf("%d\n",path_length);
    for(int i=0; i<path_length; i++)
        printf("%d ",correct_path_array[i]);
    
}
