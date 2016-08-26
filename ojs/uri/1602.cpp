#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

int dv[2000009];
int hp[2000009];
void pre() {
	int i, j;
	for(i = 1; i <= 2000000; i++) {
		for(j = i; j <= 2000000; j+= i)
			dv[j]++;
		if(dv[dv[i]] == 2) hp[i] = 1;
		hp[i] += hp[i - 1];
	}
}

int main() {
	int n;
	pre();
	while(scanf("%d", &n) != EOF)
		printf("%d\n", hp[n]);
	return 0;
}
