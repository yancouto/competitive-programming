#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

char c;
inline void rd(int &x) {
	while(isspace(c = getchar_unlocked()));
	x = (c - '0');
	while(isdigit(c = getchar_unlocked()))
		x = (x << 3) + (x << 1) + (c - '0');
}

const int M = 1123456 << 2;
ll tr[M], lz[M]; ll sum;
inline void unlaze(int i, int l, int r) {
	tr[i] += lz[i];
	if(l != r)
		lz[2 * i] += lz[i],
		lz[2 * i + 1] += lz[i];
	lz[i] = 0;
}
void add(int i, int l, int r, int ql, int qr, ll x) {
	unlaze(i, l, r);
	if(i == 1) sum += ll(qr - ql + 1) * x;
	//if(i == 1) printf("(%d, %d) += %lld\n", ql, qr, x);
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) {
		lz[i] = x;
		unlaze(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	add(2 * i, l, m, ql, qr, x);
	add(2 * i + 1, m + 1, r, ql, qr, x);
	tr[i] = max(tr[2 * i], tr[2 * i + 1]);
}
inline ll get_root(int i, int l, int r) {
	unlaze(i, l, r);
	return tr[i];
}

const int X = 1123456;

const int bad = SHRT_MAX;

struct seg_ {
	short l, r, row;
	inline bool bad() { return row == ::bad; }
	inline bool empty() { return l > r; }
} seg[41234567];

int en = 0;
int new_inter(short l, short r, short i, int val=-1) {
	assert(en < 21234567);
	seg[en] = seg_{l, r, i};
	return en++;
}

struct rm_ord {
	bool operator() (int i, int j) {
		if(seg[i].row != seg[j].row)
			return seg[i].row < seg[j].row;
		return i < j;
	}
};

struct ord {
	bool operator() (int i, int j) {
		if(seg[i].l != seg[j].l)
			return seg[i].l < seg[j].l;
		return i < j;
	}
};

int n, m, k;
set<int, rm_ord> rm;

void add_inter(set<int, ord> &s, int sid) {
	seg_ &S = seg[sid];
	if(S.empty()) return;
	auto nx = s.upper_bound(sid);
	while(nx != s.end() && seg[*nx].l <= S.l)
		++nx;
	--nx;
	int pr = seg[*nx].r;
	seg[*nx].r = S.l - 1;
	if(seg[*nx].bad())
		add(1, 0, m - k, S.l, min<int>(S.r, pr), 1);
	auto it = s.insert(sid).first;
	rm.insert(sid);
	if(pr > S.r) {
		int ns = new_inter(S.r + 1, pr, seg[*nx].row);
		s.insert(ns);
		if(!seg[ns].bad()) rm.insert(ns);
		return;
	}
	if(seg[*nx].empty()) {
		int j = *nx;
		s.erase(j);
		rm.erase(j);
	}
	while(true) {
		nx = next(it);
		if(nx == s.end() || seg[*nx].l > S.r) break;
		seg_ &T = seg[*nx];
		if(T.r <= S.r) {
			if(T.bad())
				add(1, 0, m - k, T.l, T.r, 1);
			else
				rm.erase(*nx);
			s.erase(nx);
		} else { // break
			int j = *nx;
			s.erase(j);
			if(T.bad())
				add(1, 0, m - k, T.l, S.r, 1);
			T.l = S.r + 1;
			s.insert(j);
			break;
		}
	}
}

set<int, ord> s[X];

int A[3123][3123];

void deb(int i, int l, int r) {
	if(l == r) return (void) printf("%lld ", tr[i]);
	int m = (l + r) / 2;
	deb(2 * i, l, m);
	deb(2 * i + 1, m + 1, r);
	if(i == 1) putchar('\n');
}

int main() {
	rd(n); rd(m); rd(k);
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			rd(A[i][j]);
	for(i = 0; i < X; i++)
		s[i].insert(new_inter(0, m - k, bad));
	ll best = 0, sum = 0;
	for(i = 0; i < n; i++) {
		while(!rm.empty() && seg[*rm.begin()].row <= i - k) {
			int j = *rm.begin();
			rm.erase(j);
			seg[j].row = bad;
			//printf("deleting from %d\n", seg[j].val);
			add(1, 0, m - k, seg[j].l, seg[j].r, -1);
		}
		for(j = 0; j < m; j++) {
			//printf(">> Add %d\n", A[i][j]);
			add_inter(s[A[i][j]], new_inter(max(0, j - k + 1), min(m - k, j), i, A[i][j]));
		}
		//deb(1, 0, m - k );
		if(i >= k - 1) {
			best = max(best, get_root(1, 0, m - k));
			sum += ::sum;
		}
	}
	printf("%lld %lld\n", best, sum);
}
