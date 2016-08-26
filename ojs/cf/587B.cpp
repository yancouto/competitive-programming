// WA
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int MAX = 1001109;
ll bit[2][MAX];
ll get(int x, int i) {
	ll sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum = mod(sum + bit[x][i]);
	return sum;
}
ll get(int x, int i, int j) { return mod(get(x, j) - get(x, i - 1) + modn); }
void add(int x, int i, ll v) {
	for(i += 2; i < MAX; i += (i & -i))
		bit[x][i] = mod(bit[x][i] + v);
}
int a[MAX], b[MAX];
int n, k; ll l;
ll go1() {
	int i, j;
	ll x = (l + n - 1) / n;
	x--; // sem considerar o ultimo;
	int k = min<ll>(::k, x);
	k--;
	//printf("using k=%d\n", k);
	for(i = 0; i < n; i++)
		add(k & 1, a[i], 1);
	ll tot = 0;
	for(i = k - 1; i >= 0; i--) {
		memset(bit[i & 1], 0, (n + 14) * sizeof(int));
		//printf("[%d]:", i + 1);
		//for(j = 0; j < n; j++)
		//	printf(" %d", (int)get((i+1)&1, j, j));
		//putchar('\n');
		tot = mod(tot + mod(x - (k - i) + 1) * get((i+1)&1, 0, n-1));
		for(j = 0; j < n; j++) {
			//printf("%d|add(%d, %d, %d)\n", i, i & 1, a[j], (int)get(!(i & 1), a[j], n));
			add(i & 1, a[j], get(!(i & 1), a[j], n));
		}
	}
	//printf("[%d]:", 0);
	//for(j = 0; j < n; j++)
	//	printf(" %d", (int)get(0, j, j));
	//putchar('\n');
	tot = mod(tot + mod(x - (k + 1) + 1) * get(0, 0, n - 1));
	//printf("%d\n", (int) tot);
	//puts("-----------------------");
	return tot;
}

ll go2() {
	int i, j;
	ll x = (l + n - 1) / n;
	int k = min<ll>(::k, x);
	k--;
	memset(bit, 0, sizeof bit);
	int en = (l % n);
	if(en == 0) en = n;
	for(i = en - 1; i >= 0; i--)
		add(k & 1, a[i], 1);
	ll tot = 0;
	for(i = k - 1; i >= 0; i--) {
		memset(bit[i & 1], 0, (n + 14) * sizeof(int));
		//printf("[%d]:", i + 1);
		//for(j = 0; j < n; j++)
		//	printf(" %d", (int)get((i+1)&1, j, j));
		//putchar('\n');
		tot = mod(tot + get((i+1)&1, 0, n-1));
		for(j = 0; j < n; j++) {
			//printf("%d|add(%d, %d, %d)\n", i, i & 1, a[j], (int)get(!(i & 1), a[j], n));
			add(i & 1, a[j], get(!(i & 1), a[j], n));
		}
	}
	//printf("[%d]:", 0);
	//for(j = 0; j < n; j++)
	//	printf(" %d", (int)get(0, j, j));
	//putchar('\n');
	tot = mod(tot + get(0, 0, n - 1));
	//printf("%d\n", (int) tot);
	return tot;
}


int main() {
	int i, j;
	scanf("%d %lld %d", &n, &l, &k);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	if(l < n) n = l;
	sort(b, b + n);
	for(i = 0; i < n; i++)
		a[i] = lower_bound(b, b + n, a[i]) - b;
	//for(i = 0; i < n; i++)
	//	printf("%d ", a[i]);
	//putchar('\n');
	ll tot = mod(go1() + go2());
	printf("%d\n", (int)tot);
}
