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

int n;

struct perm {
	int p[10007];
	int& operator[](int i) { return p[i]; }
	const int& operator[](int i) const { return p[i]; }
	perm() { for(int i = 0; i < n*n; i++) p[i] = i; }
	perm operator*(const perm &o) const {
		perm x;
		for(int i = 0; i < n*n; i++)
			x[i] = p[o[i]];
		return x;
	}
};

perm simple(char d, int x) {
	perm p;
	if(d == 'L') {
		for(int j = 0; j < n - 1; j++)
			p[x * n + j] = x * n + j + 1;
		p[x * n + n - 1] = x * n;
	} else if(d == 'R') {
		for(int j = 1; j < n; j++)
			p[x * n + j] = x * n + j - 1;
		p[x * n] = x * n + n - 1;
	} else if(d == 'U') {
		for(int i = 0; i < n - 1; i++)
			p[i * n + x] = (i + 1) * n + x;
		p[(n - 1) * n + x] = x;
	} else if(d == 'D') {
		for(int i = 1; i < n; i++)
			p[i * n + x] = (i - 1) * n + x;
		p[x] = (n - 1) * n + x;;
	} else assert(false);
	return p;
}

perm fexp(perm p, int e) {
	perm r;
	for(; e; e >>= 1, p = p * p)
		if(e & 1)
			r = r * p;
	return r;
}

char s[11234];

perm rec(int l, int r) {
	if(l >= r) return perm();
	if(s[l] == '(') {
		int ct = 0, i;
		for(i = l + 1; ct > 0 || s[i] != ')'; ct += (s[i] == '(') - (s[i] == ')'), i++);
		int x = atoi(s + i + 1), j ;
		for(j = i + 1; isdigit(s[j]); j++);
		return fexp(rec(l + 1, i - 1), x) * rec(j, r);
	} else {
		int x = atoi(s + l + 1) - 1, j;
		for(j = l + 1; isdigit(s[j]); j++);
		return simple(s[l], x) * rec(j, r);
	}
}

int main() {
	int l, i, j;
	scanf("%d %d %s", &n, &l, s);
	perm p = rec(0, l - 1);
	for(i = 0; i < n; i++, putchar('\n'))
		for(j = 0; j < n; j++)
			printf("%d ", p[i * n + j] + 1);
}
