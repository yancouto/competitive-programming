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

const int N = 212345;
int a[N], o[N];

int main() {
	for_tests(tn, tt) {
		int i, n;
		scanf("%d", &n);
		map<int, vector<int>> oc;
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]), oc[a[i]].pb(i), o[i] = a[i];
		vector<int> fst, snd;
		for(auto e : oc) {
			fst.pb(e.snd.front());
			if(e.snd.size() == 2)
				snd.pb(e.snd.back());
		}
		if(snd.size() == 1) {
			if(a[snd.back()] == a[fst.back()] && fst.size() > 1) {
				swap(a[snd.back()], a[fst.size() - 2]);
				int x = fst.back();
				fst.pop_back();
				fst.pop_back();
				fst.pb(x);
			} else {
				swap(a[snd.back()], a[fst.back()]);
				snd.pop_back();
				fst.pop_back();
			}
		}
		if(fst.size() > 1) {
			int x = a[fst.front()];
			for(i = 0; i < int(fst.size()) - 1; i++)
				a[fst[i]] = a[fst[i + 1]];
			a[fst.back()] = x;
		}
		if(snd.size() > 1) {
			int x = a[snd.front()];
			for(i = 0; i < int(snd.size()) - 1; i++)
				a[snd[i]] = a[snd[i + 1]];
			a[snd.back()] = x;
		}
		int ct = 0;
		for(i = 0; i < n; i++) ct += (a[i] != o[i]);
		printf("%d\n", ct);
		for(i = 0; i < n; i++) printf("%d%c", a[i], " \n"[i == n - 1]);
	}
}
