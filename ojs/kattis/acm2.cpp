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

int a[100];
int main() {
	int n, p, i;
	scanf("%d %d", &n, &p);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	swap(a[p], a[0]);
	sort(a + 1, a + n);
	int ac = 0, pen = 0, cur = 0;
	for(i = 0; i < n; i++) {
		if(cur + a[i] <= 300) {
			ac++;
			cur += a[i];
			pen += cur;
		} else break;
	}
	printf("%d %d\n", ac, pen);
}
