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

int pw[8];
int x[200009];
int k[3], p[3], mrk[200009];
int main() {
	int i, n, a, b, c;
	scanf("%d", &n);
	scanf("%d %d %d", &a, &b, &c);
	multiset<int> s;
	for(i = 0; i < n; i++) {
		scanf("%d", &x[i]);
		if(x[i] > a + b + c) { puts("-1"); return 0; }
	}
	sort(x, x + n);
	k[0] = a; k[1] = b; k[2] = c;
	sort(k, k + 3);
	for(i = 0; i < 3; i++)
		p[i] = (upper_bound(x, x + n, k[i]) - x) - 1;
	int tot = 0;
	while(p[0] >= 0 && p[1] >= 0 && p[2] >= 0) {
		while(p[0] >= 0 && mrk[p[0]]) p[0]--;
		if(p[0] < 0) break;
		mrk[p[0]] = 1;
		while(p[1] >= 0 && mrk[p[1]]) p[1]--;
		if(p[1] < 0) { mrk[p[0]] = 0; break; }
		mrk[p[1]] = 1;
		while(p[2] >= 0 && mrk[p[2]]) p[2]--;
		if(p[2] < 0) { mrk[p[0]] = mrk[p[1]] = 0; break; }
		mrk[p[2]] = 1;
		tot++;
	}
	for(i = 0; i < n; i++)
		if(!mrk[i])
			s.insert(x[i]);
	for(i = 0; i < 8; i++)
		pw[i] = (i & 1) * a + ((i & 2) > 0) * b + ((i & 4) > 0) * c;
	sort(pw, pw + 8);
	while(!s.empty()) {
		tot++;
		int val = *s.rbegin();
		int p = *lower_bound(pw, pw + 8, val);
		s.erase(s.find(val));
		auto it = s.upper_bound(a + b + c - p);
		if(it != s.begin()) s.erase(prev(it));
	}
	printf("%d\n", tot);
}
