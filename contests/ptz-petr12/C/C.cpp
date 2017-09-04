#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pb push_back

struct vec {
	ll x, y;

	ll operator * (vec o) {
		return x*o.x + y*o.y;
	}
	ll operator ^ (vec o) {
		return x*o.y - y*o.x;
	}

	vec operator + (vec o) {
		return vec({x + o.x, y + o.y});
	}
	vec operator - (vec o) {
		return vec({x - o.x, y - o.y});
	}
	vec operator / (ll d) {
		return vec({x/d, y/d});
	}

	vec flip () {
		return vec({-y, x});
	}

	bool operator == (vec o) {
		return x == o.x && y == o.y;
	}

	bool in_seg (vec a, vec b) {
		return ((((*this)-a)*((*this)-b)) <= 0) && ((((*this)-a)^((*this)-b)) == 0);
	}
};

vec v[2][4];

int main () {
#ifdef ONLINE_JUDGE
	freopen("equal-squares.in", "r", stdin);
	freopen("equal-squares.out", "w", stdout);
#endif
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j += 2) {
			scanf("%lld %lld", &v[i][j].x, &v[i][j].y);
			v[i][j].x = 2 * v[i][j].x;
			v[i][j].y = 2 * v[i][j].y;
		}

		vec md = (v[i][0] + v[i][2])/2;
		v[i][1] = md + (v[i][0] - md).flip();
		v[i][3] = md + (v[i][2] - md).flip();
	}

	if (v[0][0] == v[0][1]) {
		if (v[0][0] == v[1][0])
			printf("Infinity\n");
		else
			printf("1\n");
		return 0;
	}

	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (v[0][i] == v[1][j]) {
				cnt++;
			}
		}
	}

	if (cnt == 1) {
		printf("Infinity\n");
		return 0;
	} else if (cnt) {
		printf("3\n");
		return 0;
	}

	for (int k = 0; k < 2; k++) { 
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (v[k][i].in_seg(v[!k][j], v[!k][(j+1)%4])) {
					printf("3\n");
					return 0;
				}
			}
		}
	}

	printf("4\n");
}
