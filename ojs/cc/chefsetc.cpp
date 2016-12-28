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

int main() {
	int i, j, a[14];
	for_tests(t, tt) {
		for(i = 0; i < 4; i++) scanf("%d", &a[i]);
		for(i = 1; i < (1 << 4); i++) {
			int sum = 0;
			for(j = 0; j < 4; j++)
				if(i & (1 << j))
					sum += a[j];
			if(sum == 0) break;
		}
		if(i < (1 << 4)) puts("Yes");
		else puts("No");
	}
}
