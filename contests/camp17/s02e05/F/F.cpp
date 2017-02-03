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

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

const int N = 1e5+7;

int c[N], v[N], r[N];

struct node {
	int i;

	bool operator < (const node & ot) const {
		if (v[i] - i != v[ot.i] - ot.i) return v[i] - i < v[ot.i] - ot.i;
		if (c[i] != c[ot.i]) return c[i] < c[ot.i];
		return i < ot.i;
	};
};

int n;
map<int, node> mp;
set<node> s;

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);

	c[0] = -2;
	for (int i = 1; i <= n; i++)
		scanf("%d", &c[i]);
	c[n+1] = -2;
	n+=2;

	v[0] = 0;
	node att;
	att.i = 0;
	mp[-2] = att;
	s.insert(att);

	for (int i = 1; i < n; i++) {

		for (auto it : s) {
			if (abs(c[it.i] - c[i]) == 1) continue;
			v[i] = v[it.i] - it.i + i - 1;
			r[i] = it.i;
			break;
		}


		node at;
		at.i = i;

		if (mp.find(c[i]) == mp.end()) {
			mp[c[i]] = at;
		} else {
			s.erase(mp[c[i]]);
			mp[c[i]] = min(mp[c[i]], at);
		}
		s.insert(mp[c[i]]);
	}


	printf("%d\n", v[n-1]);
	int x = r[n-1];
	stack<int> st;
	while (x) {
		st.push(c[x]);
		x = r[x];
	}
	while (!st.empty()) {
		int x = st.top(); st.pop();
		printf("%d ", x);
	}
	printf("\n");
}
