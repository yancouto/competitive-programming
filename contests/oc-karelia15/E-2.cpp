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
const int N = 1000009;
int p[N], p1[N], p2[N], seen[N];

int main() {
	int i, n;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 1; i <= n; i++)
			seen[i] = false, p2[i] = p1[i] = i;
		for(i = 1; i <= n; i++)
			scanf("%d", &p[i]);
		for(i = 1; i <= n; i++)
			if(p[i] != i && p[p[i]] != i)
				break;
		if(i > n) {
			printf("1\n");
			for(i = 1; i <= n; i++)
				printf("%d ", p[i]);
			putchar('\n');
			continue;
		}
		for(i = 1; i <= n; i++)
			if(!seen[i]) {
				int j = i;
				vector<int> d;
				while(!seen[j]) {
					seen[j] = true;
					d.pb(j);
					j = p[j];
				}
				int l = 0, r = d.size() - 1;
				while(l < r) {
					swap(p1[d[l]], p1[d[r]]);
					l++; r--;
				}
				if(l == r) r++;
				else r += 2, l--;
				while(r < d.size() && l >= 0) {
					swap(p2[d[l]], p2[d[r]]);
					r++; l--;
				}
			}
		printf("2\n");
		for(i = 1; i <= n; i++)
			printf("%d ", p2[i]);
		putchar('\n');
		for(i = 1; i <= n; i++)
			printf("%d ", p1[i]);
		putchar('\n');
	}
}
