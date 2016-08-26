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
const int N = 512;

int f[N], N1[N], N0[N], F[N][2];
char P[N], T[N];
int pn, tn;

inline void kmp() {
	for(int i = 2; i <= pn; i++) {
		f[i] = f[i - 1];
		while(f[i] && P[f[i] + 1] != P[i])
			f[i] = f[f[i]];
		if(P[f[i] + 1] == P[i]) f[i]++;
	}
	for(int i = 0; i <= pn; i++)
		for(int j = 0; j <= 1; j++) {
			F[i][j] = f[i];
			while(F[i][j] && P[F[i][j] + 1] != j + '0')
				F[i][j] = f[F[i][j]];
			if(P[F[i][j] + 1] == j + '0') F[i][j]++;
		}
}

inline bool addC(int &v, char c) {
	if(P[v + 1] != c) v = F[v][c - '0'];
	else v++;
	bool mt = (v == pn);
	if(mt) v = f[v];
	return mt;
}

pii memo[2][505][505][2];
inline pii& solve(int i, int v, int nx0, int nx1) {
	return memo[i & 1][v][max(nx0, nx1)][nx0 > nx1];
}

int main() {
	int i, v, nx0, nx1;
	scanf("%s", T + 1); tn = strlen(T + 1);
	scanf("%s", P + 1); pn = strlen(P + 1);
	kmp();

	int n1 = tn + 1, n0 = tn + 1;
	for(i = tn + 1; i >= 0; i--) {
		N0[i] = n0;
		N1[i] = n1;
		if(T[i] == '1') n1 = i;
		else if(T[i] == '0') n0 = i;
	}

	for(i = tn; i >= 1; i--)
		for(v = 0; v < pn; v++) {
			for(nx0 = N0[i]; ; nx0 = N0[nx0]) {
				nx1 = i;
				pii &r = solve(i, v, nx0, nx1);
				int p = v;
				bool mt = addC(p, '1');
				r = solve(i + 1, p, nx0, (i + 1) == nx0? N1[i + 1] : i + 1);
				r.fst -= mt;
				if(nx0 < tn + 1) {
					p = v;
					mt = addC(p, '0');
					pii o = solve(i + 1, p, N0[nx0], i + 1);
					o.fst -= mt;
					o.snd += nx0 - i;
					r = min(r, o);
				}
				if(nx0 == tn + 1) break;
			}
			for(nx1 = N1[i]; ; nx1 = N1[nx1]) {
				nx0 = i;
				pii &r = solve(i, v, nx0, nx1);
				int p = v;
				bool mt = addC(p, '0');
				r = solve(i + 1, p, (i + 1) == nx1? N0[i + 1] : i + 1, nx1);
				r.fst -= mt;
				if(nx1 < tn + 1) {
					p = v;
					mt = addC(p, '1');
					pii o = solve(i + 1, p, i + 1, N1[nx1]);
					o.fst -= mt;
					o.snd += nx1 - i;
					r = min(r, o);
				}
				if(nx1 == tn + 1) break;
			}
		}
	pii ans = solve(1, 0, N0[0], N1[0]);
	printf("%d %d\n", -ans.fst, ans.snd);
}
