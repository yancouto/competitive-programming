#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif
typedef long double ld;

int n;
int acc[1112];
vector<vector<int>> st[30];
map<vector<int>, int> pos[30];
vector<ld> an[30];

int go(int left, int mn, vector<int> v) {
	if(left == 0) {
		pos[v.size()][v] = st[v.size()].size();
		st[v.size()].pb(v);
		an[v.size()].pb(0);
		return 1;
	}
	if(left < mn) return 0;
	vector<int> v1 = v; v1.pb(mn);
	return go(left, mn + 1, v) + go(left - mn, mn, v1);
}



const int N = 233;

ld a[N][N];
ld ans[N];

// sum(a[i][j] * x_j) = a[i][n] para 0 <= i < n
void solve(int n) {
	for(int i = 0; i < n; i++) {
		int mx = i;
		for(int j = i + 1; j < n; j++)
			if(abs(a[j][i]) > abs(a[mx][i]))
				mx = j;
		swap_ranges(a[i], a[i] + n + 1, a[mx]);
		if(abs(a[i][i]) < 1e-6) /* sem solucao*/;
		for(int j = i + 1; j < n; j++) {
			for(int k = i + 1; k <= n; k++)
				a[j][k] -= (a[j][i] / a[i][i]) * a[i][k];
			a[j][i] = 0;
		}
	}
	for(int i = n - 1; i >= 0; i--) {
		ans[i] = a[i][n];
		for(int j = i + 1; j < n; j++)
			ans[i] -= a[i][j] * ans[j];
		ans[i] /= a[i][i];
	}
}

char s[100];

int main() {
	int i, j, k, l;
	scanf("%s", s);
	n = strlen(s);
	go(n, 1, vector<int>());
	an[1][0] = 0;
	for(i = 2; i <= n; i++) {
		//printf("i%d\n", i);
		for(j = 0; j < st[i].size(); j++) {
			vector<int> &v = st[i][j];
			for(k = 0; k <= st[i].size(); k++)
				a[j][k] = 0;
			a[j][j] = -1;
			a[j][st[i].size()] = -1;
			//printf("at guy %d\n", j);
			for(k = 0; k < v.size(); k++) {
				for(l = 0; l < v.size(); l++) {
					ld p;
					if(l == k) {
						if(v[k] == 1) continue;
						p = (ld(v[k]) / n) * (ld(v[k] - 1) / (n - 1));
					} else {
						p = (ld(v[k]) / n) * (ld(v[l]) / (n - 1));
					}
					vector<int> v2 = v;
					v2[k]++; v2[l]--;
					sort(v2.begin(), v2.end());
					if(v2.front() == 0) {
						swap(v2.front(), v2.back());
						v2.pop_back();
						sort(v2.begin(), v2.end());
						a[j][st[i].size()] -= an[v2.size()][pos[v2.size()][v2]] * p;
						continue;
					}
					int g = pos[v2.size()][v2];
					a[j][g] += p;
				}
			}
		}
		//printf("proc %d\n", i);
		solve(st[i].size());
		for(j = 0; j < st[i].size(); j++)
			an[i][j] = ans[j];
		//for(j = 0; j < st[i].size(); j++) {
		//	for(k = 0; k < st[i][j].size(); k++)
		//		printf("%d + ", st[i][j][k]);
		//	printf("0 = %.10f\n", ans[j]);
		//}
	}
	map<char, int> tmp;
	for(i = 0; i < n; i++)
		tmp[s[i]]++;
	vector<int> c;
	for(auto e : tmp)
		c.pb(e.snd);
	sort(c.begin(), c.end());
	cout << setprecision(25) << an[c.size()][pos[c.size()][c]] << endl;

}
