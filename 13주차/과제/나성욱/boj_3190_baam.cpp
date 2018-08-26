#include <iostream>
#include <list>
#include <utility>
using namespace std;

int n, k, l;
int map[100][100] = {0,};
int move_x[] = {1, 0, -1, 0}; // E, S, W, N
int move_y[] = {0, 1, 0, -1};
list <pair <int, int>> snake;
list <pair <int, char>> query;

void Get(){
    int col, row, sec;
    char dir;
    cin >> n >> k;

    for(int i=0;i<k;i++){
        cin >> row >> col;
        map[row-1][col-1] = 1;
    }

    cin >> l;
    for(int i=0;i<l;i++){
        cin >> sec >> dir;
        query.push_back({sec, dir});
    }
    snake.push_back({0, 0});
}

bool qquang(int nx, int ny){
    list <pair<int, int>>::iterator iter;
    for(iter = snake.begin(); iter != snake.end(); iter++){
        if(nx == (*iter).first && ny == (*iter).second){
            return true;
        }
    }
    return false;
}
bool fail(int nx, int ny){
    return nx <0 || nx >= n || ny < 0 || ny >= n || qquang(nx, ny);
}

int Solution(){
    int cnt=1, nx=0, ny=0, dir=0;

    while(1){
        //cout << "cnt : " << cnt << '\n';
        nx = nx + move_x[dir];
        ny = ny + move_y[dir];
       
        if(fail(nx, ny))
            break;

       // cout << "(nx, ny) : " << nx << ' ' << ny << '\n';
        if(map[ny][nx]){
            snake.push_front({nx, ny});
            map[ny][nx] = 0;
        }
        else{
            snake.push_front({nx, ny});
            snake.pop_back();
        }

        

        if(query.front().first == cnt){
            if(query.front().second == 'L'){
                --dir, (dir < 0) ? dir = 3 : dir;
            }
            else{
                ++dir, (dir >= 4) ? dir = 0 : dir;
            }
            query.pop_front();
        }
        cnt++;
    }
    return cnt;
}


int main(){
    Get();
    cout << Solution() << '\n';

}