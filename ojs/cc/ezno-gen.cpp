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

int tot = 0, b, d;
int ans[100];
void solve(int i) {
	if(i == d) { tot++; return; }
	int bk[100];
	for(int k = i + 1; k <= d; k++)
		bk[k] = ans[k];
	for(int j = !i; j < b; j++) {
		if(!((bk[i+1] * b + j) % (i + 1))) {
			for(int k = i + 2; k <= d; k++)
				ans[k] = ((bk[k] * b + j) % k);
			solve(i + 1);
		}
	}
}

int main() {
	printf("int ans[][] = {\n");
	for(b = 2; b <= 16; b++) {
		printf("{%d", b-1);
		for(d = 2; d <= 50; d++) {
			memset(ans, 0, sizeof ans);
			tot = 0; solve(0);
			printf(", %d", tot);
		}
		printf("}%s\n", b == 16? "" : ",");
	}
	printf("};\n");
}
