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
char trunfo, cur;
int val[256];
struct card {
	char c, n;
	int valc() const { return val[c]; }
	void read() { scanf(" %c%c", &c, &n); }
	bool samen(const card &ca) { return n == ca.n; }
};

void pre() {
	int i = 8;
	for(char c : {'T', 'J', 'Q', 'K', 'A'})
		val[c] = i++;
	for(i = 2; i <= 9; i++)
		val[i + '0'] = i - 2;
}
int maxx(int i, int j) { return i > j? i : j; }
int minn(int i, int j) { return i > j? j : i; }

card p[6][6];
card turn[7][6];
int play(bool newg, int bg, int pl, int r, int nswins) {
	int i;
	int (*fun)(int, int) = ((pl & 1)? minn : maxx);
	const int bas = ((pl & 1)? INT_MAX : INT_MIN);
	if(newg) {
		int v = bas;
		for(i = 0; i < r; i++) {
			swap(p[pl][i], p[pl][r-1]);
			turn[r][pl] = p[pl][r-1];
			v = fun(v, play(false, bg, (pl + 1) % 4, r, nswins));
			swap(p[pl][i], p[pl][r-1]);
		}
		return v;
	}
	if(bg == pl) {
		int wn = bg; char cur = turn[r][bg].n;
		bool has = false;
		for(i = 0; i < 4; i++)
			has |= (turn[r][i].n == trunfo);
		if(has) cur = trunfo;
		for(wn = 0; turn[r][wn].n != cur; wn++);
		for(i = 0; i < 4; i++)
			if(turn[r][i].n == cur && turn[r][i].valc() > turn[r][wn].valc())
				wn = i;
		nswins += !(wn & 1);
		if(r > 1) return play(true, wn, wn, r - 1, nswins);
		return nswins;
	}
	bool has = false;
	for(i = 0; i < r; i++)
		has |= turn[r][bg].samen(p[pl][i]);
	int v = bas;
	for(i = 0; i < r; i++)
		if(!has || turn[r][bg].samen(p[pl][i])) {
			swap(p[pl][i], p[pl][r-1]);
			turn[r][pl] = p[pl][r-1];
			v = fun(v, play(false, bg, (pl + 1) % 4, r, nswins));
			swap(p[pl][i], p[pl][r-1]);
		}
	return v;
}

int main() {
	int R, i, j;
	pre();
	for_tests(t, tt) {
		scanf(" %c%*c %d", &trunfo, &R);
		for(i = 0; i < 4; i++)
			for(j = 0; j < R; j++)
				p[i][j].read();
		printf("%d\n", play(true, 0, 0, R, 0));
	}
}
