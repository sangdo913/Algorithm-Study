//
//  main.cpp
//  algospot소풍
//
//  Created by ShinSeungYeol on 2018. 8. 27..
//  Copyright © 2018년 ShinSeungYeol. All rights reserved.
//

#include <cstdio>
#define MAX 50
using namespace std;

int n=0,m=0;
bool rel[MAX][MAX] = {false};
bool check[MAX] = {false};
int answer=0;
void combinate (int cnt,int index){
    if(cnt>=n){
        answer++;
        return;
    }
    if(check[index]==true){
        combinate(cnt,index+1);
        return;
    }
    for(int i=0; i<n; i++){
        if(rel[index][i]==true&&check[i]!=true){
            check[i] = true;
            check[index] = true;
            combinate(cnt+2,index+1);
            check[i] = false;
            check[index] = false;
        }
    }
}
void init(){
    answer = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            rel[i][j] = false;
        }
    }
}


int main(int argc, const char * argv[]) {
    int testcase;
    scanf("%d",&testcase);
    for(int z=0; z<testcase; z++){
        scanf("%d %d",&n,&m);
        for(int i=0; i<m; i++){
            int a,b;
            scanf("%d %d",&a,&b);
            rel[a][b]=1;
            rel[b][a]=1;
        }
        combinate(0, 0);
        printf("%d\n",answer);
        init();
    }
    return 0;
}
