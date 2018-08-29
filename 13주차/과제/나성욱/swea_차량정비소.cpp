#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

typedef struct Person {
	int cusnum = 0;
	int time = -1;
	int rec = 0;
	int rep = 0;
}P;
int n, m, k, rec_target, rep_target;
int rec_ability[10] = { 0, };
int rep_ability[10] = { 0, };
queue <P> rec_waiting;
queue <P> rep_waiting;
vector <vector <P>> cus_list;

void Init() {
	queue <P> t;
	rec_waiting = rep_waiting = t;


	for (int i = 0; i < cus_list.size(); i++) {
		cus_list[i].clear();
	}
	cus_list.clear();

	for (int i = 0; i < 10; i++) {
		rec_ability[i] = 0;
		rep_ability[i] = 0;
	}
}

void Get() {
	int temp = 0;

	scanf("%d %d %d %d %d", &n, &m, &k, &rec_target, &rep_target);

	for (int i = 1; i <= n; i++) {
		scanf("%d", rec_ability + i);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d", rep_ability + i);
	}

	cus_list.resize(3000);

	for (int i = 1; i <= k; i++) {
		scanf("%d", &temp);
		P p;
		p.cusnum = i;
		cus_list[temp].push_back(p);
	}

}



int Solution() {

	int ret = 0;
	vector <P> rec_service(10);
	vector <P> rep_service(10);
	vector <P> finished;

	for (int i = 0; i < 3000; i++) {

		for (int j = 0; j < cus_list[i].size(); j++) {
			rec_waiting.push(cus_list[i][j]);
		}

		for (int j = 1; j <= n; j++) {

			if (--rec_service[j].time <= 0) {
				if ((rec_service[j].cusnum > 0) && (rec_service[j].time == 0)) {
					rep_waiting.push(rec_service[j]);
				}
				if (!rec_waiting.empty()) {
					rec_service[j].cusnum = rec_waiting.front().cusnum;
					rec_service[j].rec = j;
					rec_service[j].time = rec_ability[j];
					rec_waiting.pop();
				}
			}
		}

		for (int j = 1; j <= m; j++) {

			if (--rep_service[j].time <= 0) {
				if ((rep_service[j].cusnum > 0) && (rep_service[j].time == 0)) {
					finished.push_back(rep_service[j]);
				}
				if (!rep_waiting.empty()) {
					rep_service[j].cusnum = rep_waiting.front().cusnum;
					rep_service[j].rec = rep_waiting.front().rec;
					rep_service[j].rep = j;
					rep_service[j].time = rep_ability[j];
					rep_waiting.pop();
				}
			}
		}
		if (finished.size() == k)
			break;
	}

	//cout << "finished SIZE : " << finished.size() << '\n';
	for (int i = 0; i < finished.size(); i++) {
		if ((finished[i].rec == rec_target) && (finished[i].rep == rep_target)) {
			//	cout << finished[i].cusnum << '\n';
			ret += finished[i].cusnum;
		}
	}

	return (ret == 0) ? -1 : ret;
}


int main() {

	int TC; scanf("%d", &TC);

	for (int i = 1; i <= TC; i++) {
		Init();
		Get();
		printf("#%d %d\n", i, Solution());
	}
}
