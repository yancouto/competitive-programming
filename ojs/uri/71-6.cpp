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
const int MAX = 1000006;
int dv[MAX], p[MAX];
void pre() {
	int i, j;
	for(i = 2; i < MAX; i++) {
		if(dv[i]) continue;
		for(j = 2*i; j < MAX; j += i)
			dv[j] = 1;
	}
	for(i = 3; i < MAX - 3; i++){
		if(!dv[i] && (!dv[i - 2] || !dv[i + 2]))
			p[i] = 1;
		p[i] += p[i - 1];
	}
}

int main() {
	int i, q, x, y;
	pre();
	scanf("%d", &q);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &x, &y);
		if(x > y) swap(x, y);
		printf("%d\n", p[y] - p[x - 1]);
	}
}
