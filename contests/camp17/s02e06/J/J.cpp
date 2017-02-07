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

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

int n;
map<string, set<int>> mp;

const int N = 1123;
int mrk[N][N];
char s[N][112];
int mx[N];

void deb(string s) {
	if(mp[s].empty()) return;
	printf("%s:", s.c_str());
	for(int x : mp[s]) printf(" %d", x); putchar('\n');
}

int main() {
	int i, j, n, l, m;
	rd(n); rd(l); rd(m);
	for(i = 0; i < n; i++) {
		scanf("%s", s[i]);
		mp[s[i]].insert(i);
	}
	for(auto &e : mp) {
		for(int x : e.snd)
			mx[x] = e.snd.size();
	}
	
	for(i = 0; i < m; i++) {
		int p1, w1, p2, w2;
		rd(p1); rd(w1); rd(p2); rd(w2); p1--; p2--; w1--; w2--;
		mp[s[p1]].erase(p1);
		mp[s[p2]].erase(p2);
		//printf("====== (%d, %d)\n", p1, p2); deb(s[p1]); deb(s[p2]);
		swap(s[p1][w1], s[p2][w2]);
		//printf("------\n"); deb(s[p1]); deb(s[p2]);
		mp[s[p1]].insert(p1);
		mp[s[p2]].insert(p2);
		int sz = mp[s[p1]].size();
		for(int x : mp[s[p1]])
			mx[x] = max(mx[x], sz);
		sz = mp[s[p2]].size();
		for(int x : mp[s[p2]])
			mx[x] = max(mx[x], sz);
		//puts("........"); for(auto &e : mp) deb(e.fst);
		//puts("|||||||||"); for(j = 0; j < n; j++) printf(">>%s\n", s[j]);
	}
	for(i = 0; i < n; i++)
		printf("%d\n", mx[i]);
}
