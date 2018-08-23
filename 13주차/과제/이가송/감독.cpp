#include <cstdio>
#define N	(1000000)
typedef long long ll;
int n;
ll A[N + 1];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", A + i);
	}
	ll b, c;
	scanf("%lld %lld", &b, &c);
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		A[i] -= b;
		ans++;
		if (A[i] < 0) continue;
		ll tmp = A[i] / c + (A[i] % c != 0);
		ans += tmp;
	}

	printf("%lld\n", ans);
	return 0;
}
