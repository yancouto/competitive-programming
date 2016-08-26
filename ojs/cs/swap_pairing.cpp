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
const int N = 112345;
int op[N], b[N], bit[N], a[N];

int get(int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[i];
	return sum;
}

void add(int i, int x) {
	for(i += 2; i < N; i += (i & -i))
		bit[i] += x;
}


int main() {
	int i, n;
	map<int, int> o;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		b[i] = a[i];
		op[i] = -1;
	}
	sort(b, b + n);
	int bn = unique(b, b + n) - b;
	for(i = 0; i < n; i++) {
		add(i, 1);
		a[i] = lower_bound(b, b + bn, a[i]) - b;
		if(op[a[i]] == -1) { op[a[i]] = i; continue; }
		o[op[a[i]]] = i;
		o[i] = -1;
		printf("o[%d] = %d\no[%d] = %d\n", op[a[i]], i, i, -1);
	}
	for(i = 0; i < n; i++)
		printf("bit[%d] = %d\n", i, get(i));
	ll tot = 0;
	for(i = 0; i < n; i++) {
		if(o[i] == -1) continue;
		int g = get(o[i]) - get(i - 1);
		printf("%d->%d get %d - %d\n", i, o[i], get(o[i]), get(i - 1));
		tot += g - 2;
		add(i, -1);
		add(o[i], -1);
	}
	printf("%lld\n", tot);
}
