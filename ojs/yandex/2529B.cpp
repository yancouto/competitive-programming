#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

string pos[8] = {
	"923"
	"814"
	"765",

	"329"
	"418"
	"567",

	"789"
	"612"
	"543",

	"543"
	"612"
	"789",

	"765"
	"814"
	"923",

	"567"
	"418"
	"329",

	"345"
	"216"
	"987",

	"987"
	"216"
	"345"
};

char s[100];
int main() {
	int i, j;
	for(i = 0; i < 3; i++)
		scanf(" %s", s + 3*i);
	for(i = 0; i < 8; i++) {
		for(j = 0; j < 9 && (s[j] == '?' || s[j] == pos[i][j]); j++);
		if(j == 9) {
			for(j = 0; j < 9; j++) {
				putchar(pos[i][j]);
				if((j % 3) == 2) putchar('\n');
			}
			return 0;
		}
	}

}
