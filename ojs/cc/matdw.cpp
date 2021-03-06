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

#define left asds
#define printf asdas

void expect(bool cond) {
	if(!cond) while(1);
}

int left = 500;

void reg_op() {
	left--;
	expect(left >= 0);
}

struct hd_t {
	int id;
	int p, r, w, c;
	double tmp;
	void read(int id) { this->id = id; scanf("%d %d %d %d", &p, &r, &w, &c); }
};
vector<hd_t> hds_t;

template<typename func>
hd_t best(func eval, vector<hd_t> hds=::hds_t) {
	for(hd_t &h : hds)
		h.tmp = eval(h);
	return *min_element(hds.begin(), hds.end(), [](hd_t a, hd_t b) { return a.tmp < b.tmp; });
}


hd_t cheap_fast() {
	return best([](hd_t h) { return h.p * 5 + h.r + h.w; });
}

vector<pii> data[1123];

struct hd {
	int id;
	int r, w, c;
	// pair (client, p)
	int used;
	int tmp;
	hd() {}
	hd(hd_t h, int i) : id(i), r(h.r), w(h.w), c(h.c), used(0) { data[id].resize(h.c, pii(-1, -1)); }
	void wipe();
};

vector<hd> hds;

hd_t at_least(int x) {
	vector<hd_t> H;
	for(hd_t h : hds_t)
		if(h.c >= x)
			return h;
	expect(!H.empty());
	return *H.begin();
	if(hds.size() >= 950) return best([](hd_t h) { return -h.c; }, H);
	return best([](hd_t h) { return h.p + (h.r + h.w) * 2; }, H);
}


#define print(args...) do { fprintf(stdout, args); fflush(stdout); } while(0)

#define debug(args...) fprintf(stderr, args)

void buy_hd(hd_t h) {
	expect(hds.size() < 1050);
	reg_op();
	print("p b %d\n", h.id);
	int x = hds.size();
	hds.pb(hd(h, x));
}

// client positions
vector<set<pii>> cl[112345];

void hd::wipe() {
	for(int i = 0; i < used; i++) {
		pii p = data[id][i];
		expect(cl[p.fst][p.snd].erase(pii(id, i)) > 0);
		data[id][i] = pii(-1, -1);
	}
	used = 0;
}

template<typename func>
hd best(func eval, vector<hd> hds=::hds) {
	for(hd &h : hds)
		h.tmp = eval(h);
	return *min_element(hds.begin(), hds.end(), [](hd a, hd b) { return a.tmp < b.tmp; });
}

int get_available(int size, int forbid=-1) {
	vector<hd> H;
	for(hd &h : hds)
		if(h.c >= size && h.used == 0 && h.id != forbid)
			H.pb(h);
	auto eval = [](hd h) { return h.w; };
	if(!H.empty()) return best(eval, H).id;
	for(hd &h : hds)
		if(h.c - h.used >= size && h.id != forbid)
			H.pb(h);
	if(!H.empty()) return best(eval, H).id;
	if(left > 0 && hds.size() < 1050) {
		hd_t h = at_least(size);
		expect(h.c >= size);
		buy_hd(h);
		return hds.back().id;
	} else {
		return -1;
		for(hd h : hds)
			if(h.c >= size)
				H.pb(h);
		if(H.empty()) return -1;
		int id = max_element(H.begin(), H.end(), [](hd a, hd b) { return a.c - a.used < b.c - b.used; })->id;
		if(hds[id].c == hds[id].used) return -1;
		return id;
	}
}

int store(int cid, int q, int hid, bool fst=true) {
	int &us = hds[hid].used;
	us = min(us, hds[hid].c - q);
	expect(us >= 0);
	if(fst) print("p s %d %d\n", hid, us);
	for(int i = 0; i < q; i++) {
		pii p = data[hid][us + i];
		if(p.fst != -1) expect(cl[p.fst][p.snd].erase(pii(hid, us + i)) > 0);
		data[hid][us + i] = pii(cid, i);
		cl[cid][i].insert(pii(hid, us + i));
	}
	int bus = us;
	us += q;
	return bus;
}

int penalty;

int main() {
	int n, h;
	scanf("%d %d", &n, &h);
	for(int i = 0; i < h; i++)
		hds_t.pb(hd_t()), hds_t.back().read(i);
	scanf("%d", &penalty);
	double dpl = (penalty - 50000 + 300000) / 1e6;
	hd_t ch = cheap_fast();
	for(int x = 0; x < (2000 + ch.c - 1) / ch.c && x <= 250; x++)
		buy_hd(ch);
	while(n--) {
		print("g %d\n", n);
		int op, id;
		scanf("%d %d", &op, &id);
		if(op == 0) { // store
			int q;
			scanf("%d", &q);
			cl[id].resize(q);
			int hid = get_available(q);
			if(hid == -1) print("p s -1 -1\n");
			else {
				int k = store(id, q, hid);
				if(false && left > 0 && (rand() / double(RAND_MAX)) < dpl) {
					reg_op();
					int hid2 = get_available(q, hid);
					int s = store(id, q, hid2, false);
					print("p cp %d %d %d %d %d\n", hid, k, q, hid2, s);
				}
			}
		} else if(op == 1) { // retrieve
			int p;
			scanf("%d", &p);
			if(cl[id][p].empty()) print("p i -1 -1\n");
			else {
				pii da = *cl[id][p].begin();
				expect(data[da.fst][da.snd] == pii(id, p));
				print("p i %d %d\n", da.fst, da.snd);
			}
		} else { // crash
			hds[id].wipe();
			left++;
		}
	}
	print("end\n");
}
