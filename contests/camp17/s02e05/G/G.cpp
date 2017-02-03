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

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int i, j;
	cin >> n;
	while(n--) {
		string s;
		cin >> s;
		char a = s[s.size() - 2], b = s[s.size() - 1];
		if(b == 'x' || b == 's' || b == 'o' || (a == 'c' && b == 'h')) cout << s << "es\n";
		else if(b == 'f') cout << s.substr(0, s.size() - 1) << "ves\n";
		else if(a == 'f' && b == 'e') cout << s.substr(0, s.size() - 2) << "ves\n";
		else if(b == 'y') cout << s.substr(0, s.size() - 1) << "ies\n";
		else cout << s << "s\n";
	}
}
