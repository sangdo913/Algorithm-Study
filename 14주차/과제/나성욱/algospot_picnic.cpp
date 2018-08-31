// algospot PICNIC
#include <iostream>
#include <cstring>
using namespace std;

bool isSolo[10] = { false, };
bool friend_arr[10][10] = {false, };
int n, m;

void get() {
	cin >> n >> m;
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		friend_arr[a][b] = friend_arr[b][a] =  true;
	}
}

int coupling(bool paired[10]) {
	int firstfree = -1;
	for (int i = 0; i < n; i++) {
		if (!paired[i]) {
			firstfree = i;
			break;
		}
	}
	if (firstfree == -1)
		return 1;

	int result = 0;
	for (int with = firstfree + 1; with < n; with++) {
		if (!paired[with] && friend_arr[firstfree][with]) {
			paired[firstfree] = paired[with] = true;
			result += coupling(paired);
			paired[firstfree] = paired[with] = false;
		}
	}
	//cout << result << endl;
	return result;
}



int main() {
	int testcase;
	cin >> testcase;

	while (testcase--) {
		memset(isSolo, false, sizeof(bool) * 10);
		for (int i = 0; i < 10; i++) {
			memset(friend_arr[i], false, 10 * sizeof(bool));
		}
		get();

		cout << coupling(isSolo) << endl;
	
	}

	return 0;
}