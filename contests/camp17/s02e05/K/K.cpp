#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;
char ln[1123][1123];
deque<string> o[1123], c[1123];
int st[1123];

void go(int l, int r, int d) {
	if(r < l) return;
	if(!ln[l][d] || (ln[l][d] != '*' && ln[l][d] != '#')) { st[l] = d; return go(l + 1, r, d); }
	int j = l;
	while(j < r && ln[l][d] == ln[j + 1][d]) j++;
	if(j == l) { st[l] = d; return go(l + 1, r, d); }
	if(ln[l][d] == '#') o[l].pb("ol"), c[j].push_front("/ol");
	else o[l].pb("ul"), c[j].push_front("/ul");
	go(l, j, d + 1);
	go(j + 1, r, d);
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int i = 0, j;
	while(true) {
		fgets(ln[n], sizeof ln[n], stdin);
		n++;
		if(feof(stdin)) break;
	}
	go(0, n - 1, 0);
	int cur = 0;
	for(i = 0; i < n; i++) {
		for(string &s : o[i]) {
			if(cur) puts("<li>");
			printf("<%s>\n", s.c_str()), cur++;
		}
		if(cur) printf("<li>\n");
		printf("%s", ln[i] + st[i]);
		if(cur) printf("</li>\n");
		for(string &s : c[i]) {
			printf("<%s>\n", s.c_str()), cur--;
			if(cur) puts("</li>");
		}
	}
}
