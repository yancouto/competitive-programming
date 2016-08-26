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
int f[256], seen[1003];
char s[1100];
ll pot[6009];
void pre() {
	int i;
	for(i = 0; i < 26; i++) f[i + 'A'] = i;
	for(; i < 52; i++) f[i + 'a' - 26] = i;
	for(; i < 64; i++) f["0123456789+/"[i-52]] = i;
	pot[0] = 1ll;
	for(i = 1; i < 6009; i++)
		pot[i] = mod(5ll * pot[i-1]);
}

int S[1003], sz[1003];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	a = find(a); b = find(b);
	if(a == b) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

bitset<12003> b;
ll h[12003];

bool eq(int a1, int b1, int a2, int b2) {
	bool e = mod(h[b1 + 1] - mod(h[a1] * pot[b1 - a1 + 1]) + modn) == mod(h[b2 + 1] - mod(h[a2] * pot[b2 - a2 + 1]) + modn);
	return e;
}

bool lex_less(int i, int j, int x) {
	int l = 1, r = x;
	if(b[i] != b[j]) return b[i] < b[j];
	while(l < r) {
		int m = (l + r + 1) / 2;
		if(eq(i, i + m - 1, j, j + m - 1)) l = m;
		else r = m - 1;
	}
	return b[i + l] < b[j + l];
}

pii v[1009];
int main() {
	int t = 1, i, j, n, k;
	pre();
	while(scanf("%d", &n) != EOF && n) {
		for(i = 0; i < n; i++)
			S[i] = i, sz[i] = 1;
		int vn = 0;
		for(k = 0; k < n; k++) {
			scanf("%s", s); int x = strlen(s);
			reverse(s, s + x);
			for(i = 0; i < x; i++)
				for(j = 0; j < 6; j++)
					b.set(i * 6 + j, !!(f[s[i]] & (1 << j)));
			for(i = x; i < 2 * x; i++)
				for(j = 0; j < 6; j++)
					b.set(i * 6 + j, !!(f[s[i-x]] & (1 << j)));
			for(i = 0; i < 12 * x; i++)
				h[i + 1] = mod(h[i] * 5ll + (1ll + b[i]));
			int mi = 0;
			for(i = 1; i < 6 * x; i++)
				if(lex_less(i, mi, 6 * x))
					mi = i;
			v[vn++] = pii(mod(h[mi + 6*x] - mod(h[mi] * pot[6*x]) + modn), k);
		}
		sort(v, v + vn);
		for(i = 1; i < vn; i++)
			if(v[i].fst == v[i-1].fst)
				join(v[i].snd, v[i-1].snd);
		printf("Case %d:\n", t++);
		for(k = 1; k <= n; k++)
			for(i = 0; i < n; i++)
				if(seen[find(i)] != t && sz[find(i)] == k) {
					seen[find(i)] = t; int x = 0;
					for(j = 0; j < n; j++)
						if(find(i) == find(j))
							printf("%d%s", j + 1, ++x == k? "" : " ");
					putchar('\n');
				}
	}
}
