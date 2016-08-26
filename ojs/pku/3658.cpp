#include <algorithm>
#include <cstdio>
#include <climits>
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
const int N = 100009;

int find(int S[], int i) {
	if(S[S[i]] != S[i]) S[i] = find(S, S[i]);
	return S[i];
}

int Sl[N], szl[N], Sr[N], szr[N], S[N], sz[N], r[N], l[N], w[N], id[N];
int h[N]; ll c[N];

void join(int S[], int sz[], int a, int b) {
	if((a = find(S, a)) == (b = find(S, b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
	if(S == Sr) r[a] = max(r[a], r[b]);
	else if(S == Sl) l[a] = min(l[a], l[b]);
	else if(h[id[a]] > h[id[b]]) w[a] += w[b];
	else id[a] = id[b], w[a] += w[b];
}

int main() {
	int i, n;
	scanf("%d", &n);
	int mxi = 1, mni = 1;
	for(i = 1; i <= n; i++) {
		scanf("%d %d", &w[i], &h[i]);
		if(h[i] > h[mxi])
			mxi = i;
		if(h[i] < h[mni])
			mni = i;
	}
	h[0] = h[n + 1] = INT_MAX;
	for(i = 0; i < N; i++)
		S[i] = Sl[i] = Sr[i] = l[i] = r[i] = id[i] = i;
		sz[i] = szr[i] = szl[i] = 1;
	for(i = 1; i <= n; i++) {
		if(h[i - 1]  < h[i])
			join(Sl, szl, i, i - 1);
		if(h[i] > h[i + 1])
			join(Sr, szr, i, i + 1);
	}
	ll cur = 0;
	while(true) {
		//printf("doing %d\n", mni);
		mni = find(S, mni);
		//printf("needs %lld + %d for %d\n", cur, w[mni], id[mni]);
		c[id[mni]] = cur + w[mni];
		if(h[id[mni]] == h[mxi])
			break;
		int k = l[find(Sl, mni)] - 1;
		int k2 = r[find(Sr, mni)] + 1, nx;
		if(h[k] > h[k2]) {
			k = k2;
			join(Sr, szr, mni, k);
			nx = r[find(Sr, mni)];
		} else {
			join(Sl, szl, mni, k);
			nx = l[find(Sl, mni)];
		}
		//printf("%lld to fill all\n", ll(h[k] - h[id[mni]]) * ll(w[mni]));
		cur += ll(h[k] - h[id[mni]]) * ll(w[mni]);
		join(S, sz, mni, k);
		//printf("%d to %d\n", mni, nx);
		mni = nx;
	}
	for(i = 1; i <= n; i++)
		printf("%lld\n", c[i]);
}
