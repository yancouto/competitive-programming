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

char s[100];
int main() {
	int i, j, n, k = 0;
	scanf("%d", &n);
	set<string> used;
	map<string, vector<string>> mp, mp2;
	for(i = 0; i < n; i++) {
		scanf("%s", s);
		if(!used.insert(s).snd) continue;
		int k = strlen(s);
		s[k] = s[k + 1] = '/';
		s[k + 2] = 0;
		for(j = 7; s[j] != '/'; j++);
		s[j] = 0;
		mp[string(s +  7)].pb(string(s + j + 1));
	}
	for(auto &it : mp) {
		sort(it.snd.begin(), it.snd.end());
		string f = "";
		for(string &s : it.snd)
			f += s;
		if(mp2[f].size() == 1) k++;
		mp2[f].pb(it.fst);
	}
	printf("%d\n", k);
	for(auto &it : mp2)
		if(it.snd.size() > 1) {
			for(string &s : it.snd)
				printf("http://%s ", s.c_str());
			putchar('\n');
		}
}
