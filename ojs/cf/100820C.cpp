#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(args...) {}
#else
#	define LLD "%lld"
#	define debug(args...) fprintf(stderr, args)
#endif

string name[1123];
vector<int> v[1123];
char s[1123];
int p[1123];
int main() {
	int i, j, n;
	scanf("%d", &n);
	map<string, int> mp;
	mp["lower"] = 0;
	mp["middle"] = 1;
	mp["upper"] = 2;
	for(i = 0; i < n; i++) {
		scanf("%s", s);
		name[i] = s;
		name[i].pop_back();
		while(true) {
			scanf("%s", s);
			if(!strcmp(s, "class")) break;
			v[i].pb(mp[s]);
		}
		reverse(v[i].begin(), v[i].end());
		while(v[i].size() < 60) v[i].pb(1);
		p[i] = i;
	}
	sort(p, p + n, [](int i, int j) { if(v[i] != v[j]) return v[i] > v[j]; else return name[i] < name[j]; });
	for(i = 0; i < n; i++)
		printf("%s\n", name[p[i]].c_str());
}
