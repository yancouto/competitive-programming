#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
ll inf = 1e18 + 1100;

char s[2009];
int seen[4009][2009], t;
pii memo[4009][2009];
pii solve(int l, int r) {
	if(l > r) return pii(r - l + 1, 1);
	pii &ans = memo[l][r];
	if(seen[l][r] == t) return ans;
	seen[l][r] = t;
	ans = solve(l + 1, r - (s[l] == s[r])); ans.fst += 2;
	if(s[l] != s[r]) {
		pii o = solve(l, r - 1); o.fst += 2;
		if(ans.fst == o.fst) ans.snd = min(ans.snd + o.snd, inf);
		else if(ans.fst > o.fst) ans = o;
	}
	return ans;
}

deque<char> b, e;
void build(int l, int r, ll k) {
	if(l > r) {
		if(r == l - 2) e.pop_front();
		for(char c : b) putchar(c);
		for(char c : e) putchar(c);
		putchar('\n');
		b.clear(); e.clear();
		return;
	}
	if(s[l] <= s[r]) {
		pii a = solve(l + 1, r - (s[l] == s[r]));
		if(solve(l, r).fst == a.fst + 2) {
			if(k > a.snd)
				k -= a.snd;
			else {
				b.pb(s[l]); e.push_front(s[l]);
				return build(l + 1, r - (s[l] == s[r]), k);
			}
		}
		b.pb(s[r]); e.push_front(s[r]);
		return build(l, r - 1, k);
	} else {
		pii a = solve(l, r - 1);
		if(solve(l, r).fst == a.fst + 2) {
			if(k > a.snd)
				k -= a.snd;
			else {
				b.pb(s[r]); e.push_front(s[r]);
				return build(l, r - 1, k);
			}
		}
		b.pb(s[l]); e.push_front(s[l]);
		return build(l + 1, r, k);

	}
}

int main() {
	int i, j, sz; ll k;
	while(scanf("%s %lld", s, &k) != EOF) {
		t++;
		pii o = solve(0, strlen(s)-1);
		if(o.snd < k) puts("NONE");
		else build(0, strlen(s)-1, k);
	}
}
