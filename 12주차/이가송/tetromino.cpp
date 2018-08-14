#include <cstdio>
#include <cstring>
int n, m;
int map[500][500];
int ans = 0;
int distx[4] = { 0, 1, 0, -1 };
int disty[4] = { -1,0,1,0 };

int visit[500][500];
int max(int a, int b) { return a > b ? a : b; }


void dfs(int x, int y, int cnt, int sum) {
	if (cnt == 4) {
		visit[y][x] = 1;
		ans = max(ans, sum + map[y][x]);
		visit[y][x] = 0;
		return;
	}
	visit[y][x] = 1;
	for (int i = 0; i < 3; i++) {
		int nx = x + distx[i];
		int ny = y + disty[i];
		if (nx >= 0 && ny >= 0 && nx < m && ny < n && visit[ny][nx] == 0) {
			dfs(nx, ny, cnt + 1, sum + map[y][x]);
		}
	}
	visit[y][x] = 0;
}

void case1() {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			dfs(x, y, 1, 0);
		}
	}
}

void bfs(int x, int y) {
	int sum;
	for (int i = 0; i < 4; i++) {
		sum = map[y][x];
		for (int j = 0; j < 3; j++) {
			int nx = x + distx[(j + i) % 4];
			int ny = y + disty[(j + i) % 4];
			if (nx >= 0 && ny >= 0 && nx < m && ny < n) {
				sum += map[ny][nx];
			}
			else {
				sum = 0;
				break;
			}
		}
		ans = max(ans, sum);
	}
}

void case2() {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			bfs(x, y);
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			scanf("%d", &map[y][x]);
		}
	}

	case1(); //dfs
	case2(); //bfs

	printf("%d\n", ans);
	return 0;
}