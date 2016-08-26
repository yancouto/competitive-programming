#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
#ifndef ONLINE_JUDGE
#	define debug(args...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");}
#else
#	define debug(args...) {}
#endif
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int c;

struct city {
	int coin[20], comp;
	int country, owe[20];
	int i, j;
	bool complete();
	void addcoin(int, int);
} g[13][13];

bool city::complete() {
	return comp == c;
}
void city::addcoin(int country, int qt) {
	if(!qt) return;
	if(coin[country] == 0) comp++;
	coin[country] += qt;
}
map<string, int> mp;
char names[22][27];
vector<city*> cs[23];
int complete[23];
int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool valid(int i, int j) { return i >= 0 && j >= 0 && g[i][j].comp; }

int css[23];
bool cmp(int i, int j) { return strcmp(names[i], names[j]) < 0; }

void simulate() {
	int i, j, k, com = 0;
	for(int t = 1; com < c; t++) {
		for(i = 0; i < c; i++)
			for(city *cc : cs[i]) {
				for(k = 0; k < c; k++) {
					int q = cc->coin[k] / 1000;
					if(!q) continue;
					//printf("%s  giving %d (%s)\n", names[i], q, names[k]);
					for(j = 0; j < 4; j++)
						if(valid(cc->i + d[j][0], cc->j + d[j][1])) {
							g[cc->i + d[j][0]][cc->j + d[j][1]].owe[k] += q;
							cc->coin[k] -= q;							 
						}
				}
			}
		for(i = 0; i < c; i++) {
			bool all = true;
			for(city *cc : cs[css[i]]) {
				 for(j = 0; j < c; j++) {
					  cc->addcoin(j, cc->owe[j]);
					  cc->owe[j] = 0;
					  //if(i == 0)
					  //    printf("[%d] [%d,%d] %s has %d (%s)\n", t, cc->i, cc->j, names[css[i]], cc->coin[j], names[j]);
				 }
				 //if(i == 0) puts("---------------------------------------");
				 if(!cc->complete()) all = false;
			}
			if(all && !complete[css[i]]) {
				 complete[css[i]] = 1;
				 com++;
				 printf("   %s   %d\n", names[css[i]], t);
			}
		}
	}
}

int main() {
	int i, j, k, x1, x2, y1, y2, t = 0;
	while(true) {
		scanf("%d", &c);
		if(!c) return 0;
		mp.clear();
		memset(g, 0, sizeof g);
		for(i = 0; i < c; i++) {
			scanf(" %s %d %d %d %d", names[i], &x1, &y1, &x2, &y2);
			cs[i].clear(); complete[i] = 0;
			string name(names[i]);
			mp[name] = i; css[i] = i;
			for(j = x1; j <= x2; j++)
				for(k = y1; k <= y2; k++) {
					city &gg = g[j][k];
					gg.country = i;
					gg.coin[i] = 1000000;
					gg.comp = 1;
					gg.i = j; gg.j = k;
					cs[i].pb(&gg);
				}
		}
		sort(css, css + c, cmp);
		printf("Case Number %d\n", ++t);
		if(c == 1) {
			printf("   %s   0\n", names[0]);
			continue;
		}
		simulate();
	}
}
