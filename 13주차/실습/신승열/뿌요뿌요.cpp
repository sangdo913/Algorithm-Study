//
//  main.cpp
//  baek뿌요뿌요
//
//  Created by ShinSeungYeol on 2018. 8. 26..
//  Copyright © 2018년 ShinSeungYeol. All rights reserved.
//

#include <cstdio>
enum {EMPTY=0, RED=1, GREEN=2, BLUE=3, PURPLE=4, YELLOW=5};

int dirr[8]={-1,0,1,0,1,1,-1,-1};
int dirc[8]={0,1,0,-1,-1,1,1,-1};
int map[12][6];
int cnt = 0; //this is answer
bool check = false;

using namespace std;
bool is_range(int r, int c){
    return (r>=0&&r<12&&c>=0&&c<6);
}
bool can_go(int r, int c, int call_number){
    for(int i=0; i<4; i++){
        int next_r = r+dirr[i];
        int next_c = c+dirc[i];
        if(map[next_r][next_c]==call_number)
            return true;
    }
    return false;
}
void check_shape(int cnt, int r, int c, int color, int call_number){
    if(cnt==4){
        check=true; // 지울 수 있는 모양인 경우
        return;
    }
    for(int i=0; i<8; i++){
        int next_r = r+dirr[i];
        int next_c = c+dirc[i];
        if(is_range(next_r,next_c)&&map[next_r][next_c]==color&&can_go(next_r,next_c,call_number)){
            map[next_r][next_c] = call_number;
            check_shape(cnt+1, next_r, next_c,color,call_number);
            if(!check) map[next_r][next_c] = color;
        }
    }
    
}
void adjust_map(){
    for(int i=11; i>=0; i--){
        for(int j=0; j<6; j++){
            if(map[i][j]!=EMPTY){
                int k=i+1;
                for(; k<12; k++){
                    if(map[k][j]!=EMPTY){
                        break;
                    }
                }
                int tmp = map[i][j];
                map[i][j]=EMPTY;
                map[k-1][j]=tmp;
            }
        }
    }
}
void clean_map(){
    int clean = 0;
    for(int i=11; i>=0; i--){
        for(int j=0; j<6; j++){
            if(map[i][j]>=6){
                clean++;
                map[i][j]=EMPTY;
            }
        }
    }
    if(clean!=0) cnt++;
}
void print_map(){
    printf("\n");
    for(int i=0; i<12; i++){
        for(int j=0; j<6; j++){
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
}


int main(int argc, const char * argv[]) {
    for(int i=0; i<12; i++){
        char tmp;
        for(int j=0; j<6; j++){
            scanf("%c",&tmp);
            if(tmp=='.') map[i][j] = EMPTY;
            else if(tmp=='R') map[i][j] = RED;
            else if(tmp=='G') map[i][j] = GREEN;
            else if(tmp=='B') map[i][j] = BLUE;
            else if(tmp=='P') map[i][j] = PURPLE;
            else if(tmp=='Y') map[i][j] = YELLOW;
        }
        scanf("%c",&tmp);
    }
    while(true){
        int call_number = 5;
        for(int i=0; i<12; i++){
            for(int j=0; j<6; j++){
                call_number++;
                if(map[i][j]!=EMPTY&&map[i][j]<6){
                    int color = map[i][j];
                    map[i][j] = call_number;
                    check_shape(1,i,j,color,call_number);
                    if(!check) map[i][j]=color;
                }
                check=false;
            }
        }
        int pre_cnt = cnt;
        clean_map();
        if(pre_cnt==cnt) break;
        adjust_map();
    }
    printf("%d\n",cnt);
    return 0;
}
