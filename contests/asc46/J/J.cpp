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
const int N = 100009;

char s[N];
int nx[30];
int S[67108864];

int main() {
	freopen("jingles.in", "r", stdin);
	freopen("jingles.out", "w", stdout);
	int i, n;
	for_tests(t, tt) {
		scanf("%s", s);
		n = strlen(s);
		for(i = 0; i < 26; i++) nx[i] = -1;
		map<int, int> pos;
		vector<int> all;
		for(i = n - 1; i >= 0; i--) {
			int c = s[i] - 'a';
			if(nx[c] != -1) pos.erase(pos.find(nx[c]));
			nx[c] = i;
			pos[i] = c;
			int b = 0;
			for(auto it = pos.begin(); it != pos.end(); ++it) {
				pii p = *it;
				b |= (1 << p.snd);
				if(S[b] == 0) all.pb(b);
				int r = (next(it) == pos.end()? n : next(it)->fst);
				S[b] = max(S[b], r - i);
			}
		}
		ll tot = 0;
		for(int x : all) {
			tot += int(__builtin_popcount(x)) * S[x];
			S[x] = 0;
		}
		printf("%d %I64d\n", int(all.size()), tot);
	}
}
