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

map<string, int> mp[23];
char s[25];
int main() {
	int i, j, g, n;
	for_tests(t, tt) {
		for(i = 0; i < 20; i++)
			mp[i].clear();
		scanf("%d", &n);
		for(i = 0; i < n; i++) {
			scanf("%s", s);
			int k = strlen(s);
			set<string> se;
			se.insert("");
			for(j = k; j >= 0; j--) {
				s[j] = 0;
				for(g = 0; g < j; g++)
					se.insert(s + g);
			}
			for(const string &ss : se)
				mp[ss.size()][ss]++;
		}
		for(i = 20; i >= 0; i--) {
			bool found = false;
			string st;
			for(auto &e : mp[i])
				if(e.snd == n) {
					st = e.fst;
					found = true;
					break;
				}
			if(found) { puts(st.c_str()); break; }
		}
	}
}
