#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb insert
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

#define exp adasd

int n;

struct exp {
	string str;
	int bm;
	bool operator < (exp o) const { return str < o.str; }
};

set<exp> E(int, bool);
set<exp> T(int, bool);
set<exp> F(int, bool);

set<exp> E(int l, bool c) {
	if(l == 0) return {};
	set<exp> ans;
	set<exp> A = E(l - 1, true), B = T(l - 1, true);
	if(c) for(exp x : T(l, false)) ans.pb(x);
	ans = B;
	for(exp a : A)
		for(exp b : B)
			ans.pb(exp{a.str + "|" + b.str, a.bm | b.bm});
	return ans;
}

set<exp> T(int l, bool c) {
	if(l == 0) return {};
	set<exp> ans;
	set<exp> A = T(l - 1, true), B = F(l - 1, true);
	if(c) for(exp x : T(l, false)) ans.pb(x);
	ans = B;
	for(exp a : A)
		for(exp b : B)
			ans.pb(exp{a.str + "&" + b.str, a.bm & b.bm});
	return ans;
}

exp X, Y, Z;

set<exp> F(int l, bool c) {
	set<exp> ans = {X, Y, Z};
	if(l == 0) return ans;
	set<exp> A = E(l - 1, true), B = F(l - 1, true);
	for(exp a : A)
		ans.pb(exp{"(" + a.str + ")", a.bm});
	for(exp b : B)
		ans.pb(exp{"!" + b.str, ((1 << 8) - 1) ^ b.bm});
	return ans;
}

string ans[1123];

int main() {
	int i, j;
	X.str = "x";
	X.bm = (1 << 4) - 1;
	Y.str = "y";
	Y.bm = (1 << 0) | (1 << 1) | (1 << 4) | (1 << 5);
	Z.str = "z";
	Z.bm = (1 << 0) | (1 << 2) | (1 << 4) | (1 << 6);
	set<exp> all = T(5, true);
	for(exp x : E(5, true)) all.pb(x);
	for(exp x : F(5, true)) all.pb(x);
	//for(exp x : T(5)) all.pb(x);
	//for(exp x : E(5)) all.pb(x);
	for(exp a : all) {
		if(ans[a.bm].size() == 0) { ans[a.bm] = a.str; continue; }
		if(a.str.size() < ans[a.bm].size()) { ans[a.bm] = a.str; continue; }
		if(a.str.size() == ans[a.bm].size()) { ans[a.bm] = min(ans[a.bm], a.str); continue; }
	}
	int n;
	scanf("%d", &n);
	while(n--) {
		int bm = 0;
		for(i = 0; i < 8; i++) {
			char c;
			scanf(" %c", &c);
			bm = (bm << 1) + (c == '1');
		}
		printf("%s\n", ans[bm].c_str());
	}
}
