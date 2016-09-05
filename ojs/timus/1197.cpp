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

int di[8] = {1, -1, 2, -2, 1, -1, 2, -2};
int dj[8] = {2, 2, -1, -1, -2, -2, 1, 1};

int main() {
	int b, i, j; char a;
	for_tests(t, tt) {
		scanf(" %c %d", &a, &b);
		i = a - 'a'; j = b - 1;
		int ct = 0;
		for(int d = 0; d < 8; d++) {
			int ni = i + di[d], nj = j + dj[d];
			ct += (ni >= 0 && nj >= 0 && ni < 8 && nj < 8);
		}
		printf("%d\n", ct);
	}
}
