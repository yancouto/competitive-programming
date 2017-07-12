#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e5;

int t;
int n;
int ss, st[N];
ll x[N], r[N];
int bst[N][2];
int res[N][2];
int p[N];

int main () {
	cin >> t;

	while (t--) {
		cin >> n;

		for (int i = 0; i < n; i++) {
			cin >> x[i] >> r[i];
			p[i] = i;
		}

		sort(p, p+n, [] (int i, int j) {
			return r[i] > r[j];
		});

		bst[0][0] = 0;
		ss = 1;
		st[0] = 0;

		for (int i = 1; i < n; i++) {
			int lo = 0, hi = i;
			while (lo < hi) {
				int md = (lo+hi)/2;
				if (abs(x[i] - x[md]) > r[i])
					lo = md + 1;
				else
					hi = md;
			}
			bst[i][0] = lo;

			lo = 0, hi = ss;
			while (lo < hi) {
				int md = (lo+hi)/2;
				if (abs(x[i] - x[st[md]]) > r[i])
					lo = md + 1;
				else
					hi = md;
			}

			if (lo < ss)
				bst[i][0] = min(bst[i][0], bst[st[lo]][0]);

			while (ss && bst[st[ss-1]][0] >= bst[i][0])
				ss--;
			st[ss++] = i;
		}
		
		bst[n-1][1] = n-1;
		ss = 1;
		st[0] = n-1;
		for (int i = n-2; i >= 0; i--) {
			int lo = i, hi = n-1;
			while (lo < hi) {
				int md = (lo+hi+1)/2;
				if (abs(x[i] - x[md]) > r[i])
					hi = md - 1;
				else
					lo = md;
			}
			bst[i][1] = lo;

			lo = 0, hi = ss;
			while (lo < hi) {
				int md = (lo+hi)/2;
				if (abs(x[i] - x[st[md]]) > r[i])
					lo = md + 1;
				else
					hi = md;
			}

			if (lo < ss)
				bst[i][1] = max(bst[i][1], bst[st[lo]][1]);

			while (ss && bst[st[ss-1]][1] <= bst[i][1])
				ss--;

			st[ss++] = i;
		}

		set<int> s;
		for (int _i = 0; _i < n; _i++) {
			int i = p[_i];

			res[i][0] = bst[i][0];
			res[i][1] = bst[i][1];

			auto it = s.lower_bound(i);

			if (it != s.end() && res[i][1] >= *it) {
				res[i][0] = min(res[i][0], res[*it][0]);
				res[i][1] = max(res[i][1], res[*it][1]);
			}

			if (it != s.begin()) {
				--it;
				if (res[i][0] <= *it) {
					res[i][0] = min(res[i][0], res[*it][0]);
					res[i][1] = max(res[i][1], res[*it][1]);
				}
			}

			s.insert(i);
		}

		for (int i = 0; i < n; i++) {
			if (i)
				cout << " ";
			cout << res[i][1] - res[i][0] + 1;
		}
		cout << endl;
	}


}
