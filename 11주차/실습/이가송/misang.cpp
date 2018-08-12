#include <cstdio>
#include <cstring>
using namespace std;
struct Point {
	int cnt, dir;
};

int distx[5] = { 0, 0,0,-1,1 };
int disty[5] = { 0, -1,1,0,0 };
int n, m, k, t;
int ans = 0;
int max_n[100][100];
Point map[100][100];
Point tmp[100][100];

void reverse(int *dir) {
	int tmp = *dir;
	if (tmp == 1) *dir = 2;
	else if (tmp == 2) *dir = 1;
	else if (tmp == 3) *dir = 4;
	else if (tmp == 4) *dir = 3;
}

int isBorder(int x, int y) {
	return x == 0 || y == 0 || x == n - 1 || y == n - 1;
}


int main() {
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		scanf("%d %d %d", &n, &m, &k);
		ans = 0;
		memset(map, 0, sizeof(map));
		for (int i = 0; i < k; i++) {
			int y, x, cnt, dir;
			scanf("%d %d %d %d", &y, &x, &cnt, &dir);
			map[y][x] = { cnt, dir };
		}

		while (m--) {
			memset(max_n, 0, sizeof(max_n));
			for (int y = 0; y < n; y++) {
				for (int x = 0; x < n; x++) {
					if (map[y][x].cnt == 0) continue;
					int nx = x + distx[map[y][x].dir];
					int ny = y + disty[map[y][x].dir];
					if (isBorder(nx, ny) != 0) {
						//border ÁøÀÔ
						tmp[ny][nx].dir = map[y][x].dir;
						reverse(&tmp[ny][nx].dir);
						tmp[ny][nx].cnt = map[y][x].cnt / 2;
					}
					else {
						if (max_n[ny][nx] < map[y][x].cnt) {
							max_n[ny][nx] = map[y][x].cnt;
							tmp[ny][nx].dir = map[y][x].dir;
						}
						tmp[ny][nx].cnt += map[y][x].cnt;
					}
				}
			}
			memcpy(map, tmp, sizeof(tmp));
			memset(tmp, 0, sizeof(tmp));
		}

		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				ans += map[y][x].cnt;
			}
		}

		printf("#%d %d\n", tc, ans);
	}
	return 0;
}