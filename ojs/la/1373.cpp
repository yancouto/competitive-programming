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
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

set<string> insig;
char str[200];
char s1[100][200];
char acr[200];

int solve1(int h, int ori);
int memo2[153][153][153];
int solve2(int h, int p, int ori) {
	if(ori < 0) return h == 0;
	if(p < 0) return solve1(h - 1, ori);
	int &r = memo2[h][p][ori];
	if(r != -1) return r;
	r = solve2(h, p - 1, ori);
	if(acr[ori] == s1[h][p]) r += solve2(h, p - 1, ori - 1);
	return r;
}

int memo1[153][153];
int solve1(int h, int ori) {
	if(ori < 0) return h < 0;
	if(h < 0) return 0;
	int &r = memo1[h][ori];
	if(r != -1) return r;
	r = 0;
	for(int i = strlen(s1[h]) - 1; i >= 0; i--)
		if(acr[ori] == s1[h][i])
			r += solve2(h, i - 1, ori - 1);
	return r;
}

int main() {
	int i, n;
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		insig.clear();
		for(i = 0; i < n; i++) {
			scanf("%s", str);
			insig.insert(str);
		}
		while(true) {
			scanf("%s ", acr); fgets(str, sizeof str, stdin);
			if(strcmp(acr, "LAST") == 0) break;
			printf("%s ", acr); memset(memo1, -1, sizeof memo1); memset(memo2, -1, sizeof memo2);
			for(i = 0; acr[i]; i++) acr[i] = tolower(acr[i]);
			int p = 0, i = 0;
			while(sscanf(str + p, "%s", s1[i]) == 1) {
				p += strlen(s1[i]) + 1;
				if(!insig.count(s1[i])) i++;
			}
			int sz = i;
			int r = solve1(sz - 1, strlen(acr) - 1);
			if(!r) printf("is not a valid abbreviation\n");
			else printf("can be formed in %d ways\n", r);
		}
	}
}
