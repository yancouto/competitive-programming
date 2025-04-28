
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

char s[312345];

int main() {
    int i;
    for_tests(t, tt) {
        scanf("%s", s);
        int n = strlen(s);
        if (n == 1) { puts("-1"); continue; }
        if (s[0] == s[1]) { printf("%c%c\n", s[0], s[1]); continue; }
        for(i = 2; s[i]; i++) {
            if (s[i] == s[!(i&1)]) {
                printf("%c%c\n", s[i], s[i]);
                break;
            } else if (s[i] != s[i & 1]) {
                printf("%c%c%c\n", s[i-2], s[i-1], s[i]);
                break;
            }
        }
        if (!s[i]) puts("-1");
    }
}