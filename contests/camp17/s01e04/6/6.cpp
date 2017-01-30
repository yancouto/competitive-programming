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
#define deb /*fprintf(stderr, ":%d\n", __LINE__)*/

char s[1123456];

char o[256], inv[256];

int main() {
	int i, j; int t;
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &t);
	o['('] = ')';
	o['['] = ']';
	o['{'] = '}';
	o['<'] = '>';
	for(i = 0; i < 256; i++) inv[o[i]] = i;
	while(t--) {
		scanf("%s", s);
		vector<multiset<char>> st;
		for(i = 0; s[i]; ) {
			multiset<char> cj;
			for(j = i; s[j] && !o[s[i]] == !o[s[j]]; j++) cj.insert(s[j]);
			if(o[s[i]]) { // open
				st.pb(cj);
			} else { // close
				bool bad = false;
				while(!cj.empty()) {
					deb;
					if(!st.empty() && st.back().find(inv[*cj.begin()]) != st.back().end()) {
						deb;
						st.back().erase(st.back().find(inv[*cj.begin()]));
						cj.erase(cj.begin());
					} else if(!st.empty() && !st.back().empty() && cj.find(o[*st.back().begin()]) != cj.end()) {
						deb;
						cj.erase(cj.find(o[*st.back().begin()]));
						st.back().erase(st.back().begin());
					} else {
						deb;
						bad = true;
						break;
					}
					if(!st.empty() && st.back().empty()) st.pop_back();
				}
				if(bad) { break; }
			}
			i = j;
		}
		if(!s[i] && st.empty()) puts("T");
		else puts("NIL");
	}
}
