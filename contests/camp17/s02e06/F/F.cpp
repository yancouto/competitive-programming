#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

const int N = 1e5+7;

struct vect {
	ll x[2];
	int d, i;

	bool operator == (const vect & ot) {
		return (x[0] == ot.x[0] && x[1] == ot.x[1]);
	}

	bool operator < (const vect & ot) const {
		if (x[0] != ot.x[0]) return x[0] < ot.x[0];
		return x[1] < ot.x[1];
	}
};
vect v[N];
int to[N];

struct line {
	vect a;
	bool ty;

	line (vect x, bool b) : a(x), ty(b) {}

	bool operator < (const line & ot) const {
		return a.x[ty] < ot.a.x[ty];
	}
};

int n;
// varia x[1]? secundária? qual?
map<int, set<line> > mp[2][2];
set<line>::iterator it, jt;
vect ord[N];

int getdir (int k) {
	if (v[k].x[0] == v[(k+1)%n].x[0] && v[k].x[1] < v[(k+1)%n].x[1])
		return 0;
	else if (v[k].x[1] == v[(k+1)%n].x[1] && v[k].x[0] > v[(k+1)%n].x[0])
		return 1;
	else if (v[k].x[0] == v[(k+1)%n].x[0])
		return 2;
	else
		return 3;
	/*if (v[k].x[1] == v[(k+1)%n].x[1] && v[k].x[0] < v[(k+1)%n].x[0])
		return 0;
	else if (v[k].x[0] == v[(k+1)%n].x[0] && v[k].x[1] < v[(k+1)%n].x[1])
 		return 1;
	else if (v[k].x[1] == v[(k+1)%n].x[1])
 		return 2;
	else
 		return 3;*/
}

void go (int k) {
	vect curr = v[k];

	while (true) {
		vect nxt;
		printf("%d %d dir %d\n", curr.x[0], curr.x[1], curr.d);
		if (curr.d == 0) {
			nxt.x[0] = nxt.x[1] = LLONG_MAX;
			nxt.d = -1;

			ll diag = curr.x[0]+curr.x[1];
			jt = mp[0][1][diag].lower_bound(line(curr, 0));
			if (jt != mp[0][1][diag].begin()) {
				--jt;

				vect cand;
				cand.x[1] = jt->a.x[1];
				cand.x[0] = diag - cand.x[1];
				cand.d = 3;
				printf("cand %d %d dir %d\n", cand.x[0], cand.x[1], cand.d);
				nxt = min(nxt, cand);
			}

			it = mp[1][1][diag].upper_bound(line(curr, 0));
			if (it != mp[1][1][diag].end()) {
				vect cand;
				cand.x[0] = jt->a.x[0];
				cand.x[1] = diag - cand.x[0];
				cand.d = 1;
				printf("cand %d %d dir %d\n", cand.x[0], cand.x[1], cand.d);
				nxt = min(nxt, cand);
			}

			if (nxt.x[0] == LLONG_MAX)
				assert(false);
		} else {
			printf("STAPH\n");
			return;
		}

		int ps = lower_bound(ord, ord+n, nxt) - ord;
		if (ps >= n && ord[ps].d == (curr.d+2)%4) {
			to[k] = ord[ps].i;
			to[ord[ps].i] = k;
			return;
		}
		curr = nxt;
	}
}

int main() {
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%lld %lld", &v[i].x[0], &v[i].x[1]);

	for (int i = 0; i < n; i++) {
		line a(v[i], (v[i].x[0] == v[(i+1)%n].x[0]));

		for (int p = a.a.x[a.ty]; p <= a.a.x[a.ty]; p++) {
			line b = a;
			b.a.x[!a.ty] = p;
			mp[a.ty][0][p-a.a.x[!a.ty]].insert(b);
			mp[a.ty][1][p+a.a.x[!a.ty]].insert(b);

			printf("%d %d at %d\n", b.a.x[0], b.a.x[1], a.ty);
		}
		to[i] = -1;
	}

	for (int i = 0; i < n; i++) {
		v[i].d = getdir(i);
		v[i].i = i;
		ord[i] = v[i];
	}

	sort(ord, ord+n);

	for (int i = 0; i < n; i++) {
		if (to[i] != -1) continue;
		go(i);
	}

	printf("%d\n", n/2);
	for (int i = 0; i < n; i++) {
		if (to[i] < i)
			printf("%d %d\n", i, to[i]);
	}
}
