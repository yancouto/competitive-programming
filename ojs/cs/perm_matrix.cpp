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
const int N = 1123456;
int a[N], p[N], b[N];

int main() {
	int i, j, n, m;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n * m; i++)
		scanf("%d", &a[i]);
	multimap<int, int> pr; multimap<int, int> cur;
	map<int, int> ocpr, occu;
	for(i = 0; i < m; i++) p[i] = i;
	for(i = 1; i < n; i++) {
		pr.clear(); cur.clear();
		for(j = 0; j < m; j++) {
			pr.insert(pii(a[(i - 1) * m + j], p[(i - 1) * m + j]));
			ocpr[a[(i - 1) * m + j]]++;
			cur.insert(pii(a[i * m + j], j));
			occu[a[i * m + j]]++;
		}
		for(j = 0; j < m; j++) {
			int t1 = ocpr.rbegin()->fst;
			int t2 = occu.rbegin()->fst;
			if(ocpr[t2] + occu[t2] > ocpr[t1] + occu[t1]) swap(t1, t2);
			if(ocpr[t1] + occu[t1] > m - j) { puts("-1"); return 0; }
			if(ocpr[t1] + occu[t1] == m - j && t1 == occu.rbegin()->fst) {
				printf("breaking\n");
				t1 = occu.rbegin()->fst;
				auto it = ocpr.upper_bound(t1);
				if(it == ocpr.end()) it = prev(ocpr.lower_bound(t1));
				auto it2 = cur.find(it->snd);
				auto it3 = pr.find(it->snd);
				p[i * m + it3->snd] = it2->snd;
				pr.erase(it3); cur.erase(it2);
				break;
			} else {
				t1 = ocpr.rbegin()->fst;
				auto it = occu.upper_bound(t1);
				if(it == occu.end()) it = prev(occu.lower_bound(t1));
				auto it2 = pr.find(it->snd);
				auto it3 = cur.find(it->snd);
				p[i * m + it3->snd] = it2->snd;
				cur.erase(it3); pr.erase(it2);
			}
		}
	}
	for(i = 0; i < n * m; i++)
		b[i * m + p[i]] = a[i];
	for(i = 0; i < n * m; i++)
		printf("%d ", b[i]);
	putchar('\n');
}
