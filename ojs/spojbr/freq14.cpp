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

int get(int *bit, int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[i];
	return sum;
}

void add(int *bit, int i, int x) {
	for(i += 2; i < N; i += (i & -i))
		bit[i] += x;
}

int n;
int bit[2][60][N];
struct obj {
	int val[N], tim[N], sn;
	int val2[N], tim2[N];
	obj() {
		memset(val2, 0, sizeof val2);
		memset(tim2, 0, sizeof tim2);
		memset(val, 0, sizeof val);
		memset(tim, 0, sizeof tim);
		sn = 1;
	}
	void setline(int, int);
	void setcol(int, int, int=0);
	void println(int, int=0);
};

void obj::setline(int x, int c) {
	val[x] = c;
	tim[x] = sn++;
}

void obj::setcol(int x, int c, int C) {
	if(tim2[x]) add(bit[C][val2[x]], tim2[x], -1);
	tim2[x] = sn; val2[x] = c;
	add(bit[C][c], sn++, 1);
}

void obj::println(int x, int C) {
	int ct[60];
	memset(ct, 0, sizeof ct);
	ct[val[x]] = n;
	for(int i = 0; i <= 50; i++) {
		int p = get(bit[C][i], sn + 1) - get(bit[C][i], tim[x]);
		ct[val[x]] -= p;
		ct[i] += p;
	}
	int mx = 0, mc;
	for(int i = 0; i <= 50; i++)
		if(ct[i] >= mx)
			mx = ct[i],
			mc = i;
	printf("%d\n", mc);
}

int main() {
	int i, q, op, x, r;
	scanf("%d %d", &n, &q);
	obj l, c;
	for(i = 0; i < q; i++) {
		scanf("%d %d", &op, &x);
		if(op <= 2) scanf("%d", &r);
		switch(op) {
			case 1:
				l.setline(x, r);
				c.setcol(x, r, 1);
			break;
			case 2:
				l.setcol(x, r);
				c.setline(x, r);
			break;
			case 3:
				l.println(x);
			break;
			case 4:
				c.println(x, 1);
		}
	}
}
