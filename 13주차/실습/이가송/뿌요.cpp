#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
struct Point{
	int x, y;
};
char map[12][6];
int ans = 0;
int distx[4] = {1,0,-1,0};
int disty[4] = {0,-1,0,1};
int visit[12][6];
int bfs(int sx, int sy){
	vector<Point> list;
	queue<Point> q;
	char c = map[sy][sx];
	Point spos = {sx,sy};
	visit[sy][sx] = 1;
	q.push(spos);
	list.push_back(spos);
	while(!q.empty()){
		Point pos = q.front(); q.pop();
		for(int i = 0; i < 4; i++){
			int nx = pos.x + distx[i];
			int ny = pos.y + disty[i];
			if(nx >=0 && ny >=0 && nx < 6 && ny < 12 && visit[ny][nx] == 0 && c == map[ny][nx]){
				Point npos = {nx,ny};
				visit[ny][nx] = 1;
				q.push(npos);
				list.push_back(npos);
			}
		}
	}

	int size = list.size();
	if(size < 4) return 0;
	for(int i = 0; i < size; i++){
		map[list[i].y][list[i].x] = '.';
	}
	return 1;
}

//1. down, 2. bfs, 3. delete, 3. combo check
void simulate(){
	int dir = 1;
	while(1){
		for(int y = 11; y >= 0; y--){
			for(int x = 0; x < 6; x++){
				int ty = y;
				while(1){
					int ny = ty + dir;
					if(ny < 12 && map[ny][x] == '.'){
						map[ny][x] = map[ty][x];
						map[ty][x] = '.';
						ty = ny;
					}else{
						break;
					}
				}
			}
		}
		memset(visit, 0, sizeof(visit));
		int cflag = 0;
		for(int y = 0; y < 12; y++){
			for(int x = 0; x < 6; x++){
				if(map[y][x] != '.' && bfs(x,y) == 1){
					cflag = 1;
				}
			}
		}

		if(cflag == 0) break;

		ans++;
	}
}

int main(){
	//freopen("input.txt", "r", stdin);
	for(int y = 0;y < 12; y++){
		for(int x = 0;x < 6; x++){
			scanf(" %c", &map[y][x]);
		}
	}

	simulate();
	printf("%d\n", ans);
	return 0;
}
