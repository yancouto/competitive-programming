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

char s[1123], o[256];
int st[1123];

int main() {
	int i, sn;
	fgets(s, sizeof s, stdin);
	o['['] = ']'; o['('] = ')';
	while(true) {
		fgets(s, sizeof s, stdin);
		if(feof(stdin)) return 0;
		sn = 0;
		for(i = 0; s[i] != '\n'; i++)
			if(s[i] == '(' || s[i] == '[')
				st[sn++] = s[i];
			else if(sn == 0 || o[st[sn - 1]] != s[i]) {
				break;
			} else sn--;
		if(s[i] == '\n' && sn == 0) puts("Yes");
		else puts("No");
	}
}
