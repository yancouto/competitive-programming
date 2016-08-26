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
const int N = 11234;

char s[N];
struct edge {
	int v;
	int l, r;
	int len() const { return r - l + 1; }
	char operator[](int i) const { return s[l + i - 1]; }
};
map<char, edge> tr[N];
int en = 1, n;

void add(int st) {
	int cn = 0, cd = 0; char cc;
	for(; s[st]; st++) {
		if(cd && tr[cn][cc][cd + 1] != s[st]) {
			tr[en][tr[cn][cc][cd + 1]] = {tr[cn][cc].v, tr[cn][cc].l + cd, tr[cn][cc].r};
			tr[cn][cc] = {en, tr[cn][cc].l, tr[cn][cc].l + cd - 1};
			cn = en++; cd = 0;
		}
		if(!cd && !tr[cn].count(s[st])) {
			tr[cn][s[st]] = {en++, st, n};
			break;
		}
		if(cd) cd++;
		else cd = 1, cc = s[st];
		if(cd == tr[cn][cc].len()) cd = 0, cn = tr[cn][cc].v;
	}
}
int tot = 0;
void dfs(int u) {
	for(auto it : tr[u]) {
		edge e = it.snd;
		tot += e.len();
		dfs(e.v);
	}
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++)
		add(i);
	dfs(0);
	printf("%d\n", tot);
}
