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
const int N = 100009;
int p[N], p1[N], p2[N];
int seen[N], k[N];

int main() {
	int i, n;
	for_tests(t, tt) {
		scanf("%d", &n);
		//n = (rand() % 50) + 1;
		for(i = 1; i <= n; i++)
			seen[i] = false, p1[i] = i, p2[i] = i, k[i] = 0;
		for(i = 1; i <= n; i++)
			scanf("%d", &p[i]);
		//for(i = 1; i <= n; i++)
		//	p[i] = i;
		//random_shuffle(p + 1, p + 1 + n);
		for(i = 1; i <= n; i++)
			if(p[i] != i)
				break;
		if(i > n) { printf("0\n"); continue; }
		for(i = 1; i <= n; i++)
			if(p[i] != i && p[p[i]] != i)
				break;
		if(i > n) {
			printf("1\n");
			printf("%d", p[1]);
			for(i = 2; i <= n; i++)
				printf(" %d", p[i]);
			putchar('\n');
			continue;
		}
		for(i = 1; i <= n; i++)
			if(!seen[i]) {
				int j = i;
				deque<int> d;
				while(!seen[j]) {
					seen[j] = true;
					d.pb(j);
					j = p[j];
				}
				int l = 0, r = d.size() - 1;				
				while(r > l) {
					swap(p1[d[l]], p1[d[r]]);
					l++; r--;
				}
				if(l == r) r++;
				else r += 2, l--;
				while(r < d.size()) {
					swap(p2[d[l]], p2[d[r]]);
					r++; l--;
				}
			}
		for(i = 1; i <= n; i++)
			k[p1[i]]++;
		for(i = 1; i <= n; i++)
			assert(k[i] == 1);
		for(i = 1; i <= n; i++)
			k[p2[i]]++;
		for(i = 1; i <= n; i++)
			assert(k[i] == 2);
		for(i = 1; i <= n; i++)
			assert(p2[i] == i || p2[p2[i]] == i);
		for(i = 1; i <= n; i++)
			assert(p1[i] == i || p1[p1[i]] == i);
		for(i = 1; i <= n; i++)
			assert(p[i] == p2[p1[i]]);
		printf("2\n");
		printf("%d", p2[1]);
		for(i = 2; i <= n; i++)
			printf(" %d", p2[i]);
		putchar('\n');
		printf("%d", p1[1]);
		for(i = 2; i <= n; i++)
			printf(" %d", p1[i]);
		putchar('\n');
	}
}
