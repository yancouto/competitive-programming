#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

#define pb push_back
#define fst first
#define snd second

const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 212345;

const ll B = 239;
ll pB[N];
struct hsh {
	ll x;
	hsh() : x(0) {}
	hsh(ll a) : x(mod(a)) {}
	hsh add(ll c) const { return hsh(x * B + c); }
	hsh operator * (ll m) const { return hsh(x * m); }
	hsh& operator += (hsh o) { x = mod(x + o.x); return *this; }
	hsh operator - (hsh o) const { return hsh(x - o.x + modn); }
	hsh shift(int k) const { return hsh(x * pB[k]); }
	bool operator == (hsh o) const { return x == o.x; }
	void prn() const { printf(": %lld\n", x); }
};

char s[N], t[N];

hsh tc[N], h[N];
int p[128];

int main() {
#ifdef ONLINE_JUDGE
	freopen("substring.in", "r", stdin);
	freopen("substring.out", "w", stdout);
#endif
	pB[0] = 1;
	for(int i = 1; i < N; i++)
		pB[i] = mod(pB[i - 1] * B);
	scanf("%s %s", s + 1, t + 1);
	int tn = strlen(t + 1);
	int i, c;
	for(c = 33; c <= 126; c++) {
		for(i = 1; i <= tn; i++)
			tc[c] = tc[c].add(c == t[i]);
	}
	int sn = strlen(s + 1);
	vector<pii> fst;
	for(i = 1; i <= tn; i++) {
		if(p[t[i]] == 0) {
			p[t[i]] = 1;
			fst.pb(pii(i, t[i]));
		}
	}
	for(i = 1; i <= sn; i++) {
		h[i] = h[i - 1].add(s[i]);
	}
	vector<int> ocs;
	for(i = 1; i <= sn - tn + 1; i++) {
		memset(p, 0, sizeof p);
		hsh tot;
		bool ok = true;
		for(pii x : fst) {
			if(p[s[i + x.fst - 1]]) { ok = false; break; }
			p[s[i + x.fst - 1]] = 1;
			tot += (tc[x.snd] * s[i + x.fst - 1]);
		}
		if(ok && tot == (h[i + tn - 1] - (h[i - 1].shift(tn))))
			ocs.pb(i);
	}
	printf("%d\n", int(ocs.size()));
	for(int x : ocs)
		printf("%d ", x);
	putchar('\n');
}
