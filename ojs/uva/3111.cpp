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

const int N = 1123456;
int dv[N];

int main() {
	int i, j, n;
	for(i = 2; i < N; i++)
		if(dv[i] == 0)
			for(j = i; j < N; j += i)
				dv[j] = i;
	for_tests(t, tt) {
		scanf("%d", &n);
		int mx = 1, cur = 0, lst = -1;
		while(n != 1) {
			int x = dv[n];
			n /= x;
			if(x != lst) cur = 0, lst = x;
			mx = max(mx, ++cur);
		}
		printf("%d\n", mx);
	}
}
