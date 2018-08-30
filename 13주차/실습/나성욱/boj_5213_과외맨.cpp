// boj 5213 °ú¿Ü¸Ç
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#define MAX_ELEM 250000
using namespace std;
typedef struct tile {
	int first = 0;
	int second = 0;
	int line = 0;
	int prev = 0;
	int depth = 987654321;
}T;
int n;
int ntile;
bool visited[MAX_ELEM];
queue <int> q;
T tiles[MAX_ELEM];

void Get() {
	int a, b, cnt = 0, cur_line = 1;
	T temp;
	scanf("%d", &n);
	for (int i = 1; i <= (n*n - (n / 2)); i++) {
		if (cur_line % 2 == 1) {
			if (cnt == n) {
				cur_line++;
				cnt = 0;
			}
			cnt++;
		}
		else {
			if (cnt == n - 1) {
				cur_line++;
				cnt = 0;
			}
			cnt++;
		}
		scanf("%d %d", &a, &b);
		temp.first = a;
		temp.second = b;
		temp.line = cur_line;

		tiles[i] = temp;
	}
	ntile = n*n - (n / 2);
}

bool CanMove(int tilenum, int dir, int move[]) {
	bool flag = false;
	int nt = tilenum + move[dir];
	int line_sub = abs(tiles[tilenum].line - tiles[nt].line);
	if (nt <= 0 || nt > ntile)
		return flag;

	//cout << "dir : " << dir << "    subline : " << line_sub << '\n';
	if (dir == 0) {
		if (line_sub == 1)
			flag = tiles[tilenum].first == tiles[nt].second ? true : false;
		return flag;
	}
	else if (dir == 1) {
		if (line_sub == 1)
			flag = tiles[tilenum].second == tiles[nt].first ? true : false;
		return flag;
	}
	else if (dir == 2) {
		if (line_sub == 0)
			flag = tiles[tilenum].first == tiles[nt].second ? true : false;
		return flag;
	}
	else if (dir == 3) {
		if (line_sub == 0)
			flag = tiles[tilenum].second == tiles[nt].first ? true : false;
		return flag;
	}
	else if (dir == 4) {
		if (line_sub == 1)
			flag = tiles[tilenum].first == tiles[nt].second ? true : false;
		return flag;
	}
	else if (dir == 5) {
		if (line_sub == 1)
			flag = tiles[tilenum].second == tiles[nt].first ? true : false;
		return flag;
	}
	else {
		printf("Move Err\n");
		return flag;
	}

	return flag;
}

void Bfs(int tilenum, int move[]) {

	if (visited[tilenum])
		return;
	visited[tilenum] = true;

	for (int i = 0; i < 6; i++) {
		int nt = tilenum + move[i];
		if (CanMove(tilenum, i, move) ) {//&& (tilenum + move[i]) > tilenum
			q.push(nt);
			if (tiles[nt].depth >= tiles[tilenum].depth + 1) {
				tiles[nt].depth = tiles[tilenum].depth + 1;
				tiles[nt].prev = tilenum;
			}
		
		}
	}

	return;
}

void Solution() {
	int move[] = { -n, -n + 1, -1, +1, n - 1, n };
	stack <int> res;
	q.push(1);
	tiles[1].depth = 0;
	while (!q.empty()) {
		Bfs(q.front(), move);
		if (q.front() == ntile)
			break;
		//cout << q.front() << ' '<< endl;

		q.pop();
	}

	for (int i = ntile; i >= 1; i--) {
		if (visited[i]) {
			int temp = i;
			while (temp != 1) {
				res.push(temp);
				temp = tiles[temp].prev;
			}
			break;
		}
	}

	printf("%d\n1 ", res.size() + 1);
	while (!res.empty()) {
		printf("%d ", res.top());
		res.pop();
	}
	printf("\n");

	return;
}

int main() {

	Get();
	Solution();

	return 0;
}