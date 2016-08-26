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
int win[N], nuw[26], b[N], e[N];
char s[100];

int main() {
	int i, n, k;
	for_tests(t, tt) {
		scanf("%d %d", &n, &k);
		for(i = 0; i < n; i++) {
			scanf("%s", s);
			b[i] = s[0] - 'a';
			e[i] = s[strlen(s) - 1] - 'a';
		}
		memset(nuw, 0, sizeof nuw);
		for(i = n - 1; i >= 0; i--) {
			if(i + k + 1 < n && win[i + k + 1]) nuw[b[i + k + 1]]--;
			win[i] = nuw[e[i]] == 0;
			nuw[b[i]] += win[i];
		}
		for(i = 0; i < k && !win[i]; i++);
		if(i < k) puts("Alex");
		else puts("Bob");
	}
}
