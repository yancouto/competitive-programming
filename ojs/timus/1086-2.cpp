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

bool prime(int x) {
	for(int i = 2; i * i <= x; i++)
		if(!(x % i))
			return false;
	return true;
}

int p[21234], sn;
int main() {
	int i, k;
	for(i = 2; sn < 15009; i++)
		if(prime(i))
			p[sn++] = i;
	for_tests(t, tt) {
		scanf("%d", &k);
		printf("%d\n", p[k-1]);
	}
}
