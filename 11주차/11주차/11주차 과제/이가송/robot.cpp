#include <cstdio>
#include <cstring>
int n, m;
int map[50][50];
int tmp[50][50];
struct Point {
	int x, y;
};

Point dist[4] = { { -1,0 },{ 0,-1 },{ 1,0 },{ 0,1 } };
Point back[4] = { { 0,1 },{ -1,0 },{ 0,-1 },{ 1,0 } };
int visit[50][50];

void ccw(int *dir) {
	*dir -= 1;
	if (*dir < 0) *dir = 3;
}
int ordering = 1;
void dfs(int sx, int sy, int dir) {
	if (ordering == 54) {
		int data = 0;
	}
	visit[sy][sx] = 1;
	int ndir = dir;
	for (int i = 0; i < 4; i++) {
		int nx = sx + dist[ndir].x;
		int ny = sy + dist[ndir].y;
		ccw(&ndir);
		if (visit[ny][nx] == 0 && map[ny][nx] == 0) {
			tmp[ny][nx] = ++ordering;
			dfs(nx, ny, ndir);
			return;
		}
	}

	int nx = sx + back[dir].x;
	int ny = sy + back[dir].y;
	if (map[ny][nx] == 0) {
		dfs(nx, ny, dir);
	}
}



int main() {
	scanf("%d %d", &n, &m);
	int r, c, d;
	scanf("%d %d %d", &r, &c, &d);
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			scanf("%d", &map[y][x]);
		}
	}
	memset(visit, 0, sizeof(visit));
	tmp[r][c] = ordering;
	dfs(c, r, d);

	int ans = 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (visit[y][x]) ans++;
		}
	}

	printf("%d\n", ans);
	return 0;
}