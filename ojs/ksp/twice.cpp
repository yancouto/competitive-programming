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

int p3[20];

inline int dig(int bm, int i) {
	return (bm / p3[i]) % 3;
}

char s[212];
char ans[212];

int seen[109][60000][2][2], tempo;
bool solve(int i, int bm, bool pre, bool l0) {
	if(!s[i]) { ans[i] = 0; return true; }
	if(seen[i][bm][pre][l0] == tempo) return false;
	seen[i][bm][pre][l0] = tempo;
	for(int d = 9; d >= 0; d--) {
		if(pre && d > s[i] - '0') continue;
		if((d || !l0) && dig(bm, d) == 2) continue;
		ans[i] = d + '0';
		if(solve(i + 1, bm + (d || !l0) * p3[d], pre && d == s[i] - '0', l0 && !d)) return true;
	}
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	int i, t;
	cin >> t;
	p3[0] = 1;
	for(i = 1; i < 10; i++)
		p3[i] = 3 * p3[i - 1];
	while(t--) {
		cin >> s;
		tempo++;
		solve(0, 0, true, true);
		for(i = 0; ans[i] == '0'; i++);
		cout << (ans + i) << '\n';
	}
}
