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
const int MAX = 1000009;
int tr[MAX][26], tn;
int paln[MAX];
int pal[MAX];
char s[MAX]; int k;
vector<string> v;
ll pot[MAX];
int endn[MAX];

void calc_pal() {
	ll hl = 0, hr = 0;
	for(int i = k - 1; i >= 0; i--) {
		hl = mod(hl * 263ll + s[i]);
		hr = mod(hr + pot[k - 1 - i] * s[i]);
		pal[i] = (hl == hr);
	}
}

int main() {
	int i, n, j;
	pot[0] = 1;
	for(i = 1; i < MAX; i++)
		pot[i] = mod(pot[i - 1] * 263ll);
	for_tests(t, tt) {
		v.clear();
		tn = 1;
		memset(tr[0], 0, sizeof(int) * 26);
		memset(paln, 0, sizeof paln);
		memset(endn, 0, sizeof endn);
		scanf("%d", &n);
		for(i = 0; i < n; i++) {
			scanf(" %s", s);
			v.pb(s);
			k = v.back().size();
			reverse(s, s + k);
			calc_pal();
			int p = 0;
			for(j = 0; j < k; j++) {
				if(!tr[p][s[j] - 'a']) {
					memset(tr[tn], 0, sizeof(int) * 26);
					tr[p][s[j] - 'a'] = tn++;
				}
				p = tr[p][s[j] - 'a'];
				if(j < k - 1 && pal[j + 1])
					paln[p]++;
			}
			endn[p]++;
		}
		ll tot = 0;
		for(i = 0; i < n; i++) {
			strcpy(s, v[i].c_str());
			k = v[i].size();
			calc_pal();
			if(pal[0]) tot--;
			int p = 0;
			for(j = 0; j < k; j++) {
				if(!tr[p][s[j] - 'a']) break;
				p = tr[p][s[j] - 'a'];
				tot += ll(endn[p]) * (j == (k - 1) || pal[j + 1]);
			}
			if(j == k) tot += paln[p];
		}
		printf("%lld\n", tot);
	}
}
