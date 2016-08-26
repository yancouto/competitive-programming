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

int n, a[200];
bool ok(int k) {
	deque<int> d(a, a + n);
	k++;
	while(--k && !d.empty()) {
		d.front() -= k;
		d.back() -= k;
		if(min(d.front(), d.back()) < 0) return false;
		if(d.front() == 0) d.pop_front();
		if(!d.empty() && d.back() == 0) d.pop_back();
	}
	return k == 0;
}

int main() {
	int i;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	if((accumulate(a, a + n, 0) & 1) == 0)
		for(i = 100; i > 1; i--)
			if(ok(i)) {
				printf("%d\n", i);
				return 0;
			}
	if((n == 1 && a[0] == 2) || (n == 2 && a[0] == a[1] && a[0] == 1)) puts("1");
	else puts("no quotation");
}
