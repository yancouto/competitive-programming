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

int en = 1;
map<char, int> tr[100000];
int F[100000], mrk[100000], nx[100000];
void aho() {
	queue<int> q;
	for(auto e : tr[0])
		q.push(e.snd), F[e.snd] = 0;
	while(!q.empty()) {
		int v = q.front(); q.pop();
		for(auto e : tr[v]) {
			int &f = F[e.snd];
			f = F[v];
			while(f && !tr[f].count(e.fst)) f = F[f];
			if(tr[f].count(e.fst)) f = tr[f][e.fst];
			if(mrk[f]) nx[e.snd] = f;
			else nx[e.snd] = nx[f];
			q.push(e.snd);
		}
	}
}

int root[100009], no[100009];

const int N = 21234567;
int c1[N], c2[N];
int L[N], R[N];

void add(int &i, int l, int r, int p) {
	if(i == 0) i = en++;
	c2[i]++;
	if(l == r) return (void)(c1[i] = 1);
	int m = (l + r) / 2;
	if(p <= m) add(L[i], l, m, p);
	else add(R[i], m + 1, r, p);
	c1[i] = c1[L[i]] + c1[R[i]];
}

int get(int i, int l, int r, int ql, int qr, int c[]) {
	if(!i || l > qr || r < ql) return 0;
	if(l >= ql && r <= qr) return c[i];
	int m = (l + r) / 2;
	return get(L[i], l, m, ql, qr, c) + get(R[i], m + 1, r, ql, qr, c);
}

inline void add_oc(int i, int p) {
	add(root[i], 0, 100000, p);
}


char s[112345];
int main() {
	int i, j, n, m, q, l, r, op, p; char c;
	scanf("%d %d %d", &n, &m, &q);
	for(i = 0; i < m; i++) {
		scanf("%s", s);
		reverse(s, s + strlen(s));
		int v = 0;
		for(j = 0; s[j]; j++) {
			if(!tr[v].count(s[j])) tr[v][s[j]] = en++;
			v = tr[v][s[j]];
		}
		mrk[v] = 1 + i;
	}
	aho(); en = 1;
	for(j = 0; j < q; j++) {
		scanf("%d", &op);
		if(op == 0) {
			scanf("%d %c", &i, &c); i--;
			while(no[i] && !tr[no[i]].count(c)) no[i] = F[no[i]];
			if(tr[no[i]].count(c)) no[i] = tr[no[i]][c];
			if(mrk[no[i]]) add_oc(mrk[no[i]] - 1, i);
			for(int g = nx[no[i]]; g; g = nx[g])
				add_oc(mrk[g] - 1, i);
		} else {
			scanf("%d %d %d", &l, &r, &p); l--; r--; p--;
			printf("%d\n", get(root[p], 0, 100000, l, r, op == 1? c1 : c2));
		}
	}
}
