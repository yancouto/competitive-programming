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

const int N = 2e5+7;

int n;
int v[N];
multiset<pii> s;

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	rd(n);

	int j = 0;
	n -= 2;
	for (int i = 0; i < n; i++) {
		char c;

		scanf(" %c", &c);

		if (c == 'd') {
			scanf("%d", &v[i]);
			s.insert(pii(v[i], i));
		} else {
			scanf("%d", &v[i]);
			while (s.size() >= v[i])
				s.erase(s.begin());
			v[i] = -1;
		}
	}

	char cc;
	int val;
	scanf(" %c %d", &cc, &val);

	if (s.size() < val) {
		printf("-1\n");
	} else {
		ll res = 0;
		for (pii x : s)
			res += x.first;
		printf("%lld\n", res);
		printf("%d\n", int(s.size()));
		vector<int> rs;
		for (pii x : s)
			rs.push_back(x.second+2);
		sort(rs.begin(), rs.end());
		for (int x : rs)
			printf("%d ", x);
		printf("\n");
	}
}
