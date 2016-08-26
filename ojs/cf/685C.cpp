#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif
#define abs asdasdasd

const int N = 112345;
ll a[N][3];
inline ll ts(int x) { return ((x > 0) * 2 - 1); }
inline ll apply(ll a[3], int bm) {
	return a[0] * ts(bm & 1) + a[1] * ts(bm & 2) + a[2] * ts(bm & 4);
}
inline ll abs(ll x) { if(x >= 0) return x; else return -x; }
int p[3];

int main() {
	int i, j, n, t, b, g;
	scanf("%d", &t);
	while(t--) {
		ll c[8];
		scanf("%d", &n);
		//n = 100000;
		for(i = 0; i < n; i++) scanf("%lld %lld %lld", &a[i][0], &a[i][1], &a[i][2]);
		//for(i = 0; i < n; i++) a[i][0] = rand(), a[i][1] = rand(), a[i][2] = rand();
		for(b = 0; b < 8; b++) {
			int bi = 0;
			for(i = 1; i < n; i++)
				if(apply(a[i], b) > apply(a[bi], b))
					bi = i;
			c[7 ^ b] = apply(a[bi], b);
		}
		ll ans = LLONG_MAX;
		ll a1, a2, a3;
		for(b = 0; b < 8; b++) {
			ll v2[3], ne[3];
			for(g = 0; g < 3; g++) {
				v2[g] = c[b ^ (1 << g)] - c[b];
				if(v2[g] % 2) v2[g]++;
				v2[g] /= 2;
			}
			for(g = 0; g < 3; g++) {
				int bm = (b ^ ((1 << g) ^ 7));
				ll X = c[bm] - c[b];
				if(X % 2) X++;
				X /= 2;
				ne[g] = max<ll>(0, X - (v2[0] + v2[1] + v2[2] - v2[g]));
			}
			p[0] = 0; p[1] = 1; p[2] = 2;
			ll MX = LLONG_MAX;
			ll VV[3] = {0, 0, 0};
			do {
				ll V[3] = {0, 0, 0};
				ll n0 = ne[p[0]], n1 = ne[p[1]], n2 = ne[p[2]];
				ll X = min(n1, n2);
				n1 -= X; n2 -= X; V[p[0]] += X;
				if(n1 > 0) {
					V[p[2]] += max(n1, n0);
				} else {
					V[p[1]] += max(n2, n0);
				}
				if(V[0] + V[1] + V[2] < MX) {
					MX = V[0] + V[1] + V[2];
					for(i = 0; i < 3; i++) VV[i] = V[i];
				}
			} while(next_permutation(p, p + 3));
			for(i = 0; i < 3; i++) v2[i] += VV[i];
			//ll X = min(ne[1], ne[2]);
			//v2[0] += X;
			//ne[1] -= X; ne[2] -= X;
			//if(ne[1] > 0) {
			//	v2[2] += max(ne[1], ne[0]);
			//} else {
			//	v2[1] += max(ne[2], ne[0]);
			//}
			ll X = c[b ^ 7] - c[b];
			if(X % 2) X++;
			X /= 2;
			v2[0] += max<ll>(0, X - (v2[0] + v2[1] + v2[2]));
			for(i = 0; i < 3; i++)
				if(!((b >> i) & 1))
					v2[i] = -v2[i];
			ll mx = 0;
			for(i = 0; i < n; i++)
				mx = max(mx, abs(a[i][0] - v2[0]) + abs(a[i][1] - v2[1]) + abs(a[i][2] - v2[2]));
			//assert(mx == apply(v2, b) + c[b]);
			if(mx < ans) {
				ans = mx;
				a1 = v2[0];
				a2 = v2[1];
				a3 = v2[2];
			}
		}
		printf("%lld %lld %lld\n", a1, a2, a3);
	}
}
