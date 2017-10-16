
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 412345;
int visi[N];
int mrk[N];

struct dt {
	int x[10];
};

dt join(dt a, dt b) {
	dt d;
	for(int i = 0; i < 10; i++)
		d.x[i] = a.x[i] + b.x[i];
	return d;
}


dt tr[N];
int lz[N];

void deb(int i, int l, int r) {
	return;
	printf("[%d,%d] %d: ", l, r, i);
	for(int j = 0; j < 10; j++)
		printf("%d ", tr[i].x[j]);
	putchar('\n');
}

void unlaze(int i, int l, int r) {
	if(lz[i] == 0) return;
	rotate(tr[i].x, tr[i].x + (lz[i] % 10), tr[i].x + 10);
	if(l != r) lz[2 * i] += lz[i], lz[2 * i + 1] += lz[i];
	lz[i] = 0;
}

#define debug(...) ((void)0)

void add(int i, int l, int r, int p, int x) {
	unlaze(i, l, r);
	if(l == r) {
		debug("%d: adding %d on %d\n", i, x, p);
		tr[i].x[0] = x;
		for(int j = 1; j < 10; j++)
			tr[i].x[j] = (tr[i].x[j - 1] * tr[i].x[j - 1]) % 2010;
		assert((tr[i].x[9] * tr[i].x[9]) % 2010 == x);
		return;
	}
	int m = (l + r) / 2;
	if(p <= m) add(2 * i, l, m, p, x);
	else add(2 * i + 1, m + 1, r, p, x);
	unlaze(2 * i, l, m);
	unlaze(2 * i + 1, m + 1, r);
	tr[i] = join(tr[2 * i], tr[2 * i + 1]);
}


int get(int i, int l, int r, int ql, int qr) {
	unlaze(i, l, r);
	deb(i, l, r);
	if(l > qr || r < ql) { debug("out\n"); return 0; }
	if(l >= ql && r <= qr) { debug("in\n"); return tr[i].x[0]; }
	int m = (l + r) / 2;
	return get(2 * i, l, m, ql, qr) + get(2 * i + 1, m + 1, r, ql, qr);
}

void cycle(int i, int l, int r, int ql, int qr) {
	unlaze(i, l, r);
	deb(i, l, r);
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) {
		lz[i] = 1;
		unlaze(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	cycle(2 * i, l, m, ql, qr);
	cycle(2 * i + 1, m + 1, r, ql, qr);
	tr[i] = join(tr[2 * i], tr[2 * i + 1]);
}

int bit[N];
int get(int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[i];
	return sum;
}
int get(int l, int r) { return get(r) - get(l - 1); }
int add(int i, int x) {
	for(i += 2; i < N; i += (i & -i))
		bit[i] += x;
}

int a[N];
int b[N];

void upd_quad(int l, int r) {
	for(int j = l; j <= r; j++) b[j] = (b[j] * b[j]) % 2010;
}

int get_quad(int l, int r) {
	int sum = 0;
	for(int i = l; i <= r; i++)
		sum += b[i];
	return sum;
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("enigmatic.in", "r", stdin);
	freopen("enigmatic.out", "w", stdout);
#endif

	int mx = 1;
	mrk[0] = 1;
	for (int i = 1; i < 2010; i++) {
		int j = i;
		int cnt = 0;
		while (visi[j] != i) {
			visi[j] = i;
			j = (j*j)%2010;
			cnt++;
		}
		if(j == i)
			mrk[i] = 1;
	}
	int i, n, l, r, k, m;

	scanf("%d", &n);
	set<int> s;
	for(i = 0; i < n; i++) {
		a[i] = rand() % 2010;
		scanf("%d", &a[i]);
		//printf("a[%d] = %d (%d)\n", i, a[i], mrk[a[i]]);
		b[i] = a[i];
		if(mrk[a[i]]) add(1, 0, n - 1, i, a[i]);
		else s.insert(i), add(i, a[i]);
	}
	scanf("%d", &m);
	for(i = 0; i < m; i++) {
		debug("----\n");
		k = (rand() % 2) + 1; l = rand() % n; r = rand() % n; if(l > r) swap(l, r);
		scanf("%d %d %d", &k, &l, &r); l--; r--;
		//printf("k %d l %d r %d\n", k, l, r);
		if(k == 1) {
			//upd_quad(l, r);
			cycle(1, 0, n - 1, l, r);
			for(auto it = s.lower_bound(l); it != s.end() && *it <= r;) {
				int j = *it;
				add(j, -a[j]);
				a[j] = (a[j] * a[j]) % 2010;
				if(mrk[a[j]]) {
					add(1, 0, n - 1, j, a[j]);
					it = s.erase(it);
				} else {
					add(j, a[j]);
					++it;
				}
			}
		} else {
			int s = get(1, 0, n - 1, l, r) + get(l, r);
			printf("%d\n", s);
			//printf("vs %d\n", get_quad(l, r));
			//assert(s == get_quad(l, r));
		}
	}
}

