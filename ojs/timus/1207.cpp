#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10009;
ll x[N], y[N];
ll cross(int a, int b, int c) {
	return (x[b] - x[a]) * (y[c] - y[a]) - (y[b] - y[a]) * (x[c] - x[a]);
}
int p[N];

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%lld %lld", &x[i], &y[i]), p[i] = i;
	sort(p + 1, p + n, [](int i, int j) { return cross(0, i, j) < 0; });
	printf("1 %d\n", p[n / 2] + 1);
}
