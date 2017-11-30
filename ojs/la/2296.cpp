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

int suit_val[256];
int val_val[256];

struct card {
	int v;
	char s;
	bool operator < (card o) const {
		if(v != o.v) return v < o.v;
		return s < o.s;
	}
	inline int num() { return suit_val[s] * 13 + (v - 2); }
	inline void prn() { printf("%c%c ", "--23456789TJQKA"[v], s); }
	inline void read() {
		char c;
		scanf(" %c %c", &c, &s);
		v = val_val[c];
	}
};
#define left lft
int val[11];
enum {
	NOTHING = 0,
	ONE_PAIR,
	TWO_PAIR,
	THREE,
	STRAIGHT,
	FLUSH,
	FULL_HOUSE,
	FOUR,
	ST_FLUSH,
	ROYAL
};
vector<pii> hshs;
bitset<380204032> bad;

int eval(vector<card> h) {
	sort(h.begin(), h.end());
	assert(h.size() == 5);
	int hsh = 0;
	for(card c : h) hsh = 52 * hsh + c.num();
	//for(card c : h) c.prn(); putchar('\n');
	//printf("hsh %d\n", hsh);
	//assert(memo.count(hsh));
	//printf(" = %d = %d\n", memo[hsh], val[memo[hsh]]);
	if(bad[hsh]) return 0;
	//assert(lower_bound(hshs.begin(), hshs.end(), pii(hsh, 0))->fst == hsh);
	//printf("%d->%d\n", hsh, lower_bound(hshs.begin(), hshs.end(), pii(hsh, 0))->snd);
	return val[lower_bound(hshs.begin(), hshs.end(), pii(hsh, 0))->snd];
}
int eval_(vector<card> h) {
	assert(h.size() == 5);
	sort(h.begin(), h.end());
	int hsh = 0;
	for(card c : h) hsh = 52 * hsh + c.num();
	hshs.pb(pii(hsh, 0));
	int &v = hshs.back().snd;
	int i;
	for(i = 1; i < 5 && h[i].v == h[i - 1].v + 1; i++);
	bool straight = (i == 5 || (i == 4 && h[0].v == 2 && h[4].v == 14));
	for(i = 1; i < 5 && h[i].s == h[i - 1].s; i++);
	bool flush = (i == 5);
	if(straight && flush && h[0].v == 10) return v = ROYAL;
	if(straight && flush) return v = ST_FLUSH;
	vector<int> eq;
	int cur = 1;
	for(i = 1; i < 5; i++) {
		if(h[i].v != h[i - 1].v) {
			eq.pb(cur);
			cur = 0;
		}
		cur++;
	}
	eq.pb(cur);
	sort(eq.begin(), eq.end());
	if(eq.back() == 4) return v = FOUR;
	if(eq[0] == 2 && eq[1] == 3) return v = FULL_HOUSE;
	if(flush) return v = FLUSH;
	if(straight) return v = STRAIGHT;
	if(eq.back() == 3) return v = THREE;
	if(eq.size() == 3 && eq[1] == 2 && eq[2] == 2) return v = TWO_PAIR;
	if(eq.back() == 2) return v = ONE_PAIR;
	bad[hsh] = 1;
	return v = NOTHING;
	assert(false);
}

vector<int> mrk;
vector<card> hd;
vector<card> left;

ll tot;
int ct;
vector<vector<int>> g_size[6], h_size;
vector<int> cur;

void gen(int i) {
	if(i == 52 - 5) {
		g_size[cur.size()].pb(cur);
		return;
	}
	gen(i + 1);
	if(cur.size() < 5) {
		cur.pb(i);
		gen(i + 1);
		cur.pop_back();
	}
}

void gen2(int i) {
	if(i == 5) {
		h_size.pb(cur);
		return;
	}
	gen2(i + 1);
	if(cur.size() < 5) {
		cur.pb(i);
		gen2(i + 1);
		cur.pop_back();
	}
}

vector<card> ccur, all;
void gen3(int i) {
	if(ccur.size() == 5) {
		eval_(ccur);
		//if(bad[hshs.back().fst]) assert(hshs.back().snd == 0);
		//else assert(hshs.back().snd);
		//if(ccur[4].v == 14 && ccur[3].v == 14 && ccur[2].v == 14 && ccur[1].v == 14 && ccur[0].v == 2) {
		//	eval(ccur);
		//	for(card c : ccur) c.prn(); printf("\n");
		//}
		return;
	}
	if(i == 52) return;
	gen3(i + 1);
	ccur.pb(all[i]);
	gen3(i + 1);
	ccur.pop_back();
}

void rpl() {
	tot = ct = 0;
	for(vector<int> &f : g_size[mrk.size()]) {
		for(int i = 0; i < int(mrk.size()); i++)
			hd[mrk[i]] = left[f[i]];
		tot += eval(hd);
		ct++;
	}
}

double bst;

void go(vector<card> &h) {
	for(vector<int> &f : h_size) {
		hd = h;
		mrk = f;
		rpl();
		bst = max(bst, double(tot) / ct);
	}
}

double solve(vector<card> &h) {
	left.clear();
	set<card> all;
	for(int v = 2; v <= 14; v++)
		for(char s : string("cdhs"))
			all.insert(card{v, s});
	for(card c : h) all.erase(c);
	for(card x : all) {
		//printf("add "); x.prn(); putchar('\n');
		left.pb(x);
	}
	bst = 0;
	vector<card> hh = h;
	go(hh);
	return bst;
}

int main() {
	int i = 0;
	for(char c : "cdhs") suit_val[c] = i++;
	i = 2;
	for(char c : "23456789TJQKA") val_val[c] = i++;
	gen(0);
	gen2(0);
	for(int i = 2; i <= 14; i++)
		for(char c : string("cdhs"))
			all.pb(card{i, c});
	gen3(0);
	sort(hshs.begin(), hshs.end());
	for_tests(tn, tt) {
		for(i = 1; i < 10; i++) scanf("%d", &val[i]);
		for_tests(n, j) {
			vector<card>  h(5);
			for(i = 0; i < 5; i++)
				h[i].read();
			printf("%.10f\n", solve(h));
		}
	}
}
