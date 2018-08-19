// BOJ 14500 테트로미노

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <utility>
using namespace std;

typedef struct Point{
	int xpos;
	int ypos;
}p;


int n, m;
int map[500][500] = {0,};

p cover1[3][2][4] = { // x, y
	{ { {0,0},{1,0},{2,0},{3,0} },	{ { 0,0 },{ 0,1 },{ 0, 2 },{ 0,3 } } },
	{ { { 1,0 },{ 2,0 },{ 0,1 },{ 1,1 } },	{ { 0,0 },{ 0,1 },{ 1, 1 },{ 1,2 } } },
	{ { { 0,0 },{ 1,0 },{ 1,1 },{ 2,1 } },{ { 1,0 },{ 0,1 },{ 1, 1 },{ 0,2 } } }
};
p cover2[3][4][4] = {
	{ { { 0,0 },{ 0,1 },{ 0,2 },{ 1,2 } },	{ { 0,1 },{ 1,1 },{ 2, 1 },{ 2,0 } },	{ { 0,0 },{ 1,0 },{ 1, 1 },{ 1,2 } },	{ { 0,0 },{ 1,0 },{ 2, 0 },{ 0,1 } } },
	{ { { 0,0 },{ 1,0 },{ 2,0 },{ 1,1 } },	{ { 1,0 },{ 0,1 },{ 1, 1 },{ 1,2 } },	{ { 1,0 },{ 0,1 },{ 1, 1 },{ 2,1 } },	{ { 0,0 },{ 0,1 },{ 0, 2 },{ 1,1 } } },
	{ { { 1,0 },{ 1,1 },{ 1,2 },{ 0,2 } },	{ { 0,0 },{ 0,1 },{ 1, 1 },{ 2,1 } },	{ { 0,0 },{ 1,0 },{ 0, 1 },{ 0,2 } },	{ { 0,0 },{ 1,0 },{ 2, 0 },{ 2,1 } } }
};
p cover3[4] = {
	{ 0,0 },{ 1,0 },{ 0,1 },{ 1,1 }
};



void Get() {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &map[i][j]);
		}
	}

}



int Cover(int x, int y) {
	bool flag = true;
	int max = -1, temp = 0;
	int nx = x, ny = y;

	for (int i = 0; i < 4; i++) {
		nx = x + cover3[i].xpos;
		ny = y + cover3[i].ypos;

		if (nx < 0 || nx >= m || ny < 0 || ny >= n){
			flag = false;
			break;
		}
		temp += map[ny][nx];
	}
	if (flag) max < temp ? max = temp : max;
	


	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			flag = true;
			temp = 0;

			for (int k = 0; k < 4; k++) {
				nx = x + cover1[i][j][k].xpos;
				ny = y + cover1[i][j][k].ypos;

				if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
					flag = false;
					break;
				}
				temp += map[ny][nx];
				
			}
			if (flag) max < temp ? max = temp : max;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			flag = true;
			temp = 0;

			for (int k = 0; k < 4; k++) {
				nx = x + cover2[i][j][k].xpos;
				ny = y + cover2[i][j][k].ypos;

				if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
					flag = false;
					break;
				}
				temp += map[ny][nx];
				
			}
			if (flag) max < temp ? max = temp : max;
		}
	}

	return max;
}

int Solution() {
	int max = -1, temp;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			temp = Cover(j, i);
			max < temp ? max = temp : max;
		}
	}

	return max;
}

int main() {
	Get();
	printf("%d\n", Solution());

	return 0;
}