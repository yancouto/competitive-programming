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

char s[103][105];
map<vector<int>, int> memo;
int solve(vector<int> &v) {
	if(memo.count(v)) return memo[v];
	int &r = memo[v], i; r = 0;
	for(i = 0; i < v.size(); i++) {
		if(!s[i][v[i]]) continue;
		v[i]++;
		r = max(r, solve(v));
		v[i]--;
	}
	char c = s[0][v[0]];
	for(i = 1; i < v.size() && c == s[i][v[i]]; i++);
	if(i == v.size() && c) {
		for(i = 0; i < v.size(); i++) v[i]++;
		r = max(r, 1 + solve(v));
		for(i = 0; i < v.size(); i++) v[i]--;
	}
	return r;
}

int main() {
	int n;
	while(scanf("%d", &n) != EOF && n) {
		for(int i = 0; i < n; i++) scanf("%s", s[i]);
		memo.clear(); vector<int> v(n, 0);
		printf("%d\n", solve(v));
	}
}
