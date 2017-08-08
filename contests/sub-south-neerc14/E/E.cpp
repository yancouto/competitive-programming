#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 5e6+7;
const int inf = 1e8;

int n, m;
int a[N];
ll r[N];
int p[N];

int seg[N];
int bit[N];

int build (int i, int l, int r) {
	if (l == r) {
		seg[i] = l;
	} else {
		int md = (l+r)/2;
		int x = build(i+i, l, md);
		int y = build(i+i+1, md+1, r);
		if (a[x] < a[y])
			seg[i] = x;
		else
			seg[i] = y;
	}

	return seg[i];
}

int get (int u, int l, int r, int ql, int qr) {
	if (qr < l || r < ql) return -1;
	if (ql <= l && r <= qr) return seg[u];
	int md = (l+r)/2;
	int x = get(u+u, l, md, ql, qr);
	int y = get(u+u+1, md+1, r, ql, qr);

	if (x == -1)
		return y;
	else if (y == -1)
		return x;
	else if (a[x] < a[y])
		return x;
	else
		return y;
}

int upd (int u, int l, int r, int i) {
	if (i < l || r < i) return seg[u];
	if (l == r && i == l) return seg[u];
	int md = (l+r)/2;
	int x = upd(u+u, l, md, i);
	int y = upd(u+u+1, md+1, r, i);

	if (a[x] < a[y])
		seg[u] = x;
	else
		seg[u] = y;
	return seg[u];
}

void add (int i, int x) {
	for (i+=2; i < N; i+=(i&-i))
		bit[i] += x;
}

int get (int i) {
	int x = 0;
	for (i+=2; i > 0; i-=(i&-i))
		x += bit[i];
	return x;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		p[i] = i;
	}

	stable_sort(p, p+n, [] (int i, int j) {
		return a[i] < a[j];
	});

	ll res = 0;
	build(1, 0, n-1);
	for (int _i = 0; _i < n; _i++) {
		int i = p[_i];
		r[i] = get(n-i);
		res += r[i];
		add(n-i,1);
	}
	cout << res << endl;
	for (int i = 0; i < m; i++) {
		int q;
		cin >> q;
		q--;
		//cout << "query " << q << " ============ " << endl;

		if (a[q] != inf) {
			int x = n;
			do {
				x = get(1, 0, n-1, q, n-1);
				//cout << "found " << x << " " << r[x] << endl;
				a[x] = inf;
				res -= r[x];
				r[x] = 0;
				upd(1, 0, n-1, x);
			} while (x != q);
		}

		cout << res << endl;
	}
}
