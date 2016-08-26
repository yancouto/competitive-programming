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
int a[1000009], n;
int mx[10000002][25];
int num[1000009], ns; ull oc[1000009];
void pre() {
	int i, j;
	for(i = 0; i < n; i++)
		mx[i][0] = i;
	for(j = 1; j <= 24; j++)
		for(i = 0; i < n; i++) {
			if(i + (1 << (j - 1)) >= n) { mx[i][j] = mx[i][j-1]; continue; }
			if(a[mx[i][j - 1]] > a[mx[i + (1 << (j - 1))][j - 1]]) mx[i][j] = mx[i][j - 1];
			else mx[i][j] = mx[i + (1 << (j - 1))][j - 1];
		}
}
void calc(int s, int e) {
	if(s > e) return;
	int i, mi = s;
	for(i = 0; (1 << i) <= (e - s + 1); i++);
	i--;
	int c1 = mx[s][i], c2 = mx[e - (1 << i) + 1][i];
	if(a[c1] > a[c2]) mi = c1;
	else mi = c2;
	assert(mi >= s && mi <= e);
	int p = lower_bound(num, num + ns, a[mi]) - num;
	oc[p] += ull(mi - s + 1) * ull(e - mi + 1);
	calc(s, mi - 1);
	calc(mi + 1, e);
}
int main() {
	int m, i, k; char op, pc;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		num[i] = a[i];
	}
	pre();
	num[n] = 0; num[n + 1] = 1000000009;
	sort(num, num + n + 2);
	ns = unique(num, num + n + 2) - num;
	calc(0, n - 1);
	for(i = 1; i < ns; i++)
		oc[i] += oc[i - 1];
	for(i = 0; i < m; i++) {
		scanf(" %c %d %c", &op, &k, &pc);
		bool p = (pc == 'D');
		if(op == '=') {
			int j = lower_bound(num, num + ns, k) - num;
			if(num[j] != k) { putchar('C' + !p); }
			else { putchar('C' + !(p ^ ((oc[j] - oc[j - 1]) & 1))); }
		} else if(op == '<') {
			int j = lower_bound(num, num + ns, k) - num;
			putchar('C' + !(p ^ (oc[j - 1] & 1)));
		} else {
			int j = upper_bound(num, num + ns, k) - num;
			putchar('C' + !(p ^ ((oc[ns - 1] - oc[j - 1]) & 1)));
		}
	}
	putchar('\n');
	return 0;
}
