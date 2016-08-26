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
const int MAX = 40009;
struct no {
	pii p; int i;
	no() {}
	no(int a, int b, int c) : p(a, b), i(c) {}
	bool operator < (no o) const { return p < o.p; }
	bool operator == (no o) const { return p == o.p; }
} l[MAX];
int p[MAX][19], r[MAX], n;
char s[MAX];
int lcp(int i, int j) {
	int t = 0;
	for(int k = 18; k >= 0; k--)
		if(p[i+t][k] == p[j+t][k] && i + t + (1 << k) <= n && j + t + (1 << k) <= n)
			t += 1 << k;
	return t;
}

int main() {
	int i, j, m;
	while(scanf("%d", &m) != EOF && m) {
		scanf("%s", s); n = strlen(s);
		if(m == 1) { printf("%d 0\n", n); continue; }
		for(i = 0; i < n; i++)
			p[i][0] = s[i];
		for(j = 1; j < 19; j++) {
			for(i = 0; i < n; i++)
				l[i] = no(p[i][j-1], i + (1 << (j - 1)) < n? p[i + (1 << (j - 1))][j - 1]:  -1, i);
			sort(l, l + n);
			for(i = 0; i < n; i++)
				p[l[i].i][j] = i && l[i] == l[i - 1]? p[l[i - 1].i][j] : i;
		}
		for(i = 0; i < n; i++)
			r[p[i][18]] = i;
		multiset<int> s;
		set<int> s2; s2.insert(r[0]);
		for(i = 0; i < m - 1; i++)
			s.insert(lcp(r[i], r[i + 1])), s2.insert(r[i+1]);
		int md = *s.begin(), mi = *s2.rbegin();
		for(i = m - 1; i < n - 1; i++) {
			s.erase(s.find(lcp(r[i-m+1], r[i-m+2])));
			s2.erase(r[i - m + 1]);
			s.insert(lcp(r[i], r[i+1]));
			s2.insert(r[i + 1]);
			if(*s.begin() == md)
				mi = max(mi, *s2.rbegin());
			if(*s.begin() > md)
				md = *s.begin(), mi = *s2.rbegin();
		}
		if(md == 0) puts("none");
		else printf("%d %d\n", md, mi);
	}
}
