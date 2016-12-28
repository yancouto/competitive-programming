#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 512;
int x[N], y[N], p[N], t, seen[N], n;

inline ll sqr(ll x) { return x * x; }

int go(int i) {
	if(seen[i] == t) return 0;
	seen[i] = t;
	int r = 1;
	for(int j = 0; j < n; j++)
		if(sqr(x[i] - x[j]) + sqr(y[i] - y[j]) <= sqr(p[i]))
			r += go(j);
	return r;
}

int main() {
	freopen("moocast.in", "r", stdin);
	freopen("moocast.out", "w", stdout);
	int i;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d %d %d", &x[i], &y[i], &p[i]);
	int best = 0;
	for(i = 0; i < n; i++) {
		t++;
		best = max(best, go(i));
	}
	printf("%d\n", best);
}
