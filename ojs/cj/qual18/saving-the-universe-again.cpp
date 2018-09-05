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

int n;
char s[1123];

ll eval() {
	ll cur = 1, tot = 0;
	for(int i = 0; i < n; i++)
		if(s[i] == 'C')
			cur <<= 1;
		else
			tot += cur;
	return tot;
}

int main() {
	int i, h;
	for_tests(tn, tt) {
		scanf("%d %s", &h, s);
		n = strlen(s);
		int ct = 0;
		for(i = 0; i < n; i++) ct += (s[i] == 'S');
		printf("Case #%d: ", tt);
		if(ct > h) { puts("IMPOSSIBLE"); continue; }
		for(ct = 0; eval() > h; ct++) {
			for(i = n - 1; s[i] == 'C'; i--);
			for(; s[i] != 'C'; i--);
			swap(s[i], s[i + 1]);
		}
		printf("%d\n", ct);
	}
}
