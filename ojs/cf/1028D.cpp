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
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;
char op[112];

int main() {
	int i, j, p;
	scanf("%d", &n);
	set<int> s;
	int sell = INT_MAX, buy = INT_MIN;
	int unknown = 0;
	ll tot = 1;
	for(i = 0; i < n; i++) {
		//printf("it %d\n", i);
		scanf(" %s %d", op, &p);
		//printf("%s %d\n", op, p);
		if(op[1] == 'D') { // ADD
			if(p < sell && p > buy) {
				unknown++;
			}
			s.insert(p);
		} else { // ACCEPT
			if(p > sell || p < buy) {
				puts("0");
				return 0;
			} else {
				if(p != buy && p != sell)
					tot = mod(tot * 2ll);
				auto it = s.find(p);
				if(it == s.begin()) buy = INT_MIN;
				else buy = *prev(it);
				if(next(it) == s.end()) sell = INT_MAX;
				else sell = *next(it);
			}
			unknown = 0;

			s.erase(p);
		}
	}
	printf("%lld\n", mod(tot * ll(unknown + 1)));
}
