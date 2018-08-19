// BOJ 14499 주사위굴리기

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

int n, m, x, y, k;
int map[20][20] = {0,};
int move_x[] = {1, -1, 0, 0}; // E, W, N, S
int move_y[] = {0, 0, -1, 1};
vector <int> dice(6);
/*
   1
3  0  2
   4
   5
*/

void print() {
	printf("  %d\n%d %d %d\n  %d\n  %d\n", dice[1], dice[3], dice[0], dice[2], dice[4], dice[5]);
}
void Get() {
	scanf("%d %d %d %d %d", &n, &m, &y, &x, &k);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}


void Rotate(int dir) {
	vector <int> t(6);
	switch (dir) {
	case 1: 
		t[0] = dice[3];
		t[1] = dice[1];
		t[2] = dice[0];
		t[3] = dice[5];
		t[4] = dice[4];
		t[5] = dice[2];
		break;
	case 2:
		t[0] = dice[2];
		t[1] = dice[1];
		t[2] = dice[5];
		t[3] = dice[0];
		t[4] = dice[4];
		t[5] = dice[3];
		break;
	case 3:
		t[0] = dice[4];
		t[1] = dice[0];
		t[2] = dice[2];
		t[3] = dice[3];
		t[4] = dice[5];
		t[5] = dice[1];
		break;
	case 4:
		t[0] = dice[1];
		t[1] = dice[5];
		t[2] = dice[2];
		t[3] = dice[3];
		t[4] = dice[0];
		t[5] = dice[4];
		break;
	default:
		break;
	}
	dice = t;
}

void Solution() {
	
	int sel;

	for (int i = 0; i < k; i++) {
		scanf("%d", &sel);
		int nx = x + move_x[sel-1];
		int ny = y + move_y[sel-1];

		if (nx < 0 || nx >= m || ny < 0 || ny >= n)
			continue;
		else {

			Rotate(sel);
			x = nx;
			y = ny;
			if (map[y][x] == 0)
				map[y][x] = dice[5];
			else {
				dice[5] = map[y][x];
				map[y][x] = 0;
			}
			
			printf("%d\n", dice[0]);
		//	print();
		}
	}
}

int main() {
	Get();
	Solution();

	return 0;
}