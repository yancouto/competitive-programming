#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

#define pb push_back
#define fst first
#define snd second

typedef ll cood;
cood eps = 0;

struct vec {
	cood x, y;
	int i;
	vec() : x(0), y(0) {}
	vec(cood a, cood b) : x(a), y(b) {}

	vec operator - (vec o) { return vec(x - o.x, y - o.y); }
	cood operator ^ (vec o) { return x * o.y - y * o.x; }
	cood ar(vec a, vec b) { return (b - a) ^ ((*this) - a); }
	int sd (vec a, vec b) { cood o = ar(a, b); return (o < -eps) - (eps < o); }
	bool operator < (vec o) const { return x < o.x; }
};

const int N = 223;

vec p[N];

int up[N][N], dw[N][N], upl[N], dwl[N], upr[N], dwr[N];

int n;

int memo[N][N][N];
int solve(int i, int up, int dw) {
	int &r = memo[i][up][dw];
	if(r != -1) return r;
	r = INT_MAX;
	for(int j = i + 1; j < n; j++)
		if(p[j].x > p[i].x)
			r = min(r, solve(j, up + ::up[i][j], dw + ::dw[i][j]));
	if(upr[i] >= 0) {
		up += upr[i];
		dw += dwr[i];
		int eq = n - up - dw;
		r = min(r, max({up, dw, eq}) - min({up, dw, eq}));
	}
	return r;
}

vector<int> ans;
void build(int i, int up, int dw) {
	int r = solve(i, up, dw);
	for(int j = i + 1; j < n; j++)
		if(p[j].x > p[i].x && r == solve(j, up + ::up[i][j], dw + ::dw[i][j])) {
			ans.pb(p[j].i + 1);
			return build(j, up + ::up[i][j], dw + ::dw[i][j]);
		}
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("division.in", "r", stdin);
	freopen("division.out", "w", stdout);
#endif
	memset(memo, -1, sizeof memo);
	int i, j, k;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%lld %lld", &p[i].x, &p[i].y);
		p[i].i = i;
	}
	sort(p, p + n);
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			for(k = 0; k < n; k++) {
				if(p[k].x > p[i].x && p[k].x <= p[j].x) {
					if(p[i].sd(p[j], p[k]) == -1) up[i][j]++;
					if(p[i].sd(p[j], p[k]) == +1) dw[i][j]++;
				}
			}
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			if(i != j && p[j].x <= p[i].x) {
				if(p[j].y == p[i].y) upl[i] -= 1e8;
				if(p[j].y > p[i].y) upl[i]++;
				if(p[j].y < p[i].y) dwl[i]++;
			}
		}
	}
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			if(i != j && p[j].x > p[i].x) {
				if(p[j].y == p[i].y) upr[i] -= 1e8;
				if(p[j].y > p[i].y) upr[i]++;
				if(p[j].y < p[i].y) dwr[i]++;
			}
		}
	}
	//for(i = 0; i < n; i++) printf("upl[%d] = %d\n", i, upl[i]);
	//for(i = 0; i < n; i++) printf("dwl[%d] = %d\n", i, dwl[i]);
	//for(i = 0; i < n; i++) printf("upr[%d] = %d\n", i, upr[i]);
	//for(i = 0; i < n; i++) printf("dwr[%d] = %d\n", i, dwr[i]);
	//for(i = 0; i < n; i++)
	//	for(j = i + 1; j < n; j++)
	//		printf("up[%d][%d] = %d\n", i, j, up[i][j]);
	//for(i = 0; i < n; i++)
	//	for(j = i + 1; j < n; j++)
	//		printf("dw[%d][%d] = %d\n", i, j, dw[i][j]);
	int mn = INT_MAX, mni = -1;
	for(i = 0; i < n; i++)
		if(upl[i] >= 0) {
			//printf("try[%d] = %d\n", i, solve(i, upl[i], dwl[i]));
			if(solve(i, upl[i], dwl[i]) < mn) {
				mn = solve(i, upl[i], dwl[i]);
				mni = i;
			}
		}
	//printf("ans %d\n", mn);
	ans.pb(p[mni].i + 1);
	build(mni, upl[mni], dwl[mni]);
	printf("%d\n", int(ans.size()));
	for(int x : ans)
		printf("%d ", x);
	putchar('\n');
}
