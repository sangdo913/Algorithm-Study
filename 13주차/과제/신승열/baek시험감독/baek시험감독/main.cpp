//
//  main.cpp
//  baek시험감독
//
//  Created by ShinSeungYeol on 2018. 8. 20..
//  Copyright © 2018년 ShinSeungYeol. All rights reserved.
//

#include <cstdio>

using namespace std;

int n; // n개의 시험장
int a[1000000]; // 시험장마다 응시생 수
int b,c; //b: 총 감독 역량, c: 부 감독 역량

int cal_per_nsupervisor(int a){
    if(a<0) return 0;
    int nsupervisor = a/c;
    if(a%c!=0)
        nsupervisor++;
    return nsupervisor;
} // 필요한 부감독 수

int main(int argc, const char * argv[]) {
    scanf("%d",&n);
    for(int i=0; i<n; i++)
        scanf("%d",a+i);
    scanf("%d %d",&b,&c);
    long long  res = n; // 일단 결과 값에 총 감독 수 저장 무조건 n명은 있어야 함.
    
    for(int i=0; i<n; i++){
        res+=cal_per_nsupervisor(a[i]-b);
    }
    printf("%lld\n",res);
    return 0;
}


