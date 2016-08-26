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
char s[109], s2[109];
int main() {
	int i, j, n;
	scanf("%d", &n);
	map<string, vector<string> > mp;
	for(i = 0; i < n; i++) {
		scanf("%s", &s);
		int k = strlen(s);
		for(j = 0; j < k; j++)
			s2[j] = tolower(s[j]);
		s2[k] = 0;
		char *at = strchr(s2, '@');
		if(strcmp(at + 1, "bmail.com") == 0) {
			int g = 0;
			for(j = 0; s2[j] != '@'; j++) {
				if(s2[j] == '+') break;
				if(s2[j] != '.') s2[g++] = s2[j];
			}
			for(; *at; at++)
				s2[g++] = *at;
			s2[g] = 0;
		}
		mp[s2].pb(s);
	}
	printf("%d\n", mp.size());
	for(auto &e : mp) {
		vector<string> &v = e.snd;
		printf("%d", v.size());
		for(string &ss : v)
			printf(" %s", ss.c_str());
		putchar('\n');
	}
}
