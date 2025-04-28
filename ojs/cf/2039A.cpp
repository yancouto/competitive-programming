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


int main() {
    int n;
    for_tests(t, tt) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
            printf("%d ", i * 2 + 1);
        putchar('\n');
    }
}