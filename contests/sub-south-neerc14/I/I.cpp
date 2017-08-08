#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;

const int N = 1e4+7;

struct res {
	int a, b, c; ll vl;

	bool operator < (const res & ot) const {
		int t1 = a+b+c, t2 = ot.a+ot.b+ot.c;
		if (t1 != t2)
			return t1 < t2;
		return vl > ot.vl;
	}
};

ll n, a, b;
vector<pii> v[3];
ll acc[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> a >> b;
	for (int i = 0; i < n; i++) {
		int t, w;
		cin >> t >> w;
		t--;
		v[t].pb(pii(w,i+1));
	}

	for (int i = 0; i < 3; i++)
		sort(v[i].begin(), v[i].end());
	
	for (int i = 1; i <= v[2].size(); i++)
		acc[i] = acc[i-1] + v[2][i-1].first;

	res rs(res({0,0,0,0}));
	
	ll ca = 0, cb = 0, cc = 0;
	for (int qa = 0; qa <= min<int>(a,v[0].size()); qa++) {
		cb = cc = 0;
		for (int qb = 0; qb <= min<int>(b, v[1].size()); qb++) {
			int i = min<int>(v[2].size(), a-qa+b-qb);
			cc = acc[i];
			rs = max(rs, res({qa,qb,i,ca+cb+cc}));
			if (qb < v[1].size())
				cb += v[1][qb].first;
		}
		if (qa < v[0].size())
			ca += v[0][qa].first;
	}

	cout << rs.a + rs.b + rs.c << " " << rs.vl << endl;
	for (int i = 0; i < rs.a; i++)
		cout << v[0][i].second << " " << i+1 << endl;
	for (int i = 0; i < rs.b; i++)
		cout << v[1][i].second << " " << i+a+1 << endl;
	for (int i = rs.a; i < a && i - rs.a < rs.c; i++)
		cout << v[2][i-rs.a].second << " " << i+1 << endl;
	for (int i = rs.b; i < b && i - rs.b + (a-rs.a) < rs.c; i++)
		cout << v[2][i-rs.b+(a-rs.a)].second << " " << i+a+1 << endl;
}
