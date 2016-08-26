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

int a[30];
void ver(int n) {
	assert(*max_element(a, a + n) * 2 <= accumulate(a, a + n, 0));
}

int main() {
	int i, n, x, sum;
	for_tests(t, tt) {
		scanf("%d", &n);
		set<pii> s; sum = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &x);
			s.insert(pii(x, i));
			sum += x;
			a[i] = x;
		}
		printf("Case #%d:", tt);
		while(sum > 3) {
			putchar(' ');
			pii p = *s.rbegin();
			s.erase(p); s.insert(pii(p.fst - 1, p.snd));
			putchar('A' + p.snd); a[p.snd]--;
			p = *s.rbegin();
			s.erase(p); s.insert(pii(p.fst - 1, p.snd));
			putchar('A' + p.snd); a[p.snd]--;
			sum -= 2;
			assert(s.rbegin()->fst * 2 <= sum);
			ver(n);
		}
		if(sum == 3) {
			putchar(' ');
			pii p = *s.rbegin();
			s.erase(p); s.insert(pii(p.fst - 1, p.snd)); a[p.snd]--;
			putchar('A' + p.snd);
			sum--;
			assert(s.rbegin()->fst * 2 <= sum);
			ver(n);
		}
		putchar(' ');
		while(s.rbegin()->fst > 0) {
			pii p = *s.rbegin();
			s.erase(p); s.insert(pii(p.fst - 1, p.snd));
			putchar('A' + p.snd);
		}
		putchar('\n');
	}
}
