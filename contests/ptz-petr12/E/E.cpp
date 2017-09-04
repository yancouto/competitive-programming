#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pb push_back

const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 412345;

int cp[N], dv[N];
int cur1[N], cur0[N], acc1[N], add1[N];

int a, b;
ll sum1(int l, int r) {
	if(r < a) return 0;
	l = max(l, a);
	return mod(acc1[r - a] - (l == a? 0 : acc1[l - a - 1]) + modn);
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("jumping.in", "r", stdin);
	freopen("jumping.out", "w", stdout);
#endif
	scanf("%d %d", &a, &b);
	int i, j;

	for(i = 2; i < N; i++)
		if(!cp[i]) {
			for(j = i + i; j < N; j += i)
				cp[j] = 1;
			for(j = int((a + i - 1) / i) * i; j <= b; j += i) {
				if(j < N && !cp[j]) continue;
				if(!dv[j - a])
					dv[j - a] = i;
			}
		}
	for(i = a; i <= b; i++) {
		//printf("[%d, %d] -> %d\n", i - (i / dv[i - a]), i - dv[i - a], i);
		cur1[i - a] = mod((i == a? 0 : cur1[i - a - 1]) + add1[i - a]);
		acc1[i - a] = mod((i == a? 0 : acc1[i - a - 1]) + cur1[i - a]);
		if(i == a) cur0[i - a] = 1;
		else {
			if(dv[i - a])
				cur0[i - a] = sum1(i - (i / dv[i - a]), i - dv[i - a]);
		}
		if(dv[i - a]) {
			//printf("%d -> [%d, %d]\n", i, i + dv[i - a], i + (i / dv[i - a]));
			add1[i - a + dv[i - a]] = mod(add1[i - a + dv[i - a]] + cur0[i - a]);
			if(i - a + (i / dv[i - a]) + 1 < N) add1[i - a + (i / dv[i - a]) + 1] = mod(add1[i - a + (i / dv[i - a]) + 1] - cur0[i - a] + modn);
		}
		//printf("%d: zero %d one %d\n", i, cur0[i - a], cur1[i - a]);
		//printf("acc1 %d\n=====\n\n", acc1[i - a]);
	}
	printf("%lld\n", mod(cur0[b - a] + cur1[b - a]));
}
