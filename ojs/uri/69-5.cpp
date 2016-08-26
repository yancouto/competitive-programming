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

struct cil {
	int h, r, c;
	bool operator < (cil o) const { return r > o.r; }
} cs[1009];
int n;
int memo[1002][1002];
int solve(int lst, int i) {
	if(i == n) return 0;
	int &r = memo[lst][i];
	if(r != -1) return r;
	r = solve(lst, i + 1);
	if(cs[i].r < cs[lst].r && cs[lst].c != ((cs[i].c + 1)%4)) r = max(r, cs[i].h + solve(i, i + 1));
	return r;
}


map<string, int> mp;
char str[100];
int main() {
	int i;
	mp["VERMELHO"] = 0;
	mp["LARANJA"] = 1;
	mp["AZUL"] = 2;
	mp["VERDE"] = 3;
	while(true){
		scanf("%d", &n);
		if(!n) return 0;
		for(i = 0; i < n; i++) {
			scanf("%d %d %s", &cs[i].h, &cs[i].r, str);
			cs[i].c = mp[str];
		}
		sort(cs, cs + n);
		memset(memo, -1, sizeof memo);
		int mx = 0;
		for(i = 0; i < n; i++)
			mx = max(mx, cs[i].h + solve(i, i + 1));
		printf("%d centimetro(s)\n", mx);
	}
}
