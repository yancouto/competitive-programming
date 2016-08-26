#include <cstdio>
#include <algorithm>
using namespace std;

struct uni {
	int S[100009], size[100009];
	int find(int i);
	int join(int a, int b);
} s1, s2;
int fib[100];
int fib_n;

int uni::find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

int uni::join(int a, int b) {
	if(a == b) return 0;
	if(size[a] < size[b]) swap(a, b);
	size[a] += size[b];
	S[b] = a;
	return 1;
}

void pre() {
	fib[0] = fib[1] = 1;
	int &i = fib_n;
	for(i = 2; ; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
		if(fib[i] > 100000) return;
	}
}

pair<int, int> es[100009];
int e_n;

int main() {
	int t, m, n, i, u, v, c;
	pre();
	scanf("%d", &t);
	for(int tt = 1; tt <= t; tt++) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++) {
			s1.S[i] = s2.S[i] = i;
			s1.size[i] = s2.size[i] = 1;
		}
		e_n = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &u, &v, &c); u--; v--;
			if(c == 0) s1.join(s1.find(u), s1.find(v));
			else es[e_n++] = make_pair(u, v);
		}
		int mw = -1, mxw = 0, mxw2 = 0;
		if(s1.size[s1.find(0)] == n) mw = 0; 
		for(i = 0; i < e_n; i++) {
			mxw2 += s1.join(s1.find(es[i].first), s1.find(es[i].second));
			mxw += s2.join(s2.find(es[i].first), s2.find(es[i].second));
			if(mw == -1 && s1.size[s1.find(0)] == n) mw = mxw2;
		}
		printf("Case #%d: ", tt);
		if(mw != -1 && *lower_bound(fib, fib + fib_n + 1, mw) <= mxw) puts("Yes");
		else puts("No");
	}
	return 0;
}