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

vector<int> v;

int main() {
	for_tests(t, tt) {
		v.clear();
		int i, k;
		scanf("%d", &k);
		if(k == 1) { printf("1\n1\n"); continue; }
		for(i = 31; i >= 0; i--)
			if((k >> i) & 1)
				break;
		int sz = i;
		int a = 1000;
		int b = 1;
		for(i = 0; i < sz; i++) {
			v.pb(a); v.pb(a - 1); a += 100;
			if((k >> (sz - i - 1)) & 1)
				while(b <= i + 1)
					v.pb(b++);
		}
		vector<int> v2(v);
		sort(v2.begin(), v2.end());
		printf("%d\n", v.size());
		for(int x : v) printf("%d ", int(lower_bound(v2.begin(), v2.end(), x) - v2.begin()) + 1);
		putchar('\n');
	}
}
