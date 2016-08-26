#include <bits/stdc++.h>
using namespace std;

map<string, int> mp;
int get(char *s) {
	string st(s);
	if(!mp.count(st)) mp[st] = mp.size() - 1;
	return mp[st];
}

struct man {
	int p, q, ex;
	man() {}
	man(int pp, int qq, int exx) : p(pp), q(qq), ex(exx) {}
};
int q[4009];
int main() {
	int i, n, m, x;
	char str[50];
	scanf("%d", &m);
	for(i = 0; i < m; i++) {
		scanf("%d %*s %s", &x, str);
		int ind = get(str);
		q[ind] += x;
	}
	scanf("%d", &n);
	vector<man> qu;
	for(i = 0; i < n; i++) {
		scanf("%d %*s %s", &x, str);
		int ind = get(str);
		qu.push_back(man(ind, x, 0));
	}
	qu.push_back(man(-1, -1, -1));
	reverse(qu.begin(), qu.end());
	int tot = 0;
	while(true) {
		tot++;
		man ma = qu.back(); qu.pop_back();
		if(ma.p == -1) { tot--; break; }
		if(!q[ma.p]) continue;
		if(!ma.ex && q[ma.p] >= ma.q) { q[ma.p] -= ma.q; continue; }
		if((!ma.ex && q[ma.p] < ma.q) || (ma.ex && q[ma.p] != ma.ex)) {
			ma.ex = q[ma.p];
			if(!qu.empty()) swap(ma, qu.back());
			qu.push_back(ma);
			continue;
		}
		if(ma.ex && q[ma.p] == ma.ex) {
			q[ma.p] = 0;
			continue;
		}
		assert(false);
	}
	printf("%d\n", tot);
}
