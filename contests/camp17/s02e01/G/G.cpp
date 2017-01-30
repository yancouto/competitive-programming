#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<string, string> pss;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;
char s[1123];
map<set<pss>, int> all;
pss p[112345][5];

int main() {
	int i, j, k, l;
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &l);
		for(j = 0; j < l; j++) {
			scanf("%s", s);
			for(k = 0; s[k] != '='; k++);
			s[k] = 0;
			p[i][j] = pss(s, s + k + 1);
		}
		for(j = 0; j < (1 << l); j++) {
			set<pss> S;
			for(k = 0; k < l; k++)
				if((j >> k) & 1)
					S.insert(p[i][k]);
			all[S]++;
		}
	}
	int m;
	scanf("%d", &m);
	while(m--) {
		scanf("%d", &l);
		set<pss> S;
		for(j = 0; j < l; j++) {
			scanf("%s", s);
			for(k = 0; s[k] != '='; k++);
			s[k] = 0;
			S.insert(pss(s, s + k + 1));
		}
		printf("%d\n", all[S]);
	}
}
