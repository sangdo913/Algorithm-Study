#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
struct Point {
	int x, y, cnt;
};

int t;
int n, m;
int map[20][20];
int visit[20][20];
int distx[4] = { 1,0,-1,0 };
int disty[4] = { 0,-1,0,1 };
int ans = 0;
int g_cnt = 0;
int max(int a, int b) { return a > b ? a : b; }

void bfs(int sx, int sy, int k, int *sum) {
	Point s = { sx, sy, 1 };
	queue<Point> q;
	q.push(s);
	visit[sy][sx] = 1;
	while (!q.empty()) {
		Point pos = q.front(); q.pop();
		*sum += map[pos.y][pos.x] * m;
		if (map[pos.y][pos.x]) g_cnt++;
		for (int i = 0; i < 4; i++) {
			int nx = pos.x + distx[i];
			int ny = pos.y + disty[i];
			if (nx >= 0 && ny >= 0 && nx < n && ny < n && visit[ny][nx] == 0 && pos.cnt + 1 <= k) {
				visit[ny][nx] = 1;
				q.push({ nx,ny, pos.cnt + 1 });
			}
		}
	}

}

int main() {
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		scanf("%d %d", &n, &m);
		ans = 0;
		memset(map, 0, sizeof(map));
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				scanf("%d", map[y] + x);
			}
		}
		for (int k = n + 1; k >= 1; k--) {
			for (int y = 0; y < n; y++) {
				for (int x = 0; x < n; x++) {
					memset(visit, 0, sizeof(visit));
					g_cnt = 0;
					int sum = 0;
					bfs(x, y, k, &sum);
					if (sum >= (k*k + (k - 1)*(k - 1))) {
						ans = max(ans, g_cnt);
					}

				}
			}
			if (ans != 0) break;
		}

		printf("#%d %d\n", tc, ans);
	}


	return 0;
}