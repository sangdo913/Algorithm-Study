#define	_CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#define ISCHECK 1
using namespace std;

int C, N, M, first,second,cnt;
bool arr[11][11];

void solution(int visit)
{
	if (visit == (int)pow(2, N) - 1)
	{
		cnt++;
		return;
	}
	int member = 0;
	int tmp = visit;
	while (tmp&ISCHECK)
	{
		tmp = tmp >> 1;
		member++;
	}
	for (int i = member+1; i < N; i++)
		if (!(1 << i & visit) && arr[member][i])
			solution(visit | (1 << i) | (1 << member));			
}

int main()
{

	freopen("C:\\Users\\hykan\\OneDrive\\Desktop\\input.txt", "r", stdin);
	scanf("%d",&C);
	for (int i = 0; i < C; i++)
	{
		cnt = 0;
		memset(arr, 0, sizeof(arr));
		scanf("%d %d",&N,&M);
		for (int j = 0; j < M; j++)
		{
			scanf("%d %d",&first, &second);
			arr[first][second] = arr[second][first] = true;
		}
		solution(0);
		printf("%d\n",cnt);
	}
	return 0;
}