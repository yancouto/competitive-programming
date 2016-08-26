#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int p[26][26];
int n;
char str[1000009];
ll memo[500009];

ll solve(int i) {
	if(i >= n / 2) return 0;
	ll &r = memo[i];
	if(r != -1) return r;
	if(str[i] == str[n-1-i]) return r = solve(i + 1);
	r = LLONG_MAX;
	for(int j = 0; j < 26; j++)
		r = min(r, solve(i + 1) + p[str[i] - 'a'][j] + p[str[n-1-i] - 'a'][j]);
	return r;
}

struct no {
	int l, d;
	no() {}
	no(int a, int b) : l(a), d(b) {}
	bool operator < (const no &o) const { return d > o.d; }
};

int seen[26];
void dij(int i) {
	memset(seen, 0, sizeof seen);
	priority_queue<no> pq;
	pq.push(no(i, 0));
	while(!pq.empty()) {
		no x = pq.top(); pq.pop();
		if(seen[x.l]) continue;
		seen[x.l] = 1;
		p[i][x.l] = x.d;
		for(int j = 0; j < 26; j++)
			pq.push(no(j, x.d + p[x.l][j]));
	}
}


int main() {
	int i, j;
	for(i = 0; i < 26; i++)
		for(j = 0; j < 26; j++)
			scanf("%d", &p[i][j]);
	for(i = 0; i < 26; i++)
		dij(i);
	scanf("%s", str); n = strlen(str);
	memset(memo, -1, sizeof memo);
	printf("%I64d\n", solve(0));
	return 0;
}
