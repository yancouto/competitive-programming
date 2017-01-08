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

const double pi = acos(-1);

int main() {
	for_tests(t, tt) {
		int x, y, p;
		scanf("%d %d %d", &p, &x, &y);
		printf("Case #%d: ", tt);
		if(p == 0) { puts("white"); continue; }
		x -= 50;
		y -= 50;
		if(x * x + y * y > 50 * 50) { puts("white"); continue; }
		int ny = -x, nx = y;
		double ang = atan2(ny, nx);
		if(ang <= 0) ang = -ang;
		else ang = 2 * pi - ang;
		if(ang <= p * 2. * pi / 100.) puts("black");
		else puts("white");
	}
}
