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

struct module {
	int start;
	//vector<pair<string, int>> D;
	vector<string> E;
};

int data[112345];
int dn;
map<string, int> vars;
set<string> mult, all;
char s[11234];


int main() {
	int i, x, n; char c;
	int tt = 0;
	bool fst = true;
	while(true) {
		scanf(" %c", &c);
		if(c == '$') break;
		if(fst) fst = false;
		else putchar('\n');
		tt++;
		ungetc(c, stdin);
		vars.clear(); mult.clear(); all.clear();
		dn = 256;
		vector<module> mods;
		while(true) {
			scanf(" %c", &c);
			if(c == '$') break;
			ungetc(c, stdin);
			mods.pb(module());
			module &m = mods.back();
			m.start = dn;
			while(true) {
				scanf(" %c", &c);
				if(c == 'D') {
					scanf("%s %X", s, &x);
					all.insert(s);
					if(!vars.count(s)) vars[s] = x + m.start;
					else mult.insert(s);
				} else if(c == 'E') {
					scanf("%s", s);
					all.insert(s);
					m.E.pb(s);
				} else if(c == 'C') {
					scanf("%X", &n);
					for(i = 0; i < n; i++) {
						scanf(" %c", &c);
						if(c == '$') data[dn++] = -int(mods.size());
						else {
							ungetc(c, stdin);
							scanf("%X", &data[dn++]);
						}
					}
				} else break;
			}
		}
		int csum = 0;
		for(i = 256; i < dn; i++) {
			if(data[i] < 0) {
				int j = -data[i] - 1;
				string s = ((data[i + 1] >= int(mods[j].E.size()))? "-" : mods[j].E[data[i + 1]]);
				if(vars.count(s)) data[i] = (vars[s] >> 8), data[i + 1] = (vars[s] & 255);
				else data[i] = data[i + 1] = 0;
			}
			int b = (csum >> 15);
			csum = (((csum << 1) + data[i] + b) & ((1 << 16) - 1));
		}
		// answer case
		printf("Case %d: checksum = %04X\n", tt, csum);
		puts(" SYMBOL   ADDR");
		puts("--------  ----");
		for(string s : all) {
			printf("%s", s.c_str());
			for(i = s.size(); i < 10; i++) putchar(' ');
			if(vars.count(s)) {
				printf("%04X", vars[s]);
				if(mult.count(s)) printf(" M");
				putchar('\n');
			} else puts("????");
		}
	}

}
