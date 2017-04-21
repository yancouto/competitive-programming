#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

char s[1123]; int g[1123];
bool go(int i, int mn, bool pre) {
	if(!s[i]) return true;
	if(!pre) {
		g[i] = 9;
		return go(i + 1, 9, false);
	}
	int x = s[i] - '0';
	if(x < mn && pre) return false;
	g[i] = x;
	//printf("at %d trying %d\n", i, x);
	if(go(i + 1, x, pre)) return true;
	if(x == 0 || (x - 1 < mn && pre)) return false;
	g[i] = x - 1;
	//printf("at %d trying %d\n", i, x - 1);
	return go(i + 1, x - 1, false);
}

int main() {
	int i;
	for_tests(t, tt) {
		scanf("%s", s);
		go(0, 0, true);
		bool l0 = true;
		printf("Case #%d: ", tt);
		for(i = 0; s[i]; i++) {
			if(g[i]) putchar('0' + g[i]), l0 = false;
			else if(!l0) putchar('0' + g[i]);
		}
		putchar('\n');
	}
}
