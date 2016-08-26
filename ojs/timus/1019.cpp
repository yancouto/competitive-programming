#include <bits/stdc++.h>
using namespace std;
struct pt {
	pt() {}
	pt(int a, int b) : c(a), p(b) {}
	int c, p;
	bool operator < (pt o) const { return p > o.p; }
};
typedef pair<int, pt> pii;


pii ev[20000]; int pn;
map<int, int> mp;
int main() {
	int i, n, a, b; char c;
	scanf("%d", &n);
	ev[pn++] = pii(0, pt(0, 1));
	ev[pn++] = pii(1000000000, pt(0, -1));
	for(i = 2; i <= n + 1; i++) {
		scanf("%d %d %c", &a, &b, &c);
		int ind = (c == 'b');
		ev[pn++] = pii(a, pt(ind, i));
		ev[pn++] = pii(b, pt(ind, -i));
	}
	sort(ev, ev + pn);
	set<pt> cur;
	int last = 0; int bl = 0, br = -1;
	int lw = 0;
	cur.insert(pt(0, 1));
	for(i = 1; i < pn; i++) {
		int df = ev[i].first - lw;
		bool is_white = cur.begin()->c == 0;
		if(ev[i].second.p < 0) cur.erase(pt(ev[i].second.c, -ev[i].second.p));
		else cur.insert(ev[i].second);
		bool white = cur.begin()->c == 0;
		if(is_white) {
			if(df > br - bl + 1) {
				bl = lw;
				br = ev[i].first - 1;
			}
			if(!white) lw = 1000000009;
		} else {
			if(white) lw = ev[i].first;
		}
	}
	printf("%d %d\n", bl, br + 1);
	return 0;
}
