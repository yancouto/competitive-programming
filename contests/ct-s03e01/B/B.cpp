#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n, m, a, b;

int eval(int x) {
	//if(x < m) printf("eval(%d) = %d\n", x, (m - x) * b);
	//else printf("eval(%d) = %d\n", x, (x - m) * a);
	if(x < m) return (m - x) * b;
	else return (x - m) * a;
}

const int N = 51234;
int v[N], acc[N], opt[N];

int memo[N];
int seen[N], t;
int solve(int i) {
	if(i == n) return 0;
	int &r = memo[i];
	if(seen[i] == t) return r;
	seen[i] = t;
	int cur = 0;
	r = eval(acc[i]);
	opt[i] = n - 1;
	for(int j = i; cur <= m && j < n; j++) {
		cur += v[j];
		if(r > solve(j + 1) + eval(cur)) opt[i] = j;
		r = min(r, solve(j + 1) + eval(cur));
	}
	return r;
}


int main() {
	int i, j, t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		scanf("%d %d", &a, &b);
		for(i = 0; i < n; i++) scanf("%d", &v[i]);
		acc[n - 1] = v[n - 1];
		for(i = n - 2; i >= 0; i--) acc[i] = v[i] + acc[i + 1];
		::t++;
		printf("%d\n", solve(0));
		i = 0;
		while(i < n) {
			//printf("[%d,%d] = %d\n", i, opt[i], eval(acc[i] - acc[opt[i]] + v[opt[i]]));
			i = opt[i] + 1;
		}
	}
}
