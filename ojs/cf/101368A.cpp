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
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

int adj[13][13];
int adj2[13][1 << 13];
int pop[1 << 13], to_b3[1 << 13];
int adj4[13], adj3[1 << 13];

int memo[2123456][2];
int solve(int bs, int bt, int ss) {
	assert((bs & bt) == 0);
	if(ss == 2) return pop[bs] - pop[bt];
	int &r = memo[to_b3[bs] + 2 * to_b3[bt]][ss];
	if(r != INT_MIN) return r;
	r = INT_MIN;
	bool any = false;
	int rst = ((1 << n) - 1) ^ (bs | bt);
	for(int bm = rst; bm; bm = ((bm - 1) & rst)) {
		int pA = pop[adj3[bm] & bs], pB = pop[adj3[bm] & bt];
		if(pA > pop[bm] + pB)
			r = max(r, -solve(bt, bs | bm, 0)), any = true;
	}
	if(!any) r = -solve(bt, bs, ss + 1);
	return r;
}

int pol[13];

int main() {
#ifdef ONLINE_JUDGE
	freopen("battle.in", "r", stdin);
	freopen("battle.out", "w", stdout);
#endif
	int i, j;
	for(i = 0; i < 2123456; i++) memo[i][0] = memo[i][1] = INT_MIN;
	int s, t;
	scanf("%d %d %d", &n, &s, &t); s--; t--;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++) {
			char c;
			scanf(" %c", &c);
			adj[i][j] = (c == '1');
			adj4[i] |= (adj[i][j] << j);
		}
	for(i = 0; i < n; i++) scanf("%d", &pol[i]);
	for(i = 0; i < (1 << n); i++) {
		int b3 = 0;
		for(j = n - 1; j >= 0; j--) {
			if((i >> j) & 1) {
				adj3[i] |= adj4[j];
				pop[i] += pol[j];
				for(int k = 0; k < n; k++)
					adj2[k][i] += adj[k][j] * pol[j];
			}
			b3 = b3 * 3 + ((i >> j) & 1);
		}
		adj3[i] = adj3[i] & (((1 << n) - 1) ^ i);
		to_b3[i] = b3;
	}
	printf("%d\n", solve((1 << s), (1 << t), 0));
}
