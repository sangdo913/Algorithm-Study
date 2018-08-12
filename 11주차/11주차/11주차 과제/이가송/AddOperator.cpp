#include <cstdio>
#include <cmath>
const int MAX_VALUE = -pow(10, 9);
const int MIN_VALUE = pow(10, 9);
int max_ans, min_ans;
int A[100];
int cal[4];
int n;
int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int calculate(int a, int b, int cmd) {
	int sum = 0;
	if (cmd == 0) sum = a + b;
	else if (cmd == 1) sum = a - b;
	else if (cmd == 2) sum = a*b;
	else if (cmd == 3) sum = a / b;
	return sum;
}

void dfs(int idx, int sum) {
	if (idx == n) {
		max_ans = max(max_ans, sum);
		min_ans = min(min_ans, sum);
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (cal[i] > 0) {
			cal[i]--;
			int ret = calculate(sum, A[idx], i);
			dfs(idx + 1, ret);
			cal[i]++;
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", A + i);
	}
	for (int i = 0; i < 4; i++) {
		scanf("%d", cal + i);
	}

	max_ans = MAX_VALUE;
	min_ans = MIN_VALUE;

	dfs(1, A[0]);

	printf("%d %d\n", max_ans, min_ans);
	return 0;
}