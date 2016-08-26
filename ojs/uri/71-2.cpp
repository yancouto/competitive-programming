#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

int mdc(int a, int b) {
	if(b == 0) return a;
	return mdc(b, a % b);
}

int a[1009];
int main() {
	int i, j, n, m, d, kd;
	set<int> s;
	for(i = 2; i <= 500; i++)
		for(j = i + 1; j <= 500; j++) {
			int mm = i  * j / mdc(i, j);
			if(mm > 500 && mm <= 1000)
				s.insert(mm);
		}
	printf("%d\n", s.size());
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &d, &kd);
		for(j = d; j <= kd; j += d)
			a[j]++;
	}
	sort(a, a + 1009, greater<int>());
	int tot = 0;
	for(i = 0; i < m; i++)
		tot += a[i];
	printf("%d\n", tot);
}
