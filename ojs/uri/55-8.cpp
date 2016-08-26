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
map<int, int> mp;

const int MAX = 50009;
int nxt[MAX << 1];
int ini[MAX], ql[MAX], qr[MAX];
char qt[MAX];
int n, q;

int bit[MAX << 1];
int get(int i) {
	i += 2; int sum = 0;
	while(i) {
		sum += bit[i];
		i -= (i & -i);
	}
	return sum;
}
inline int get(int a, int b) { return get(b) - get(a - 1); }
void add(int i, int x) {
	i += 2;
	while(i < (MAX << 1)) {
		bit[i] += x;
		i += (i & -i);
	}
}

void deb() {
	return;
	for(int i = 0; i < 20; i++)
		printf("%d ", get(i, i));
	putchar('\n');
}

map<int, int> rl, last;
int inv[MAX << 1];
int main() {
	char op;
	int i, j, x;
	while(scanf("%d", &n) != EOF) {
		mp.clear();
		rl.clear();
		last.clear();
		for(i = 0; i < n; i++) {
			scanf("%d", &x);
			mp[x] = mp.size();
			inv[mp[x]] = x;
			last[x] = mp[x];
			nxt[mp[x]] = mp[x] + 1;
			//printf("nxt[%d] = %d + 1\n", mp[x], mp[x]);
			ini[i] = x;
		}
		int nu = 1;
		nxt[mp[x]] = -1;
		scanf("%d", &q);
		for(i = 0; i < q; i++) {
			scanf(" %c %d", &op, &x);
			qt[i] = op;
			ql[i] = x;
			if(op != 'R') {
				scanf("%d", &x);
				qr[i] = x;
			}
			if(op == 'I') {
				int nn = 1000000002 + (nu++);
				rl[nn] = ql[i];
				ql[i] = nn;
				mp[ql[i]] = mp.size();
				last[rl[ql[i]]] = mp[ql[i]];
				inv[mp[ql[i]]] = ql[i];
				int ii = mp[ql[i]], jj = last[qr[i]];
				nxt[ii] = nxt[jj];
				nxt[jj] = ii;
			}
		}
		i = 0; int l = 1;
		while(l != -1) {
			//printf("l %d next %d\n", l, nxt[l]);
			mp[inv[l]] = i++;
			l = nxt[l];
		}
		memset(bit, 0, sizeof bit);
		last.clear();
		for(i = 0; i < n; i++) {
			add(mp[ini[i]], 1);
			last[ini[i]] = mp[ini[i]];
		}
		deb();
		for(i = 0; i < q; i++) {
			if(qt[i] == 'I') { add(mp[ql[i]], 1); last[rl[ql[i]]] = mp[ql[i]]; }
			else if(qt[i] == 'R') add(last[ql[i]], -1);
			else {
				int a = last[ql[i]], b = last[qr[i]];
				if(a > b) swap(a, b);
				printf("%d\n", get(a, b) - 1 - (a != b));
			}
			deb();
		}
	}
	return 0;
}
