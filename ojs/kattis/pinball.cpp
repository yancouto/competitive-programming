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

const int N = 112345;

#define y1 sddfsdf
#define y2 kjasdo
int x1[N], x2[N], y1[N], y2[N];
int p[N];

double at_y(int i, int x) {
	if(x1[i] == x2[i]) return y1[i];
	int dy = y2[i] - y1[i];
	double p = double(x - x1[i]) / (x2[i] - x1[i]);
	return y1[i] + dy * p;
}

int cur_x;

struct cmp {
	bool operator() (int i, int j) {
		return at_y(i, cur_x) < at_y(j, cur_x);
	}
};

struct ev {
	int x, i; bool add;
	bool operator < (ev o) const {
		if(o.x != x) return x < o.x;
		if(add) {
			if(!o.add) return true;
			return y1[i] < y1[o.i];
		} else {
			if(o.add) return false;
			return y2[i] > y2[o.i];
		}
	}
};

int main() {
	int i, n;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	vector<ev> evs;
	for(i = 0; i < n; i++) {
		cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
		if(x1[i] > x2[i]) {
			swap(x1[i], x2[i]);
			swap(y1[i], y2[i]);
		}
		evs.pb(ev{x1[i], i, true});
		evs.pb(ev{x2[i], i, false});
	}
	cin >> x1[i];
	x2[i] = x1[i] + 1;
	y1[i] = 10000000;
	y2[i] = 10000001;
	evs.pb(ev{x1[i], i, true});
	evs.pb(ev{x2[i], i, false});
	n++;
	set<int, cmp> s;
	sort(evs.begin(), evs.end());
	for(ev e : evs) {
		cur_x = e.x;
		if((e.add ^ (y2[e.i] > y1[e.i])) == 0) {
			auto it = s.lower_bound(e.i);
			if(it == s.begin()) p[e.i] = -1;
			else p[e.i] = *prev(it);
		}
		if(e.add)
			s.insert(e.i);
		else
			s.erase(e.i);
	}
	int x = x1[n - 1];
	i = n - 1;
	while(p[i] != -1) {
		i = p[i];
		if(y1[i] < y2[i]) x = x1[i];
		else x = x2[i];
	}
	cout << x << endl;
}
