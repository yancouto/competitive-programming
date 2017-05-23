#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const int N = 112345;
int x[N], y[N];
multiset<int> U, D;
deque<int> L, R;

void add(int i) {
	if(y[i] >= 0) U.insert(y[i]);
	else D.insert(-y[i]);
}

void rem(int i) {
	if(y[i] >= 0) U.erase(U.find(y[i]));
	else D.erase(D.find(-y[i]));
}

int any(int X) {
	deque<int> l = L, r = R;
	U.clear(); D.clear();
	for(int i : l) add(i);
	for(int s = 0; s <= X; s++) {
		while(!r.empty() && x[r.front()] <= X + s) { add(r.front()); r.pop_front(); }
		while(!l.empty() && x[l.back()] > X - s) { rem(l.back()); l.pop_back(); }
		if(!U.empty() && *U.begin() == 0) continue;
		if(U.empty() || D.empty()) return true;
		//if(s < 10) printf("%d/%d is %d and %d\n", s, X, *U.begin(), *D.begin());
		if((*U.begin() + *D.begin()) / 2 > X) return true;
	}
	return false;
}

bool ok(int X) {
	if(any(X)) return true;
	L.swap(R);
	return any(X);
}

int main() {
	int n, i, T = 0;
	while(scanf("%d", &n) != EOF && n != -1) {
		L.clear(); R.clear();
		for(i = 0; i < n; i++) {
			scanf("%d %d", &x[i], &y[i]);
			if(x[i] <= 0) L.pb(i);
			else R.pb(i);
			x[i] = abs(x[i]);
		}
		sort(L.begin(), L.end(), [](int i, int j) { return x[i] < x[j]; });
		sort(R.begin(), R.end(), [](int i, int j) { return x[i] < x[j]; });
		printf("Case %d: ", ++T);
		if(ok(2123456)) { puts("never"); continue; }
		int l = 0, r = 2123456;
		while(l < r) {
			int m = (l + r + 1) / 2;
			if(ok(m)) l = m;
			else r = m - 1;
		}
		printf("%d\n", l + 1);
	}
}
