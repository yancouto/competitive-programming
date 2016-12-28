#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<string, map<string, int>> mp;

char city[112], state[112];

int main() {
	freopen("citystate.in", "r", stdin);
	freopen("citystate.out", "w", stdout);
	int i, n;
	scanf("%d", &n);
	ll tot = 0;
	for(i = 0; i < n; i++) {
		scanf("%s %s", city, state);
		string c = city;
		c = c.substr(0, 2);
		if(c != string(state))
			tot += mp[c][state];
		mp[state][c]++;
	}
	printf("%lld\n", tot);
}
