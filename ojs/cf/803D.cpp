#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n, k;
string s[1123456];
vector<int> sz[1123456];
int lines(int W) {
	int cur = 0, curs = 0, lines = 1;
	for(int i = 0; i < n; i++) {
		if(cur + sz[i].back() - (curs? sz[i][curs-1] : 0) + (i < n - 1) <= W) cur += sz[i].back() - (curs? sz[i][curs - 1] : 0) + (i < n - 1), curs = 0;
		else {
			int mx = -1;
			for(int j = curs; j < s[i].size(); j++)
				if(s[i][j] == '-') {
					if(cur + sz[i][j] - (curs? sz[i][curs - 1] : 0) + 1 <= W) mx = j;
					else break;
				}
			if(mx != -1) cur += sz[i][mx] - (curs? sz[i][curs - 1] : 0) + 1, curs = mx + 1;
			else if(cur == 0) return INT_MAX;
			else lines++, cur = 0;
			i--;
		}
	}
	return lines;
}

int main() {
	scanf("%d ", &k);
	while(cin >> s[n++]);
	n--;
	for(int i = 0; i < n; i++) {
		for(char c : s[i])
			sz[i].pb((sz[i].empty()? 0 : sz[i].back()) + 1);
	}
	int l = 1, r = 1123456;
	while(l < r) {
		int m = (l + r) / 2;
		if(lines(m) <= k) r = m;
		else l = m + 1;
	}
	printf("%d\n", l);
}
