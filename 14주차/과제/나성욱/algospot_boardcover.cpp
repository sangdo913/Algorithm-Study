// algospot BOARDCOVER
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int h, w;
char map[20][20] = {0,};
int covertype[4][3][2] = { //[type][cellnum][x, y]
	{ { 0, 0 },{ 1, 0 },{ 0, 1 } },
	{ { 0, 0 },{ 0, 1 },{ 1, 1 } },
	{ { 0, 0 },{ 0, 1 },{ -1, 1 } },
	{ { 0, 0 },{ 1, 0 },{ 1, 1 } }
};

void Init() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			map[i][j] = { 0, };
		}
	}
}

void Get() {
	
	scanf("%d %d", &h, &w);
	char buf[20];
	for (int i = 0; i < h; i++) {
		scanf("%s", buf);
		for (int j = 0; j < w; j++) {
			map[i][j] = buf[j];
		}
	}
}

bool CanCover(int x, int y, int ct) {
	int nx, ny;
	for (int j = 0; j < 3; j++) {
		nx = x + covertype[ct][j][0];
		ny = y + covertype[ct][j][1];

		if (nx < 0 || nx >= w || ny < 0 || ny >= h || map[ny][nx] == '#') {
			return false;
		}
	}

	return true;
}

void Cover(int x, int y, int ct, char mode) {
	int nx, ny;

	for (int j = 0; j < 3; j++) {
		nx = x + covertype[ct][j][0];
		ny = y + covertype[ct][j][1];
		map[ny][nx] = mode;
	}
}

int Solution() {
	int ret = 0;
	int x = -1, y = -1;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (map[i][j] == '.') {
				x = j;
				y = i;
				goto exit;
			}
		}
	}
exit:
	//printf("%d %d\n", x, y);
	if (x == -1 || y == -1) {
		return 1;
	}

	for (int i = 0; i < 4; i++) {
		if (CanCover(x, y, i)) {
			Cover(x, y, i, '#');
			ret += Solution();
			Cover(x, y, i, '.');
		}
	}
	
	return ret;
}

int main() {
	int TC; scanf("%d", &TC);

	while (TC--) {
		Init();
		Get();
		printf("%d\n", Solution());
	}
	
}