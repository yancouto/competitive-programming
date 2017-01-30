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

const int N = 1e5+8;
int n, l;
int v[N];

int main () {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d", &n, &l);
	for (int i = 0; i < n; i++) {
		int a;
		scanf("%d", &a);
		v[a]++;
	}

	for (int i = 0; i < N; i++)
		if (v[i]%l) {
			printf("ARGH!!1\n");
			return 0;
		}
	
	printf("OK\n");
}
