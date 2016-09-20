#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
typedef tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update> ord_set;

int main() {
	ord_set s;
	char op;
	int x;
	for_tests(tn, tt) {
		scanf(" %c %d", &op, &x);
		if(op == 'I') s[x] = 0;
		else if(op == 'D') s.erase(x);
		else if(op == 'K') {
			if(s.find_by_order(x-1) != s.end()) printf("%d\n", s.find_by_order(x-1)->fst);
			else puts("invalid");
		} else printf("%d\n", s.order_of_key(x));
	}

}
