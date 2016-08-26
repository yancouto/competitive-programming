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

const int N = 112345;

int has[N], a[N], mx[N], mn[N], hmx[N], hmn[N];

int st[N], sn, h[N], p[N];
int S[N], sz[N];
int find(int i) {
	if(S[S[i]] != S[i]) return S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

int main() {
	int i, n, m;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		has[a[i]] = 1;
	}
	for(i = 1; i < N; i++) has[i] += has[i - 1];
	for(i = 0; i < n; i++) a[i] = has[a[i]];
	for(i = 0; i < n; i++) mx[a[i]] = i;
	for(i = n - 1; i >= 0; i--) mn[a[i]] = i;
	int nu = has[N-1];
	for(i = 1; i <= nu; i++) hmx[mx[i]] = i;
	for(i = 1; i <= nu; i++) hmn[mn[i]] = i;
	for(i = 1; i <= nu; i++) S[i] = i, sz[i] = 1;
	for(i = 0; i < n-1; i++)
		if(hmx[i] && hmn[i + 1]) join(hmx[i], hmn[i + 1]);
	for(i = 1; i <= nu; i++) p[i] = i;
	sort(p + 1, p + 1 + nu, [](int i, int j) { return mn[i] > mn[j]; });
	for(i = 1; i <= nu; i++) {
		while(sn && mx[st[sn - 1]] <= mx[p[i]]) {
			h[p[i]] = max(h[p[i]], h[st[--sn]]);
		}
		h[p[i]] += sz[find(p[i])];
		st[sn++] = p[i];
	}
	printf("%d\n", *max_element(h + 1, h + 1 + nu) + (m - nu));
}
