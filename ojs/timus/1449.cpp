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
const int N = 302;
int n, c[N][N], MA[N], MB[N], PB[N], d[N], mn[N];
bool S[N], T[N];
int y[N], z[N], st[N], sn;

void reset_all() {
	// need to be changed for costs < 0
	int i;
	for(i = 0; i < n; i++)
		y[i] = -2000000;
	memset(z, 0, sizeof z);
	for(i = 0; i < n; i++)
		MA[i] = MB[i] = -1;
}

bool increase(int b) {
	int a = PB[b];
	while(true) {
		int n_b = MA[a];
		MB[b] = a;
		MA[a] = b;
		if(n_b == -1) break;
		b = n_b;
		a = PB[b];
	}
	return true;
}

// O(n)
bool visit(int a) {
	S[a] = true;
	for(int b = 0; b < n; b++) {
		if(T[b]) continue;
		if(c[a][b] - y[a] - z[b] < d[b]) {
			d[b] = c[a][b] - y[a] - z[b];
			mn[b] = a;
		}
		if(c[a][b] == y[a] + z[b]) {
			T[b] = true;
			PB[b] = a;
			st[sn++] = b;
			if(MB[b] == -1)
				return increase(b);
		}
	}
	return false;
}

// O(n)
bool update_dual() {
	int mb = -1, b;
	for(b = 0; b < n; b++)
		if(!T[b] && (mb == -1 || d[b] < d[mb]))
			mb = b;
	int e = d[mb];
	for(b = 0; b < n; b++)
		if(T[b]) z[b] -= e;
		else d[b] -= e;
	for(int a = 0; a < n; a++)
		if(S[a]) y[a] += e;
	PB[mb] = mn[mb];
	if(MB[mb] == -1) return increase(mb);
	st[sn++] = mb;
	T[mb] = true;
	return false;
}

// O(n^2)
void find_path() {
	int i, a;
	for(a = 0; MA[a] != -1; a++);
	memset(S, 0, sizeof S);
	memset(T, 0, sizeof T);
	memset(d, 0x7f, sizeof d); // ~inf
	sn = 0;
	if(visit(a)) return;
	while(true) {
		if(sn) { if(visit(MB[st[--sn]])) break; }
		else if(update_dual()) break;
	}
}

int min_match() {
	reset_all();
	for(int i = 0; i < n; i++)
		find_path();
	int all = 0;
	for(int a = 0; a < n; a++)
		all += c[a][MA[a]];
	return all;
}

int main() {
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++) {
			scanf("%d", &c[i][j]);
			c[i][j] = -c[i][j];
		}
	min_match();
	for(i = 0; i < n; i++)
		printf("%d ", -y[i]);
	putchar('\n');
	for(i = 0; i < n; i++)
		printf("%d ", -z[i]);
	putchar('\n');
}
