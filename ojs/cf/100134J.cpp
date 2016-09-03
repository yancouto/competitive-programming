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
typedef vector<int> per;

void add(per &p, const per &x) {
	int n = p.size();
	for(int k : x) p.pb(k + n);
}

per brut(int a, int b, int c, int fixlst = 1) {
	int n = a + b + c + 1, i;
	per p(n);
	for(i = 0; i < n; i++) p[i] = i;
	do {
		per k(n+1, 0);
		for(i = 0; i < n - 1; i ++)
			k[abs(p[i + 1] - p[i])]++;
		if(k[1] == a && k[2] == b && k[3] == c) {
			per q(n-1);
			for(i = 1; i < n; i++) q[i - 1] = p[i] - 1;
			return q;
		}
	} while(next_permutation(p.begin() + 1, p.end() - fixlst));
	assert(false);
}

const per single(1, 0),
          z42 = brut(0, 4, 2),
          z23 = brut(0, 2, 3),
          o20 = brut(1, 2, 0),
          o41 = brut(1, 4, 1),
          t02 = brut(2, 0, 2);

void go3(int &a, int &b, int &c, per &p) {
	int k = (c + 1) / 3, i;
	per x;
	for(i = 0; i < k; i++) x.pb(i * 3 + 2);
	x.pb((k - 1) * 3 + 1);
	for(i = (k - 1) * 3 + 1 - 3; i >= 0; i -= 3)
		x.pb(i);
	x.pb(0);
	for(i = 3; i <= 3 * k; i += 3) x.pb(i);
	add(p, x);
	a -= 2; c -= 3 * k - 1;
}

int main() {
	freopen("jumping.in", "r", stdin);
	freopen("jumping.out", "w", stdout);
	int i, a, b, c, t;
	scanf("%d", &t);
	srand(time(NULL));
	while(t--) {
		scanf("%d %d %d", &a, &b, &c);
		//const int t = 5000 - 3;
		//a = (rand() % t) + 3, b = (rand() % t) + 3, c = (rand() % t) + 3;
		//fprintf(stderr, "(%d, %d, %d)\n", a, b, c);
		int on = a + b + c + 1, oa = a, ob = b, oc = c;
		per p(1, 0);
		for(i = 0; i < a - 3; i++) add(p, single);
		a = 3;
		while(b >= 3 + 4 && c >= 3 + 2) {
			b -= 4; c -= 2;
			add(p, z42);
		}
		while(b >= 3 + 2 && c >= 3 + 3) {
			b -= 2; c -= 3;
			add(p, z23);
		}
		if(b <= 4 && c <= 4) add(p, brut(a, b, c, 0));
		else if(b >= c) {
			add(p, brut(2, 2, c));
			b -= 2;
			per x;
			for(i = 1; i <= b; i += 2) x.pb(i);
			int nx = b - (b % 2);
			for(i = nx; i >= 0; i -= 2) x.pb(i);
			add(p, x);
		} else {
			go3(a, b, c, p);
			add(p, brut(a, b, c, 0));
		}
		assert(p.size() == on);
		vector<int> k(on + 10, 0);
		for(i = 0; i < on; i++)
			assert(p[i] >= 0 && p[i] < on && !k[p[i]]), k[p[i]] = 1;
		for(i = 0; i < on; i++) k[i] = 0;
		for(i = 0; i < on - 1; i++)
			k[abs(p[i + 1] - p[i])]++;
		assert(k[1] == oa && k[2] == ob && k[3] == oc && p[0] == 0);
		printf("0");
		for(i = 1; i < on; i++) printf(" %d", p[i]);
		printf("\n");
	}
}
