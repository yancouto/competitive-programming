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
const int N = 2123;
char a[N], b[N];
int n, oc[256];
vector<int> ha[N], hb[N];

map<int, int> tr[5123456];
int en;

void proc(char *s) {
	int i, j;
	for(i = 0; i < n; i++) {
		for(j = 0; j < 256; j++) oc[j] = 0;
		int v = 0, ct = 0;
		for(j = i; j < i + n; j++) {
			if(!oc[s[j]]) oc[s[j]] = ++ct;
			if(!tr[v].count(oc[s[j]])) tr[v][oc[s[j]]] = en++;
			v = tr[v][oc[s[j]]];
		}
	}
}

int main() {
	int i, j;
	while(scanf("%d", &n) != EOF) {
		scanf("%s %s", a, b);
		for(i = n; i < 2 * n; i++)
			a[i] = a[i - n],
			b[i] = b[i - n];
		en = 1;
		proc(a);
		int ans = 0;
		char *s = b;
		for(i = 0; i < n; i++) {
			for(j = 0; j < 256; j++) oc[j] = 0;
			int v = 0, ct = 0;
			for(j = i; j < i + n; j++) {
				if(!oc[s[j]]) oc[s[j]] = ++ct;
				if(!tr[v].count(oc[s[j]])) break;
				v = tr[v][oc[s[j]]];
				ans = max(ans, j - i + 1);
			}
		}
		printf("%d\n", ans);
		for(i = 0; i < en; i++) tr[i].clear();
	}
}
