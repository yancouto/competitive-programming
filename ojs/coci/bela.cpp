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

int nos[256], su[256];

int main() {
	nos['A'] = su['A'] = 11;
	nos['K'] = su['K'] = 4;
	nos['Q'] = su['Q'] = 3;
	nos['J'] = 2; su['J'] = 20;
	nos['T'] = su['T'] = 10;
	su['9'] = 14;
	int n; char B, c, s;
	scanf("%d %c", &n, &B);
	int tot = 0, i;
	for(i = 0; i < 4*n; i++) {
		scanf(" %c %c", &c, &s);
		tot += (s == B? su : nos)[c];
	}
	printf("%d\n", tot);
}
