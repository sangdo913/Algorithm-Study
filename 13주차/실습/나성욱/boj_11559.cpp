#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <utility>
#define XSIZE 6
#define YSIZE 12
using namespace std;

int map[12][6] = { 0, };
bool visited[12][6] = { false, };
vector < pair<int, int> > list;
int move_x[] = {0, 0, -1, 1}; // U D L R
int move_y[] = {-1, 1, 0, 0};


void Get() {
	char temp;
	for (int i = 0; i < YSIZE; i++) {
		for (int j = 0; j < XSIZE; j++) {
			scanf(" %c", &temp);
			if (temp == '.')
				map[i][j] = -1;
			else if (temp == 'R')
				map[i][j] = 1;
			else if (temp == 'G')
				map[i][j] = 2;
			else if (temp == 'B')
				map[i][j] = 3;
			else if (temp == 'P')
				map[i][j] = 4;
			else if (temp == 'Y')
				map[i][j] = 5;
		}
	}
}

void dfs(int x, int y, int val) {

	int nx, ny;

	if (visited[y][x])
		return;
	visited[y][x] = true;
	list.push_back({ x, y });

	for (int i = 0; i < 4; i++) {
		nx = x + move_x[i];
		ny = y + move_y[i];

		if (nx >= 0 && nx < 6 && ny >= 0 && ny < 12) {
			
			if(map[ny][nx] == val)
				dfs(nx, ny, val);
			
		}
	}
	visited[y][x] = false;
	return;
}


bool ppung() {
	bool flag = false;
	for (int i = 0; i < YSIZE; i++) {
		for (int j = 0; j < XSIZE; j++) {
			if (map[i][j] == -1)
				continue;

			list.clear();
			dfs(j, i, map[i][j]);
			if (list.size() >= 4) {
				for (int k = 0; k < list.size(); k++) {
					map[list[k].second][list[k].first] = -1;
				}
				flag = true;
			}
		}
	}
	return flag;
}

void Down() {
	vector <int> t;

	for (int j = 0; j < XSIZE; j++) {
		t.clear();
		for (int i = YSIZE-1; i >= 0; i--) {
			if (map[i][j] != -1) {
				t.push_back(map[i][j]);
				map[i][j] = -1;
			}
		}

		for (int i = 0; i < t.size(); i++) {
			map[YSIZE-1-i][j] = t[i];
		}
	}
	return;
}

int Solution() {
	int ret = 0;

	while(1) {

		if (!ppung()) {
			break;
		}
		Down();
		ret++;
	}

	return ret;
}

int main() {
	Get();
	printf("%d\n", Solution());
}