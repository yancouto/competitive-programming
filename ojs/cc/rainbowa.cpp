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

int a[112345], A[112];

int main() {
	int i, n, t;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> t;
	while(t--) {
		cin >> n;
		for(i = 0; i < n; i++) cin >> a[i];
		i = 0; int j = 0;
		for(int k : {1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1}) {
			A[++j] = 0;
			while(i < n && a[i] == k) i++, A[j]++;
		}
		if(i != n) { puts("no"); continue; }
		for(i = 1; i <= 7; i++)
			if(A[i] == 0 || A[i] != A[7 + (7 - i)])
				break;
		if(i <= 7) puts("no");
		else puts("yes");
	}
}
