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

char S[100];
vector<string> s[1123];
deque<int> st[1123];
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int i, n, j, k;
	scanf("%d", &n);
	int tot = 0;
	for(i = 0; i < n; i++) {
		scanf("%d", &k);
		for(j = 0; j < k; j++) {
			scanf("%s", S);
			s[i].pb(S);
		}
		for(j = 0; j < k; j++)
			if(j == k - 1 || s[i][j] != s[i][j + 1])
				st[i].pb(s[i][j] == "c");
		if(!st[i].empty() && st[i].front() == 0) tot++, st[i].pop_front();
	}
	for(i = 0; i < n; i++) tot += st[i].size();
	if(n == 1) {
		if(st[0].size() > 3) puts("-1");
		else printf("%d\n", tot - (st[0].size() > 1));
		return 0;
	}
	int g = 0;
	for(i = 0; i < n; i++) g += !st[i].empty();
	for(i = 0; i < n; i++)
		if(st[i].size() > 1 && (g >= 2 || st[i].size() < 4)) {
			tot--;
			break;
		}
	printf("%d\n", tot);
}
