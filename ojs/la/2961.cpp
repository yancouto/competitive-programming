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

struct ed {
	int a, b, w;
	bool operator < (ed o) const { return w < o.w; }
} es[112345];

const int N = 412;
int S[N], sz[N];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}
int cmp;
void join(int a, int b) {
	//printf("join(%d, %d)\n", a, b);
	if((a = find(a)) == (b = find(b))) return;
	//puts("OK");
	cmp--;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

int S2[N], sz2[N], seen[N], tempo;
inline void access(int i) {
	if(seen[i] != tempo) {
		seen[i] = tempo;
		S2[i] = S[i];
		sz2[i] = sz[i];
	}
}
int find2(int i) {
	access(i);
	if(S2[i] == i) return i;
	return find2(S2[i]);
}
void join2(int a, int b) {
	//printf("join(%d, %d)\n", a, b);
	if((a = find2(a)) == (b = find2(b))) return;
	//puts("OK");
	access(a); access(b);
	cmp--;
	if(sz2[a] < sz2[b]) swap(a, b);
	sz2[a] += sz2[b];
	S2[b] = a;
}

int n, m;

bool go(int d) {
	const int M = ceil(sqrt(m));
	int cur = 0;
	int R = -1;
	for(int i = 0; i < m; i++) {
		if(i == cur) {
			//printf("CLEAR\n");
			cmp = n;
			for(int j = 0; j < n; j++) S[j] = j, sz[j] = 1;
			cur += M;
			R = i - 1;
		}
		while(R + 1 < m && es[R + 1].w <= es[i].w + d)
			if(++R >= cur)
				join(es[R].a, es[R].b);
		//printf("[%d] (%d, %d) M = %d cmp %d\n", d, i, R, M, cmp);
		tempo++;
		int prev = cmp;
		for(int j = i; cmp > 1 && j <= R && j < cur; j++)
			join2(es[j].a, es[j].b);
		//printf("cmp %d\n", cmp);
		if(cmp == 1) return true;
		cmp = prev;
	}
	return false;
}

int main() {
	int i, a, b, w;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &w);
			es[i] = ed{a, b, w};
		}
		sort(es, es + m);
		int l = 0, r = (1 << 15);
		while(l < r) {
			int m = (l + r) / 2;
			bool x = go(m);
			//printf("go(%d) = %d\n", m, x);
			if(x) r = m;
			else l = m + 1;
		}
		printf("%d\n", l);
	}
}
