#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int N = 112;

int p[N];

ll p10[N];

char s[N];
int a[N];

ll g;

ll gcd(ll a, ll b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}

void go(int i, int bm, ll x, int s) {
	if(g == 1) return;
	if(s == -1) {
		g = gcd(g, x);
		return;
	}
	if(p[a[i]] != -1) {
		x = x + p10[s] * p[a[i]];
		return go(i + 1, bm, x, s - 1);
	}
	for(int d = !i; d < 10; d++) {
		if((bm >> d) & 1) continue;
		p[a[i]] = d;
		go(i + 1, bm | (1 << d), x + p10[s] * d, s - 1);
		p[a[i]] = -1;
	}
}

typedef long long ll;
int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int i, n;
	p10[0] = 1;
	for(i = 1; i < N; i++)
		p10[i] = 10ll * p10[i - 1];
	memset(p, -1, sizeof p);
	scanf("%d", &n);
	int t = 0;
	while(n--) {
		scanf("%s", s);
		for(i = 0; s[i]; i++)
			a[i] = s[i] - '0';
		g = 0;
		go(0, 0, 0, strlen(s) - 1);
		printf("Case %d:", ++t);
		ll x;
		for(x = 1; x * x <= g; x++)
			if(!(g % x))
				printf(" %lld", x);
		for(x--; x >= 1; x--)
			if(x * x != g && !(g % x))
				printf(" %lld", g / x);
		putchar('\n');
	}
}
