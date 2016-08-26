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
const int N = 1123456;
int dv[N];
int acc[11][N];

int main() {
	int a, b, n, i, j;
	for(i = 2; i < N; i++)
		if(!dv[i])
			for(j = i; j < N; j += i)
				dv[j]++;
	for(i = 1; i < N; i++)
		acc[dv[i]][i] = 1;
	for(j = 0; j < 10; j++) 
		for(i = 1; i < N; i++)
			acc[j][i] += acc[j][i - 1];
	for_tests(t, tt) {
		scanf("%d %d %d", &a, &b, &n);
		printf("%d\n", acc[n][b] - acc[n][a - 1]);

	}
}
