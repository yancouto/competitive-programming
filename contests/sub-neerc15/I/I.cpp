#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int N = 60;

int n;
char c;
int u;

struct node {
	int u, v;
	ll t;
	
	bool operator < (const node & ot) const {
		return t > ot.t;
	}
};

priority_queue<node> pq;
deque<int> qu;

vector<pair<int, ll> > res;

int pr[N];
int to[N];
int ch[N];
bool tr[N];
char sm[N];

int rel[300];

int main () {
	freopen("instruction.in", "r", stdin);
	freopen("instruction.out", "w", stdout);
	scanf("%d", &n);

	sm[0] = 'z'+1;
	for (int i = 1; i <= n; i++) {
		scanf(" %c %d", &c, &pr[i]);
		ch[pr[i]]++;
		sm[i] = 'z'+1;
		if (c == 'p') {
			scanf(" %c", &sm[i]);
			rel[sm[i]] = i;
			tr[i] = 1;
			qu.push_back(i);
		}
	}

	while (!qu.empty()) {
		int u = qu.front();
		qu.pop_front();

		if (!u) continue;

		if (to[pr[u]] == 0 || to[pr[u]] > u) {
			to[pr[u]] = u;
		}
		ch[pr[u]]--;
		if (!ch[pr[u]])
			qu.push_back(pr[u]);
	}

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		node curr;
		scanf("%lld", &curr.t);
		curr.v = 0;
		scanf(" %c", &c);
		curr.u = rel[c];

		pq.push(curr);
	}

	while (!pq.empty()) {
		node att = pq.top();
		pq.pop();
		int v = att.v;
		int u = att.u;

		while (pr[u] != v) u = pr[u];
		if (to[v] != u) {
			to[v] = u;
			res.push_back(make_pair(v, att.t));
		}
		if (tr[u]) continue;
		att.v = u;
		att.t++;
		pq.push(att);
	}

	printf("%d\n", int(res.size()));
	for (pair<int, ll> rr : res)
		printf("%d %lld\n", rr.first, rr.second);
}
