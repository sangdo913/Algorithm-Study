#include <cstdio>
#include <cstring>
int n, m, x, y, k;
int map[20][20];
int dice[7];
int verti[4] = { 6,2,1,5 };
int hori[4] = { 6,4,1,3 };
int distx[5] = { 0, 1,-1,0,0 };
int disty[5] = { 0, 0,0,-1,1 };

//0이면 오른쪽 쉬프트, 1이면 왼쪽 쉬프트.
void move(int *p, int dir) {
	if (dir == 0) {
		int tmp = p[3];
		for (int i = 2; i >= 0; i--) {
			p[i + 1] = p[i];
		}
		p[0] = tmp;
	}
	else if (dir == 1) {
		int tmp = p[0];
		for (int i = 1; i <= 3; i++) {
			p[i - 1] = p[i];
		}
		p[3] = tmp;
	}
}

void update(int *d, int *s) {
	d[0] = s[0];
	d[2] = s[2];
}

void simulate(int x, int y) {
	if (map[y][x] == 0) {
		map[y][x] = dice[verti[0]];
	}
	else {
		dice[verti[0]] = map[y][x];
		map[y][x] = 0;
	}
}

int main() {
	scanf("%d %d %d %d %d", &n, &m, &y, &x, &k);
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			scanf("%d", &map[y][x]);
		}
	}

	for (int i = 0; i < k; i++) {
		int q;
		scanf("%d", &q);
		int nx = x + distx[q];
		int ny = y + disty[q];
		if (nx >= 0 && ny >= 0 && nx < m && ny < n) {
			if (q <= 2) {
				move(hori, q - 1);
				update(verti, hori);
			}
			else {
				move(verti, 4 - q);
				update(hori, verti);
			}
			simulate(nx, ny);
			printf("%d\n", dice[verti[2]]);
			x = nx;
			y = ny;
		}
	}
	return 0;
}
