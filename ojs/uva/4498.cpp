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
const int N = 1000009;
int S[N], sz[N], r[N], ans[N], a[N], mn[N];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	S[b] = a;
	sz[a] += sz[b];
	r[a] = max(r[a], r[b]);
}

inline int getnum() {
	int a = 0; char c;
	while(isspace(c = getchar_unlocked()));
	a = c - '0';
	while(isdigit(c = getchar_unlocked())) a = (a << 3) + (a << 1) + (c - '0');
	return a;
}

char str[100];
int main() {
	int i, n, m, x, ct;
	for_tests(t, tt) {
		n = getnum(); m = getnum();
		for(i = 0; i <= m + 1; i++) S[i] = i, sz[i] = 1, r[i] = i;
		for(i = 0; i < m; i++) {
			a[i] = getnum();
			if(a[i]) join(i, i + 1);
			else ans[i] = 0;
			mn[a[i]] = 0;
		}
		for(i = 0; i < m; i++) {
			if(!a[i]) continue;
			int j = find(mn[a[i]]);
			if(r[j] > i) break;
			ans[r[j]] = a[i];
			join(r[j], r[j] + 1);
			mn[a[i]] = i;
		}
		if(i < m) { puts("NO"); continue; }
		puts("YES");
		for(i = 0; i < m; i++)
			if(!a[i]) {
				x = ct = 0;
				if(!ans[i]) ct++;
				while(ans[i]) ct++, x = (x << 3) + (x << 1) + (ans[i] % 10), ans[i] /= 10;
				while(ct--) putchar_unlocked('0' + (x % 10)), x /= 10;
				putchar(' ');
			}
		putchar('\n');
	}
}
