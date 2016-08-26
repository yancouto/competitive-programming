#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
pii p[5];
int cross(int i, int j, int k) {
	return (p[j].x - p[i].x) * (p[k].y - p[i].y) - (p[j].y - p[i].y) * (p[k].x - p[i].x);
}

bool between(int i, int j, int k) {
	return ((p[k].x - p[j].x) * (p[k].x - p[i].x) + (p[k].y - p[j].y) * (p[k].y - p[i].y)) < 0;
}

int main() {
	while(true) {
		int i;
		scanf("%d %d %d", &p[0].x, &p[0].y, &i);
		if(i + p[0].x + p[0].y != 10000) return 0;
		for(i = 1; i < 4; i++)
			scanf("%d %d %*d", &p[i].x, &p[i].y);
		if(cross(0, 1, 2) == 0) {
			if(cross(0, 1, 3) == 0 && (between(0, 1, 3) || between(0, 2, 3) || between(1, 2, 3))) puts("YES");
			else puts("NO");
			continue;
		}
		bool a = true;
		a &= cross(0, 1, 3) != 0 && ((cross(0, 1, 3) < 0) == (cross(0, 1, 2) < 0));
		a &= cross(0, 2, 3) != 0 && ((cross(0, 2, 3) < 0) == (cross(0, 2, 1) < 0));
		a &= cross(1, 2, 3) != 0 && ((cross(1, 2, 3) < 0) == (cross(1, 2, 0) < 0));
		if(a) puts("YES");
		else puts("NO");
	}
}
