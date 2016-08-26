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

char s[11234];
string ext[1123];
int ct[1123];
map<string, int> mp;
int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%s", s);
		for(j = 0; s[j] != '.'; j++);
		if(!mp.count(s + j + 1)) {
			mp[s + j + 1] = mp.size() - 1;
			ext[mp[s + j + 1]] = s + j + 1;
		}
		ct[mp[s + j + 1]]++;
	}
	for(i = 0; i < mp.size(); i++)
		printf("%s: %d\n", ext[i].c_str(), ct[i]);
}
