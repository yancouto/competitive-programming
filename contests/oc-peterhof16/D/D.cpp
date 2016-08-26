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

int main() {
	int i, n, j;
	scanf("%d", &n);
	if(n == 9) {
		puts("Yes\n1 2 3 4 5 6 7 8 9\n"
		"1 3 5 2 4 7 9 6 8\n"
		"1 4 6 2 8 3 9 5 7\n"
		"1 5 8 4 9 2 7 3 6");
		return 0;
	}
	for(n = 3; n <= 500; n += 2) {
		for(i = 2; i < n; i++)
			if(!(n % i))
				break;
		if(i < n) printf("%d\n", n);
	}
	if(i < n) { puts("No"); return 0; }
	puts("Yes");
	for(i = 1; i <= (n - 1) / 2; i++)
		for(j = 0; j < n; j++)
			printf("%d%c", ((j * i) % n) + 1, " \n"[j == n - 1]);
}
