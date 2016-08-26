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
const int modn = 10000;
inline int mod(int x) { return x % modn; }
int fexp(int x, int e) {
	int resp = 1;
	for(int i = 1; i <= e; i <<= 1) {
		if(i & e) resp = mod(resp * x);
		x = mod(x * x);
	}
	return resp;
}

char nn[20];
int memo[10][2][10];
int sd(int d, bool pre, int num) {
	if(!nn[d]) return num;
	int &ret = memo[d][pre][num];
	if(ret != -1) return ret;
	ret = 0;
	for(int i = 0; i <= 9; i++) {
		if(pre && i > (nn[d] - '0')) break;
		ret = mod(ret + sd(d + 1, pre && i == (nn[d] - '0'), (i || num)? num + 1 : 0));
	}
	return ret;
}
int sol;
void add(int x) {
	sol = mod(sol + x);
}

int main() {
	int n, t = 0;
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		memset(nn, 0, sizeof nn);
		sprintf(nn, "%d", n);
		memset(memo, -1, sizeof memo);
		int sdn = sd(0, true, 0); // digit count
		int x = fexp(2, n - 1); // 2^(n-1)
		sol = mod(n + (sdn - 1)); // x, x2, x3, ...
		add(sdn * x); // 1,2,3,4,... from a's
		add(mod(n) * x); // a's
		add(2 * mod(n - 1)); // ( and )
		add(n); // + outside parenthesis
		add(2 * x - mod(n + 1) + modn); // + inside parenthesis
		printf("Case %d: %d\n", ++t, sol);
	}
}
