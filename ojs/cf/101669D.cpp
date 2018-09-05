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

const int N  = 112345;
int S[N], sz[N];
vector<int> e[N];

int find(int i) {
	if(S[i] != S[S[i]]) S[i] = find(S[i]);
	return S[i];
}

inline bool join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return false;
	if(sz[a] < sz[b]) swap(a, b);
	S[b] = a;
	sz[a] += sz[b];
	return true;
}

int main() {
	int i, j;
	int n, m, k;
	scanf("%d %d", &m, &n);
	for(i = 0; i < m; i++) {
		scanf("%d", &k);
		while(k--) {
			scanf("%d", &j); j--;
			e[j].pb(i);
		}
	}
	for(i = 0; i < m; i++) S[i] = i, sz[i] = 1;
	int ct = 0;
	for(i = 0; i < n; i++) {
		assert(e[i].size() == 2);
		if(join(e[i][0], e[i][1])) ct++;
	}
	printf("%d\n", ct);
}
