#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

char s[512345];

int main () {
	int i, m;
	set<int> op, cl;
	scanf("%s", s);
	for(i = 0; s[i]; i++)
		if(s[i] == '(')
			op.insert(i);
		else
			cl.insert(i);
	op.insert(1e8);
	cl.insert(1e8 + 1);
	scanf("%d", &m);
	while(m--) {
		int l, r;
		scanf("%d %d", &l, &r); l--; r--;
		int ct = 0;
		while(true) {
			int L = *op.lower_bound(l);
			int R = *cl.lower_bound(L);
			if(R > r) break;
			ct += 2;
			cl.erase(R);
			op.erase(prev(op.lower_bound(R)));
		}
		printf("%d\n", ct);
	}
}
