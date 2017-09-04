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

int ocA[256], ocB[256];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int i, t;
	cin >> t;
	while(t--) {
		string s, t;
		cin >> s >> t;
		for(i = 0; i < 26; i++) ocA[i] = ocB[i] = 0;
		for(char c : s) ocA[c - 'a']++;
		for(char c : t) ocB[c - 'a']++;
		bool any = false, good = false;
		for(i = 0; i < 26; i++)
			if(ocA[i] > 0 && ocB[i] == 0)
				any = true, good = good || (ocA[i] > 1);
		if(good) { cout << "A\n"; continue; }
		if(!any) { cout << "B\n"; continue; }
		any = false;
		for(i = 0; i < 26; i++)
			if(ocB[i] > 0 && ocA[i] == 0)
				any = true;
		if(any) cout << "B\n";
		else cout << "A\n";
	}
}
