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

const int N = 312345;
const int K = 70;

void Z(char s[], int n, int z[]) { // z[i] = |lcp(s,s[i..n])|
	for(int i = 1, m = -1; i < n; i++) {
		z[i] = (m != -1 && m + z[m] >= i)?min(m + z[m] - i, z[i - m]):0;
		while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
		if (m == -1 || i + z[i] > m + z[m]) m = i;
	}
}

char s[N], t[N];
int z[N];

const ll B = 321;

struct hsh {
	ll x = 0;
	inline void add(ll y) {
		x = mod(x * B + y);
	}
};

int en = 1;

const int M = 100000 * (K + 1);
map<char, int> tr[M];
int pr[M], ct[M];

void getstr(char *s) {
	while(true) {
		char c = getchar_unlocked();
		if(isalpha(c)) *s = c, s++;
		else { *s = 0; break; }
	}
}

int main() {
	int n, m, i, j;
	scanf("%d %d ", &n, &m);
	getstr(s);
	for(i = 0; i < n; i++) {
		int u = 0;
		for(j = i; j < i + K && j < n; j++) {
			int k = j - i + 1;
			if(!tr[u].count(s[j]))
				tr[u][s[j]] = en++;
			u = tr[u][s[j]];
			if(ct[u]) {
				if(i - pr[u] >= k)
					pr[u] = i, ct[u]++;
			} else {
				pr[u] = i;
				ct[u] = 1;
			}
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
			int u = 0;
			for(j = 0; j < k; j++) {
				if(!tr[u][t[j]])
					break;
				u = tr[u][t[j]];
			}
			if(j < k) puts("0");
			else printf("%d\n", ct[u]);
		}
	}
}
