#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int n, k, l;
int map[101][101];
int time[100];
char rot[100];
int ans;
int distx[4] = { 1,0,-1,0 };
int disty[4] = { 0,-1,0,1 };
int dirInfo[4][2] = { {1,3},{2,0},{3,1},{0,2} };
char alpha[256];
struct Point {
	int x, y;
};

queue <Point> list;

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 0; i < k; i++) {
		int x, y;
		scanf("%d %d", &y, &x);
		map[y][x] = 2;
	}
	alpha['L'] = 0;
	alpha['D'] = 1;

	scanf("%d", &l);
	for (int i = 0; i < l; i++) {
		scanf("%d %c", time + i, rot + i);
	}
	int tx = 1, ty = 1, dir = 0;
    Point sp = {tx,ty};
 	list.push(sp);
	int timeidx = 0;
	while (1) {
		int nx = tx + distx[dir];
		int ny = ty + disty[dir];
		if (nx >= 1 && ny >= 1 && nx <= n && ny <= n) {
			if (map[ny][nx] == 2) {
                Point np = {nx,ny};
				list.push(np);
				map[ny][nx] = 1;
			}
			else if (map[ny][nx] == 0) {
				Point tail = list.front(); list.pop();
                Point np = {nx,ny};
				list.push(np);
				map[tail.y][tail.x] = 0;
				map[ny][nx] = 1;
			}
			else break;
		}
		else break;

		tx = nx;
		ty = ny;
		ans++;
		if (timeidx < l && ans >= time[timeidx]) {
			dir = dirInfo[dir][alpha[rot[timeidx]]];
			timeidx++;
		}
	}

	printf("%d\n", ans+1);
	return 0;
}
