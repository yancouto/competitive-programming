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
const int M = 500009;
int S[M], sz[M];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

inline void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

int ct[M], seen[M], t;
int nok;
void count(int i) {
	i = find(i);
	if(seen[i] < t) { seen[i] = t; ct[i] = 0; nok--; }
	ct[i]++;
	if(ct[i] == sz[i]) nok++;
}
const int N = 200009;
vector<int> p[N];
int main() {
	int i, n, m, j, x;
	scanf("%d", &n);
	for(i = 0; i < M; i++)
		S[i] = i, sz[i] = 1;
	for(i = 0; i < n; i++) {
		scanf("%d", &m);
		for(j = 0; j < m; j++) {
			scanf("%d", &x);
			p[i].pb(x);
		}
	}
	int tot = 0;
	for(i = 0; i < n; i++) {
		t++; nok = 0;
		for(int c : p[i])
			count(c);
		if(nok) continue;
		tot++;
		for(j = 0; j < p[i].size() - 1; j++)
			join(p[i][j], p[i][j + 1]);
	}
	printf("%d\n", tot);
}
