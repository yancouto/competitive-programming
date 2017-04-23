#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

string all[1123];

void check(int n) {
	string S;
	for(int i = 0; i < n; i++) S += all[i];
	for(int i = 0; i < int(S.size()); i++) {
		char c = S[(i + 1) % int(S.size())];
		if(S[i] == 'O') assert(c == 'B');
		if(S[i] == 'V') assert(c == 'Y');
		if(S[i] == 'G') assert(c == 'R');
		if(S[i] == 'B') assert(c != 'B' && c != 'V' && c != 'G');
		if(S[i] == 'Y') assert(c != 'Y' && c != 'O' && c != 'G');
		if(S[i] == 'R') assert(c != 'R' && c != 'V' && c != 'O');
	}
}

int main() {
	for_tests(tn, tt) {
		int n, r, o, y, g, b, v, i;
		scanf("%d %d %d %d %d %d %d", &n, &r, &o, &y, &g, &b, &v);
		printf("Case #%d: ", tt);
		// check cases with 0 byr and small cases
		if(y + b + v + o == 0 && r == g) { for(i = 0; i < n; i++) putchar("RG"[i & 1]); putchar('\n'); continue; }
		if(r + g + b + o == 0 && y == v) { for(i = 0; i < n; i++) putchar("YV"[i & 1]); putchar('\n'); continue; }
		if(r + g + y + v == 0 && b == o) { for(i = 0; i < n; i++) putchar("BO"[i & 1]); putchar('\n'); continue; }
		if((g && r < g + 1) || (v && y < v + 1) || (o && b < o + 1)) { puts("IMPOSSIBLE"); continue; }
		string sr = "R", sb = "B", sy = "Y";
		for(; g; g--) sr += "GR", r--, n -= 2;
		for(; v; v--) sy += "VY", y--, n -= 2;
		for(; o; o--) sb += "OB", b--, n -= 2;
		int mx = max(max(b, y), r);
		if(mx * 2 > b + y + r) { puts("IMPOSSIBLE"); continue; }
		string rest;
		int A, B;
		string sA, sB;
		if(b == mx) rest = "B", A = y, sA = "Y", B = r, sB = "R";
		else if(y == mx) rest = "Y", A = b, sA = "B", B = r, sB = "R";
		else rest = "R", A = b, sA = "B", B = y, sB = "Y";
		for(i = 0; i < mx; i++) all[2 * i] = rest;
		for(i = 0; i < mx - 1; i++) {
			if(A > B) all[2 * i + 1] = sA, A--;
			else all[2 * i + 1] = sB, B--;
		}
		if(A < B) swap(sA, sB);
		assert(abs(A - B) <= 1);
		for(i = 2 * mx - 1; i < n; i++) {
			all[i] = sA;
			swap(sA, sB);
		}
		for(i = 0; i < n && all[i] != "B"; i++);
		if(i < n) all[i] = sb;
		for(i = 0; i < n && all[i] != "Y"; i++);
		if(i < n) all[i] = sy;
		for(i = 0; i < n && all[i] != "R"; i++);
		if(i < n) all[i] = sr;
		for(i = 0; i < n; i++) printf("%s", all[i].c_str());
		check(n);
		putchar('\n');
	}
}
