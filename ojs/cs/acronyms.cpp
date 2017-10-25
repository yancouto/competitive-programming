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

int ct[256], mrk[256];
string s[1123456];

int main() {
	int i, n, j;
	ios::sync_with_stdio(false);
	cin >> n;
	for(i = 0; i < n; i++) {
		cin >> s[i];
		mrk[s[i][0]]++;
	}
	int ans = 0;
	for(i = 0; i < n; i++) {
		for(j = 'a'; j <= 'z'; j++)
			ct[j] = 0;
		for(char c : s[i])
			ct[c]++;
		mrk[s[i][0]]--;
		for(j = 'a'; j <= 'z'; j++)
			if(mrk[j] < ct[j])
				break;
		mrk[s[i][0]]++;
		if(j > 'z') ans++;
	}
	cout << ans << endl;
}
