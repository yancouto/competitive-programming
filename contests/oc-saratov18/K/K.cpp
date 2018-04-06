#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const ll modn2 = 1000000009;
inline ll mod2(ll x) { return x % modn2; }

const int N = 312345;
const int K = 100;

void Z(char s[], int n, int z[]) { // z[i] = |lcp(s,s[i..n])|
	for(int i = 1, m = -1; i < n; i++) {
		z[i] = (m != -1 && m + z[m] >= i)?min(m + z[m] - i, z[i - m]):0;
		while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
		if (m == -1 || i + z[i] > m + z[m]) m = i;
	}
}

char s[N], t[N];
int z[N];

const ll B = 321, B2 = 277;

struct hsh {
	ll x = 0;
	ll y = 0;
	inline void add(ll z) {
		x = mod(x * B + z);
		y = mod2(y * B2 + z);
	}
};

map<int, int> pr[K + 9];
map<int, int> ct[K + 9];
vector<pii> hs[K + 9];
const int G = 100009;

void getstr(char *s) {
	while(true) {
		char c = getchar_unlocked();
		if(isalpha(c)) *s = c, s++;
		else { *s = 0; break; }
	}
}

vector<int> ans[K];

int main() {
	int n, m, i, j;
	scanf("%d %d ", &n, &m);
	getstr(s);
	for(i = 0; i < n; i++) {
		hsh h;
		for(j = i; j < i + K && j < n; j++) {
			int k = j - i + 1;
			h.add(s[j]);
			hs[k].pb(pii(h.x * modn2 + h.y, i));
			//if(pr[k].count(h.x)) {
			//	if(i - pr[k][h.x] >= k)
			//		pr[k][h.x] = i, ct[k][h.x]++;
			//} else {
			//	ct[k][h.x] = 1;
			//	pr[k][h.x] = i;
			//}
		}
	}
	for(int k = 1; k <= K; k++) {
		sort(hs[k].begin(), hs[k].end());
		ans[k].resize(hs[k].size());
		for(i = 0; i < hs[k].size(); ) {
			int j = i;
			while(j + 1 < hs[k].size() && hs[k][j + 1].fst == hs[k][i].fst) j++;
			int ct = 1;
			int pr = hs[k][i].snd;
			for(int g = i + 1; g <= j; g++) {
				if(hs[k][g].snd - pr >= k) {
					ct++;
					pr = hs[k][g].snd;
				}
			}
			ans[k][i] = ct;
			i = j + 1;
		}
	}
	for(i = 0; i < m; i++) {
		getstr(t);
		int k = strlen(t);
		if(k >= K) {
			strcpy(t + k, s);
			Z(t, n + k, z);
			int ct = 0;
			int pr = -1000000;
			for(j = k; j < n + k; j++)
				if(z[j] >= k && j - pr >= k)
						ct++, pr = j;
			printf("%d\n", ct);
		} else {
			hsh h;
			for(j = 0; j < k; j++)
				h.add(t[j]);
			pii x(h.x * modn2 + h.y, -1);
			auto it = lower_bound(hs[k].begin(), hs[k].end(), x);
			if(it == hs[k].end() || it->fst != h.x * modn2 + h.y) puts("0");
			else printf("%d\n", ans[k][it - hs[k].begin()]);
		}
	}
}
