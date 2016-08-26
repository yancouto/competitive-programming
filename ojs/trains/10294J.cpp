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
const int N = 30009;

typedef int& (*acc)(int);

int S[N], sz[N], S_2[N], sz_2[N], seen2[N], cur = 0;
int& S1(int i) { return S[i]; }
int& sz1(int i) { return sz[i]; }
int& S2(int i) {
	if(seen2[i] < cur) { seen2[i] = cur; S_2[i] = S[i]; sz_2[i] = sz[i]; }
	return S_2[i];
}
int& sz2(int i) {
	if(seen2[i] < cur) { seen2[i] = cur; S_2[i] = S[i]; sz_2[i] = sz[i]; }
	return sz_2[i];
}

int find(int i, acc S) {
	if(S(S(i)) != S(i)) S(i) = find(S(i), S);
	return S(i);
}

inline bool join(int a, int b, acc S, acc sz) {
	if((a = find(a, S)) == (b = find(b, S))) return false;
	if(sz(a) < sz(b)) swap(a, b);
	sz(a) += sz(b);
	S(b) = a;
	return true;
}


int a[N], b[N], c[N], p[N];
int main() {
	int i, n, m, j, k;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a[i], &b[i], &c[i]);
		a[i]--; b[i]--; p[i] = i;
	}
	sort(p, p + m, [](int i, int j) { return c[i] < c[j]; });
	int sq = ceil(sqrt(m));
	int mn = INT_MAX, l, r, nx = 0;
	for(i = 0; i < m; i++) {
		cur++;
		if(!(i % sq)) {
			for(j = 0; j < n; j++) S[j] = j, sz[j] = 1;
			nx += sq;
			for(j = i; j < m && sz2(find(0, S2)) != n; j++)
				join(a[p[j]], b[p[j]], S2, sz2);
			if(sz2(find(0, S2)) == n && c[p[j - 1]] - c[p[i]] < mn)
				mn = c[p[j - 1]] - c[p[i]], l = i, r = j - 1;
			for(k = nx; k < j; k++)
				join(a[p[k]], b[p[k]], S1, sz1);
			continue;
		}
		for(k = min(nx - 1, j - 1); k >= i; k--)
			join(a[p[k]], b[p[k]], S2, sz2);
		int pj = j;
		for(; j < m && sz2(find(0, S2)) != n; j++)
			join(a[p[j]], b[p[j]], S2, sz2);
		if(sz2(find(0, S2)) == n && c[p[j - 1]] - c[p[i]] < mn)
			mn = c[p[j - 1]] - c[p[i]], l = i, r = j - 1;
		for(pj = max(pj, nx); pj < j; pj++)
			join(a[p[pj]], b[p[pj]], S1, sz1);
	}
	for(i = 0; i < n; i++)
		S[i] = i, sz[i] = 1;
	for(i = l; i <= r; i++) {
		if(join(a[p[i]], b[p[i]], S1, sz1))
			printf("%d ", p[i] + 1);
	}
	putchar('\n');
}
