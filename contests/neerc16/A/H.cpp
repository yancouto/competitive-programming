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

int n;
char str[1123];
char s2[1123];

int all[112345];
int *acc = all + 50000;

inline bool dig(char c) { return isdigit(c) || c == '-'; }

int main() {
#ifdef ONLINE_JUDGE
	freopen("hard.in", "r", stdin);
	freopen("hard.out", "w", stdout);
#endif
	int i, j;
	while(true) {
		fgets(str, sizeof str, stdin);
		if(feof(stdin)) break;
		i = 0;
		while(!dig(str[i])) i++;
		if(strchr(str, '&')) {
			int a = atoi(str + i);
			while(dig(str[i])) i++;
			while(!dig(str[i])) i++;
			int b = atoi(str + i);
			if(a > b) continue;
			acc[a]++;
			acc[b + 1]--;
		} else {
			if(strchr(str, '<')) {
				acc[-32768]++;
				acc[atoi(str + i) + 1]--;
			} else {
				acc[atoi(str + i)]++;
				acc[32768]--;
			}
		}
	}
	vector<string> all;
	int cur = 0, fst = INT_MIN;
	for(i = -32768; i <= 32768; i++) {
		int nx = cur + acc[i];
		if(cur == 0 && nx > 0) {
			fst = i;
		} else if(cur > 0 && nx == 0) {
			if(fst == -32768 && i == 32768) {
				puts("true");
				return 0;
			}
			if(fst == -32768) sprintf(s2, "x <= %d", i - 1);
			else if(i == 32768) sprintf(s2, "x >= %d", fst);
			else sprintf(s2, "x >= %d && x <= %d", fst, i - 1);
			all.pb(string(s2));
		}
		cur = nx;
	}
	if(all.empty()) {
		puts("false");
	} else {
		for(i = 0; i < int(all.size()) - 1; i++)
			printf("%s ||\n", all[i].c_str());
		printf("%s\n", all.back().c_str());
	}
}
