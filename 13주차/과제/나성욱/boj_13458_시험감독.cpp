#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int n, b, c;
int room[1000000] = {0,};

void Get(){
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%d", room+i);
    }
    scanf("%d %d", &b, &c);
}

long long int Solution(){
    long long int ret = 0;

    for(int i=0;i<n;i++){
        room[i] -= b;
        if(room[i] < 0){
            ret++;
            continue;
        }
        
        ret += (room[i]%c == 0) ? room[i]/c +1 : room[i]/c+2;
    }
        
    

    return ret;
}

int main(){
    Get();

    //for(int i=0;i<n;i++){
    //    cout << room[i] << ' ';
    //}
    printf("%lld", Solution());
}