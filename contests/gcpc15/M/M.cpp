#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define fst first
#define snd second

const int N = 1e5+8;

int n, a[N], k;
int qr[N];
vector<pii> v[30];

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);

	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		scanf("%d", &qr[i]);
		v[0].pb(pii(qr[i],qr[i]));
	}
	sort(v[0].begin(), v[0].end());

	for (int lvl = 0; lvl; lvl++) {
		for (int i = 0; i < v[lvl].size(); i++) {
			if (!v[lvl+1].empty() && 
		}

		for (pii x : v[0]) {
			v[lvl+1].pb(x);
		}
	}
}
