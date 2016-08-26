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
const int N = 209;

int st[N], sn;
int main() {
	int n, x;
	scanf("%d", &n);
	int l = 0, r = 0, i, j;
	for(i = 0; i < n; i++) {
		sn = 0;
		for(j = 0; j < n; j++) {
			scanf("%d", &x);
			if(x == -1) continue;
			if(x & 1)
				st[sn++] = x;
			else {
				while(sn && st[sn-1] < x) sn--;
				if(!sn) l++;
			}
		}
		r += sn;
	}
	printf("%d %d\n", l, r);
}
