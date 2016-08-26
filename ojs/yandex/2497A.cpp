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

bool vowel(char c) {
	for(char C : "aeiouy") if(c == C) return true;
	return false;
}

const int N = 1123456;
char s[N], v[N], c[N];
int vn, cn;

int main() {
	scanf("%s", s);
	for(int i = 0; s[i]; i++)
		if(vowel(s[i])) v[vn++] = s[i];
		else c[cn++] = s[i];
	if(strcmp(v, c) > 0) printf("Vowel\n");
	else printf("Consonant\n");
}
