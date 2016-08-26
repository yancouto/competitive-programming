#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int tr[3609][26], tn, qt[3609], h[3609];

int distr(int, int, int, bool);
int memo[3609][102][2];
int solve(int u, int k, bool hasb) {
	int &r = memo[u][k][hasb];
	if(r != -1) return r;
	if(!hasb && k == 0) return 0;
	if(hasb && k == qt[u]) return r = solve(u, k, false);
	if(k == 0 && !hasb) return r = 0;
	if(k == 1 && qt[u] == 2) return r = (1 + hasb) * h[u];
	if(k == 1 && hasb) return r = h[u] + solve(u, qt[u] - 1, false);
	if(k == 1) return r = h[u];
	if(k == qt[u] - 1 && hasb) return r = h[u] + solve(u, k, false);
	return r = distr(u, 25, k, hasb);
}

int memo2[3609][26][102][2];
int distr(int u, int l, int k, bool hasb) {
	if(l < 0) return k == 0? 0 : 100000000;
	int &r = memo2[u][l][k][hasb];
	if(r != -1) return r;
	if(tr[u][l] == 0) return r = distr(u, l - 1, k, hasb);
	r = INT_MAX;
	for(int i = 0; i <= k && i <= qt[tr[u][l]]; i++)
		r = min(r, distr(u, l - 1, k - i, hasb) + solve(tr[u][l], i, hasb));
	return r;
}

char s[30];
int main() {
	int n, i, j;
	scanf("%d", &n);
	tn = 1;
	for(i = 0; i < 2*n; i++) {
		scanf("%s", s);
		int v = 0;
		for(j = 0; s[j]; j++) {
			if(!tr[v][s[j] - 'A'])
				tr[v][s[j] - 'A'] = tn++;
			v = tr[v][s[j] - 'A'];
			h[v] = j + 1;
			qt[v]++;
		}
	}
	qt[0] = 2*n;
	memset(memo, -1, sizeof memo);
	memset(memo2, -1, sizeof memo2);
	printf("%d\n", n*solve(0, n, true));
}
