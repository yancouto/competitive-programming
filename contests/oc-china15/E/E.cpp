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

bool query(int x) { return (x % 4) >= 2; }
bool update(int x) { return (x % 4) < 2; }
const int L = -200009, R = 200009, N = 2123456;

int mid(int l, int r) {
	return (r - l) / 2 + l;
}

int ans[N], tr[N];
int x[N], y[N], p[N];
int query(int i, int l, int r, int x) {
	if(r < x) return 0;
	if(l >= x) return tr[i];
	int m = mid(l, r);
	return max(query(2 * i, l, m, x), query(2 * i + 1, m + 1, r, x));
}

void update(int i, int l, int r, int x, int val) {
	tr[i] = max(tr[i], val);
	//printf("tr[%d] = %d\n", i, tr[i]);
	if(l == r) return;
	int m = mid(l, r);
	if(x <= m) update(2 * i, l, m, x, val);
	else update(2 * i + 1, m + 1, r, x, val);
}

int main() {
	int i, n, a, b, j; char t;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf(" %c %d %d", &t, &a, &b);
		x[4*i] = x[4*i + 1] = i;
		x[4*i+2] = x[4*i+3] = i + 1;
		if(t == 'A')  {
			y[4*i] = a;
			y[4*i+1] = b;
		} else {
			y[4*i] = i - a;
			y[4*i+1] = i - b;
		}
		y[4*i+2] = y[4*i] + 1;
		y[4*i+3] = y[4*i+1];
	}
	n *= 4;
	for(i = 0; i < n; i++) {
		x[i] -= y[i];
		p[i] = i;
	}
	sort(p, p + n, [](int i, int j) {
		if(x[i] != x[j] || y[i] != y[j]) return pii(x[i], y[i]) > pii(x[j], y[j]);
		return (i % 4) < (j % 4);
	});
	for(j = 0; j < n; j++) {
		i = p[j];
		if(x[i] < 0) break;
		//printf("%d: (%d, %d)\n", i, x[i], y[i]);
		if(query(i)) ans[i] = query(1, L, R, y[i]) + 1;
		else {
			//printf("update!\n");
			ans[i] = ans[i + 2];
			update(1, L, R, y[i], ans[i]);
		}
		//printf("%d: ans %d\n", i, ans[i]);
	}
	printf("%d\n", query(1, L, R, 0));
}
