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

struct tr {
	int a, b, c;
	bool operator < (tr o) const {
		if(a != o.a) return a < o.a;
		return pii(b, c) < pii(o.b, o.c);
	}
};

map<pii, int> ct[3];
void val(set<tr> &s, int A, int B, int C, int k) {
	assert(s.size() == k * A * B);
	for(int i = 0; i < 3; i++) ct[i].clear();
	for(tr t : s)
		ct[0][pii(t.a, t.b)]++,
		ct[1][pii(t.a, t.c)]++,
		ct[2][pii(t.b, t.c)]++;
	for(int i = 0; i < 3; i++)
		for(auto a : ct[i])
			assert(a.snd <= k);
}

#include "testlib.h"


int main(int argc, char **argv) {
	registerGen(argc, argv, 1);
	int A, B, C, k;
	for_tests(t, tt) {
		scanf("%d %d %d %d", &A, &B, &C, &k);
		k = min(k, C);
		printf("Case #%d: %d\n", tt, k * A * B);
		set<tr> ans;
		for(int a = 0; a < A; a++) {
			int c = C - a - 1;
			for(int b = 0; b < B; b++) {
				for(int i = 0; i < k; i++) {
					c = (c + 1) % C;
					ans.insert({a+1, b+1, c+1});
					printf("%d %d %d\n", a + 1, b + 1, c + 1);
				}
			}
		}
		val(ans, A, B, C, k);
	}
}
