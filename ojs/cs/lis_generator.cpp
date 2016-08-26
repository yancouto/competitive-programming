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

vector<int> v;
pii memo[1000];
pii solve(int i) {
	pii &r = memo[i];
	if(r.fst != -1) return r;
	r = pii(1, 1);
	for(int j = i + 1; j < v.size(); j++) {
		if(v[j] < v[i]) continue;
		pii o = solve(j); o.fst++;
		if(o.fst == r.fst) r.snd += o.snd;
		else if(o.fst > r.fst) r = o;
	}
	return r;
}

int main() {
	int i, k;
	scanf("%d", &k);
	if(k == 1) { printf("1\n"); return 0; }
	for(i = 31; i >= 0; i--)
		if((k >> i) & 1)
			break;
	int sz = i;
	int a = 1000;
	int b = 1;
	for(i = 0; i < sz; i++) {
		v.pb(a); v.pb(a - 1); a += 100;
		if((k >> (sz - i - 1)) & 1)
			while(b <= i + 1)
				v.pb(b++);
	}
	for(int x : v) printf("%d ", x);
	putchar('\n');
	//memset(memo, -1, sizeof memo);
	//int lis = 0, tot = 0;
	//for(i = 0; i < v.size(); i++)
	//	lis = max(lis, solve(i).fst);
	//for(i = 0; i < v.size(); i++)
	//	if(solve(i).fst == lis)
	//		tot += solve(i).snd;
}
