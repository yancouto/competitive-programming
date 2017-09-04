#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pb push_back

struct vec {
	ll x, y;
	vec operator - (vec o) { return vec{x - o.x, y - o.y}; }
	ll operator ^ (vec o) { return x * o.y - y * o.x; }
	ll operator * (vec o) { return x * o.x + y * o.y; }
	ll ar(vec a, vec b) { return (b - a) ^ ((*this) - a); }
	int sd(vec a, vec b) { ll o = ar(a, b); return (o < 0) - (0 < o); }
	bool in_seg(vec a, vec b) { return (sd(a, b) == 0) && !(0 < (((*this) - a) * ((*this) - b))); }
	bool operator == (vec o) const { return x == o.x && y == o.y; }
};

vec v[112][112];

int main () {
#ifdef ONLINE_JUDGE
	freopen("equal-squares.in", "r", stdin);
	freopen("equal-squares.out", "w", stdout);
#endif
	int i, j, k;
	for(i = 0; i < 2; i++)
		for(j = 0; j < 4; j += 2)
			scanf("%lld %lld", &v[i][j].x, &v[i][j].y);

	for(i = 0; i < 2; i++) {
		v[i][1] = vec{v[i][0].x, v[i][2].y};
		v[i][3] = vec{v[i][2].x, v[i][0].y};
	}
	
	if(v[0][0] == v[0][2]) {
		if(v[0][0] == v[1][0]) puts("Infinity");
		else puts("1");
		return 0;
	}

	int count = 0;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			count += (v[0][i] == v[1][j]);
	if(count == 1) { puts("Infinity"); return 0; }
	else if(count == 2) { puts("3"); return 0; }
	else assert(count == 0);
	
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			for(k = 0; k < 2; k++)
				if(v[k][i].in_seg(v[!k][j], v[!k][(j+1)%4])) {
					puts("3");
					return 0;
				}
	puts("4");
}
