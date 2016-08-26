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

struct no {
	int a, b, i;
	bool operator < (no o) const { return pii(a, b) < pii(o.a, o.b); }
	bool operator == (no o) const { return pii(a, b) == pii(o.a, o.b); }
};

int p[20002][17];
no l[20003];
char s[20009];

int main() {
	int i, j, n;
	for_tests(t, tt) {
		scanf("%s", s); n = strlen(s);
		memmove(s + n, s, n + 1);
		n = strlen(s);
		for(i = 0; i < n; i++)
			p[i][0] = s[i] - 'a';
		for(i = 1; i < 17; i++) {
			for(j = 0; j < n; j++)
				l[j] = no{p[j][i - 1], j + (1 << (i - 1)) < n? p[j + (1 << (i - 1))][i - 1] : INT_MAX, j};
			sort(l, l + n);
			for(j = 0; j < n; j++)
				p[l[j].i][i] = j && l[j] == l[j - 1]? p[l[j-1].i][i] : j;
		}
		int mn = INT_MAX, mi;
		for(i = 0; i < n / 2; i++)
			if(p[i][16] < mn)
				mi = i, mn = p[i][16];
		printf("%d\n", mi + 1);
	}
}
