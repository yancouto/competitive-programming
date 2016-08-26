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

int st[100009], sn;
int ct[1009], a[1009], seen[1009];
int main() {
	int i, n, j, k;
	while(scanf("%d", &n) != EOF && n) {
		for(i = 0; i < n; i++) ct[i] = 0;
		for(i = 0; i < n; i++) scanf("%d", &a[i]), ct[--a[i]]++;
		if(*max_element(ct, ct + n) > 1) { puts("No solution"); continue; }
		sn = 0;
		for(i = 0; i < n; i++) {
			int j = i;
			vector<int> cyc;
			while(!seen[j]) {
				seen[j] = 1;
				cyc.pb(j);
				j = a[j];
			}
			for(j = cyc.size() - 1; j > 0; j--) {
				int s = cyc[j], e = cyc[j - 1];
				if(s > e) {
					for(k = s; k > e; k--) st[sn++] = k - 1;
					for(k = e + 1; k < s; k++) st[sn++] = k;
				} else {
					for(k = s; k < e; k++) st[sn++] = k;
					for(k = e - 2; k >= s; k--) st[sn++] = k;
				}
			}
		}
		printf("%d", sn);
		for(i = 0; i < sn; i++)
			printf(" %d", st[i] + 1);
		putchar('\n');
	}
}
