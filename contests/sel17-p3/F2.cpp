#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back

const int N = 1123456;
int x[N], y[N], n;

deque<int> L, R;

void add(multiset<int> &U, multiset<int> &D, int i) {
	if(y[i] <= 0) D.insert(-y[i]);
	else U.insert(y[i]);
}
void rem(multiset<int> &U, multiset<int> &D, int i) {
	if(y[i] <= 0) D.erase(D.find(-y[i]));
	else U.erase(U.find(y[i]));
}

bool any(int X) {
	deque<int> l = L, r = R;
	multiset<int> U, D;
	for(int i : L)
		add(U, D, i);
	for(int s = 0; s <= X; s++) {
		while(!r.empty() && x[r.front()] <= X + s) add(U, D, r.front()), r.pop_front();
		while(!l.empty() && x[l.back()] > X - s) rem(U, D, l.back()), l.pop_back();
		if((!U.empty() && (*U.begin() == 0)) || (!D.empty() && (*D.begin() == 0))) continue;
		if(U.empty() || D.empty()) return true;
		//printf("%d + %d / 2 <= %d\n", *U.begin(), *D.begin(), X);
		if((*U.begin() + *D.begin() - 1 + 1) / 2 >= X) return true;
	}
	return false;
}

bool ok(int X) {
	if(any(X)) return true;
	L.swap(R);
	return any(X);
}

int main() {
	int t = 0, i;
	while(scanf("%d", &n) != EOF && n >= 0) {
		L.clear(); R.clear();
		for(i = 0; i < n; i++) {
			scanf("%d %d", &x[i], &y[i]);
			if(x[i] <= 0) L.pb(i);
			else R.pb(i);
			x[i] = abs(x[i]);
		}
		sort(R.begin(), R.end(), [](int i, int j) { return x[i] < x[j]; });
		sort(L.begin(), L.end(), [](int i, int j) { return x[i] < x[j]; });
		printf("Case %d: ", ++t);
		if(n <= 3 || ok(5000000)) { puts("never"); continue; }
		int l = 0, r = 5000000;
		while(l < r) {
			int m = (l + r + 1) / 2;
			if(ok(m)) l = m;
			else r = m - 1;
		}
		printf("%d\n", l);
	}
}
