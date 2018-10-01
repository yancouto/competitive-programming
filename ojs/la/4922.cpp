#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 112345;
int mrk[N], S[N], sz[N], a[N], b[N], p[N], ans[N];
char op[N];

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

int main() {
	for_tests(tn, tt) {
		int i, n, k;
		scanf("%d %d", &n, &k);
		for(i = 1; i <= n; i++)
			scanf("%d", &p[i]), mrk[i] = 0, S[i] = i, sz[i] = 1;
		for(i = 0; i < k; i++) {
			scanf(" %c %d", &op[i], &a[i]);
			if(op[i] == 'Q') scanf("%d", &b[i]);
			else mrk[a[i]]++;
		}
		for(i = 1; i <= n; i++)
			if(p[i] && !mrk[i])
				join(i, p[i]);
		for(i = k - 1; i >= 0; i--) {
			if(op[i] == 'Q') ans[i] = (find(a[i]) == find(b[i]));
			else if(--mrk[a[i]] == 0 && p[a[i]]) join(a[i], p[a[i]]);
		}
		printf("Case #%d:\n", tt);
		for(i = 0; i < k; i++)
			if(op[i] == 'Q')
				puts(ans[i]? "YES" : "NO");
	}
}
