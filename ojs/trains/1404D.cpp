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
const int N = 263009;
const int p2 = 262144;

char s[N]; int z[N];

void manacher() {
	int L, R = -1, i;
	for(i = 0; s[i]; i++) {
		if(R < i) {
			for(L = R = i; s[R] && 2*i >= R && s[R] == s[2*i-R]; R++);
			z[i] = (--R) - i;
		} else if(z[2*L-i] < R - i) { z[i] = z[2*L-i]; }
		else {
			for(L = i, R++; s[R] && 2*i >= R && s[R] == s[2*i-R]; R++);
			z[i] = (--R) - i;
		}
	}
}
vector<int> in[N];

int bit[N];

int add(int i, int x) {
	for(i += 2; i < N; i += (i & -i))
		bit[i] += x;
}
//int get(int i) {
//	int sum = 0;
//	for(; i; i -= (i & -i))
//		sum += bit[i];
//	return sum;
//}

int query(int x) {
	//printf("query for %d\n", x);
	//printf("%d", get(0));
	//for(int i = 1; i < 20; i++)
	//	printf(" %d", get(i) - get(i - 1));
	//putchar('\n');
	int l = 0, r = p2;
	while(l < r) {
		int m = (l + r) / 2;
		if(bit[m] >= x) r = m;
		else l = m + 1, x -= bit[m];
	}
	//printf("ans %d\n", l);
	return l - 2;
}

pii qs[N]; int p[N], ans[N];
int main() {
	freopen("palindrome.in", "r", stdin);
	freopen("palindrome.out", "w", stdout);
	int i, n;
	scanf("%s", s);
	int sz = strlen(s);
	for(i = sz - 1; i >= 0; i--)
		s[2*i] = s[i], s[2*i+1] = '$';
	s[2*sz - 1] = 0;
	manacher();
	for(i = 0; s[i]; i++) in[i - z[i]].pb(i);
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d %d", &qs[i].fst, &qs[i].snd), qs[i].fst = 2 * (qs[i].fst - 1), p[i] = i;
	sort(p, p + n, [](int i, int j) { return qs[i] < qs[j]; });
	int r = -1;
	for(i = 0; s[i]; i++) add(i, 1);
	add(210000, 210000);
	for(i = 0; i < n; i++) {
		while(r < qs[p[i]].fst) {
			for(int x : in[++r]) add(x, -1);
			//if(r) add(r - 1, 1);
		}
		ans[p[i]] = query(qs[p[i]].snd) - r + 1;
		if(ans[p[i]] + (r / 2) - 1 >= sz) ans[p[i]] = -1;
	}
	for(i = 0; i < n; i++) printf("%d\n", ans[i]);
}
