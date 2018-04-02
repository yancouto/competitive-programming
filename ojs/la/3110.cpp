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

int mt[2][112], st[2][112], sn[2];
string E[2];

int memo[59][50][109];
int solve(int l1, int l2, int len) {
	if(len >= 100) return 1e8;
	if(l1 == E[0].size() && l2 == E[1].size()) return 0;
	int &r = memo[l1][l2][len];
	if(r != -1) return r;
	if(l1 < E[0].size() && E[0][l1] == ')') return r = solve(l1 + 1, l2, len);
	if(l2 < E[1].size() && E[1][l2] == ')') return r = solve(l1, l2 + 1, len);
	if(l1 < E[0].size() && E[0][l1] != 'a' && E[0][l1] != 'b') {
		if(E[0][l1] == '*') return r = min(solve(mt[0][l1 + 1] + 1, l2, len + 1), solve(l1 + 1, l2, len));
		if(E[0][l1] == '|') return r = solve(mt[0][l1 + 1] + 1, l2, len);
		if(E[0][mt[0][l1] - 1] == '*') return r = min(solve(mt[0][l1] + 1, l2, len), solve(l1 + 1, l2, len));
		if(E[0][mt[0][l1 + 1] + 1] == '|') return r = min(solve(l1 + 1, l2, len), solve(mt[0][l1 + 1] + 2, l2, len));
		return r = solve(l1 + 1, l2, len);
	}
	if(l2 < E[1].size() && E[1][l2] != 'a' && E[1][l2] != 'b') {
		if(E[1][l2] == '*') return r = min(solve(l1, mt[1][l2 + 1] + 1, len + 1), solve(l1, l2 + 1, len));
		if(E[1][l2] == '|') return r = solve(l1, mt[1][l2 + 1] + 1, len);
		if(E[1][mt[1][l2] - 1] == '*') return r = min(solve(l1, mt[1][l2] + 1, len), solve(l1, l2 + 1, len));
		if(E[1][mt[1][l2 + 1] + 1] == '|') return r = min(solve(l1, l2 + 1, len), solve(l1, mt[1][l2 + 1] + 2, len));
		return r = solve(l1, l2 + 1, len);
	}
	r = 1e8;
	if(l1 < E[0].size() && len < 100) r = 1 + solve(l1 + 1, l2, len);
	if(l2 < E[1].size() && len < 100) r = min(r, 1 + solve(l1, l2 + 1, len));
	if(l2 < E[1].size() && l1 < E[0].size() && len < 100) r = min(r, (E[0][l1] != E[1][l2]) + solve(l1 + 1, l2 + 1, len));
	//if(len1 <= 4 && len2 <= 4) printf("(%d, %d, %d, %d) = %d\n", l1, l2, len1, len2, r);
	return r;
}

int solve() {
	for(int k = 0; k < 2; k++) {
		for(int i = 0; i < E[k].size(); i++) {
			if(E[k][i] == '(') st[k][sn[k]++] = i;
			else if(E[k][i] == ')') { mt[k][i] = st[k][sn[k] - 1]; mt[k][st[k][--sn[k]]] = i; }
			else mt[k][i] = i;
		}
	}
	memset(memo, -1, sizeof memo);
	return solve(0, 0, 0);
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t;
	cin >> t;
	while(t--) {
		cin >> E[0];
		cin >> E[1];
		cout << solve() << '\n';
	}
}
