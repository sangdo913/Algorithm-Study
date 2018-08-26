#include  <cstdio>
#include <queue>
#include <utility>

using namespace std;
enum {EMPTY=0, YELLOW=1, RED=2, GREEN=3, PURPLE=4, BLUE=5};

int dir_r[4]={-1,0,1,0};
int dir_c[4]={0,1,0,-1};

int map[12][6];  // map  정보
bool check[12][6]={false};// 테트로 미노일 경우: 1 아닐 경우 0
int cnt_of_burst=0;

void swap(int ar,int ac, int br, int bc){
    int tmp = map[ar][ac];
    map[ar][ac] = map[br][bc];
    map[br][bc] = tmp;
}
bool is_range(int r, int c){
    return (r>=0&&r<12&&c>=0&&c<6);
}
//queue를 이용해서 다시 한번
void determine_burst(int r, int c){
    queue<pair<int,int>> q;
    queue<pair<int,int>> tmp_q;
    q.push(make_pair(r,c));
    tmp_q.push(make_pair(r,c));
    int color = map[r][c];
    while(!q.empty()){
        int cur_r = q.front().first,cur_c = q.front().second;
        q.pop();
        check[cur_r][cur_c] = true;
        for(int i=0; i<4; i++){
            int next_r=cur_r+dir_r[i], next_c=cur_c+dir_c[i];
            if(is_range(next_r, next_c)&&map[next_r][next_c]==color&&!check[next_r][next_c]){
                q.push(make_pair(next_r,next_c));
                tmp_q.push(make_pair(next_r,next_c));
            }//같은 색인 도형이 있는 경우
        }
    }
    if(tmp_q.size()<4){
        while(!tmp_q.empty()){
            int cur_r = tmp_q.front().first, cur_c=tmp_q.front().second;
            tmp_q.pop();
            check[cur_r][cur_c] = false;
        }
    }// 테트로미노 아님
}
bool take_burst(){
    int cnt=0;
    for(int i=0; i<12; i++){
        for(int j=0; j<6; j++){
            if(check[i][j]){
                map[i][j] = EMPTY;
                check[i][j] = false;
                cnt++;
            }//테트로미노인 경우
        }
    }
    return cnt;
}//동시에 터지면 count가 1올라야 하기 때문에 bool로 리턴
void down(){
    for(int i=10; i>=0; i--){
        for(int j=0; j<6; j++){
            int k;
            for(k=i+1; k<12; k++){
                if(map[k][j]!=EMPTY)
                    break;
            }
            swap(i,j,k-1,j);
        }
    }
}



int main(void){
    for(int i=0; i<12; i++){
        char tmp;
        for(int j=0; j<6; j++){
            scanf("%c",&tmp);
            if(tmp=='.')
                map[i][j] = EMPTY;
            else if(tmp=='B')
                map[i][j] = BLUE;
            else if(tmp=='G')
                map[i][j] = GREEN;
            else if(tmp=='R')
                map[i][j] = RED;
            else if(tmp=='P')
                map[i][j] = PURPLE;
            else if(tmp=='Y')
                map[i][j] = YELLOW;
            else
                return 0; // 잘못된 경우
        }
        scanf("%c",&tmp); //\n 날려주고~
    }
    while(true){
        //print_map();
        for(int i=0; i<12; i++){
            for(int j=0; j<6; j++){
                if(map[i][j]!=EMPTY&&!check[i][j]) determine_burst(i, j);
            }
        }
        int cnt = take_burst();
        if(!cnt) break; //터질 것이 없는 상황
        cnt_of_burst+=cnt;
        down();
    }
    printf("%d\n",cnt_of_burst);
    
    return 0;
}

