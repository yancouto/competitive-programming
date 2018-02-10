#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int a[112];

int main() {
	for_tests(tn, tt) {
		for(int i = 0; i < 4; i++) scanf("%d", &a[i]);
		sort(a, a + 4);
		if(a[0] == a[1] && a[2] == a[3]) puts("YES");
		else puts("NO");
	}
}
