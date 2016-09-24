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
int x[1123];

int main(int argn, char **args) {
	srand(time(NULL));
	int i, j;
	int mx = argn > 1? atoi(args[1]) : 100000;
	int n = argn > 2? atoi(args[2]) : 10;
	printf("%d\n", n);
	for(i = 0; i < n; i++)
		x[i] = rand() % mx;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++) {
			int in = abs(x[i] - x[j]);
			if(in > 1000000) in = 0;
			else in = 1000000 - in;
			printf("%d%c", in, " \n"[j == n - 1]);
		}
}
