#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

#define x first
#define m second

pii p[2123];

int main () {
	int n, k, i;
	scanf("%d %d", &n, &k);
	for(i = 0; i < n; i++)
		scanf("%lld %lld", &p[i].x, &p[i].m);
	sort(p, p + n, greater<pii>());
	ll lst = p[0].x;
	ll cur = 0;
	ll tot = 0;
	for(i = 0; i < n; i++) {
		if(p[i].x < 0) break;
		ll pcur = cur;
		cur += p[i].m;
		//printf("[%d] lst %lld cur %lld\n", i, lst, cur);
		if(cur >= k) {
			tot += lst;
			cur -= k;
			lst = p[i].x;
			tot += (cur / k) * lst;
			cur %= k;

			p[i].m -= (k - pcur);
			p[i].m %= k;
			if(p[i].m == 0) lst = p[i + 1].x;
		}
	}
	if(cur) tot += lst;

	cur = 0;
	for(int j = i; j < n; j++) p[j].x = -p[j].x;
	sort(p + i, p + n, greater<pii>());
	lst = p[i].x;
	for(; i < n; i++) {
		ll pcur = cur;
		cur += p[i].m;
		//printf("[%d]- lst %lld cur %lld\n", i, lst, cur);
		if(cur >= k) {
			tot += lst;
			cur -= k;
			lst = p[i].x;
			tot += (cur / k) * lst;
			cur %= k;

			p[i].m -= (k - pcur);
			p[i].m %= k;
			if(p[i].m == 0) lst = p[i + 1].x;
		}
	}
	if(cur) tot += lst;
	printf("%lld\n", tot * 2ll);
}
