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
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int a[112345];
char s[100];
int main() {
	int i, j, n, q, x;
	scanf("%d %d", &n, &q);
	for(i = 1; i <= n; i++) scanf("%d", &a[i]);
	set<pii> s;
	for(i = 1; i <= n; i++) s.insert(pii(a[i], i));
	for(i = 0; i < q; i++) {
		scanf("%s %d", ::s, &x);
		if(::s[0] == 'i') {
			auto it = s.lower_bound(pii(x, -1));
			if(it == s.end()) puts("-1");
			else {
				printf("%d\n", it->snd);
				s.erase(it);
			}
		} else {
			s.insert(pii(a[x], x));
		}
	}
}
