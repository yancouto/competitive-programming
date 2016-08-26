#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif
const int M = 1296000, N = 212345;
typedef long double ld;

int x[N], y[N], phi[N], alp[N];

int main() {
	int i, j, n;
	scanf("%d", &n);
	vector<pii> ev;
	map<int, int> evs;
	for(i = 0; i < n; i++) {
		scanf("%d %d %d %d", &x[i], &y[i], &phi[i], &alp[i]);
		ev.pb(pii(alp[i], 1));
		ev.pb(pii(phi[i] + alp[i], -1));
		if(phi[i] + alp[i] > M) {
			ev.pb(pii(0, 1));
			ev.pb(pii((phi[i] + alp[i]) % M, -1));
		}
	}
	evs[M] = 0;
	for(pii p : ev) evs[p.fst] += p.snd;
	int cur = 0, lst = 0;
	puts("YES");
	for(pii p : evs) {
		//printf("[%d, %d]\n", p.fst, p.snd);
		if(cur == 0 && p.fst) {
			//printf("from %d to %d\n", lst, p.fst);
			ld d = ld(lst + p.fst) * acosl(-1)  / (M);
			//printf("ang %.10f\n", (double) d);
			printf("%d %d\n", int(cosl(d) * 4e8), int(sinl(d) * 4e8));
			return 0;
		}
		cur += p.snd;
		lst = p.fst;
	}
}
