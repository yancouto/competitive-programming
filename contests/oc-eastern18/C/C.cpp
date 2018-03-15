#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

string s[4];

ll ans = 0;

int A[256][256], B[256][256], C[256][256];

void solve() {
	for(int d = -100; d <= 100; d++) {
		for(int i = 0; i < s[0].size(); i++) {
			if(i + d < 0 || i + d >= s[1].size()) continue;
			A[s[0][i]][s[1][i + d]]++;
		}
		for(int e = 2; e < 100; e++) {
			ll ra = 0, rb = 0;
			for(int j = 0; j + e < s[2].size(); j++) {
				ra += A[s[2][j]][s[2][j + e]];
				B[s[2][j]][s[2][j + e]]++;
			}
			for(int j = 0; j + e < s[3].size(); j++) {
				rb += A[s[3][j]][s[3][j + e]];
				C[s[3][j]][s[3][j + e]]++;
			}
			//if(ra || rb) printf("\nd %d e %d ra %lld rb %lld\n", d, e, ra, rb);
			ans += ra * rb;
			for(int i = 0; i < s[0].size(); i++) {
				if(i + d < 0 || i + d >= s[1].size()) continue;
				ans -= B[s[0][i]][s[1][i + d]] * C[s[0][i]][s[1][i + d]];
				//if(ra || rb) printf("[%d]-= %d * %d\n", i, B[s[0][i]][s[1][i + d]], C[s[0][i]][s[1][i + d]]);
				if(i + d + 1 >= s[1].size() || i + 1 >= s[0].size()) continue;
				ans -= B[s[0][i]][s[1][i + d]] * C[s[0][i + 1]][s[1][i + d + 1]];
				//if(ra || rb) printf("-= %d * %d\n", B[s[0][i + 1]][s[1][i + d + 1]], C[s[0][i + 1]][s[1][i + d + 1]]);
				ans -= C[s[0][i]][s[1][i + d]] * B[s[0][i + 1]][s[1][i + d + 1]];
				//if(ra || rb) printf("-= %d * %d\n", B[s[0][i + 1]][s[1][i + d + 1]], C[s[0][i + 1]][s[1][i + d + 1]]);
			}
			for(int j = 0; j + e < s[2].size(); j++)
				B[s[2][j]][s[2][j + e]]--;
			for(int j = 0; j + e < s[3].size(); j++)
				C[s[3][j]][s[3][j + e]]--;
		}
		for(int i = 0; i < s[0].size(); i++) {
			if(i + d < 0 || i + d >= s[1].size()) continue;
			A[s[0][i]][s[1][i + d]]--;
		}
	}
}

int main () {
	for(int i = 0; i < 4; i++)
		cin >> s[i];
	sort(s, s + 4);
	do {
		solve();
	} while(next_permutation(s, s + 4));
	printf("%lld\n", ans / 2);
}
