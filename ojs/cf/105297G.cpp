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

const int N = 1009;

int n, a[N];

ll dp[N][N];

int main() {
    scanf("%d", &n);
    n += 1;
    for(int i = 1; i < n; i++)
        scanf("%d", &a[i]);
    for(int i = n - 1; i > 0; i--)
        for(int tel = 0; tel < i; tel++) {
            dp[i][tel] = min(dp[i + 1][tel] + abs(a[i] - a[i - 1]), dp[i + 1][i - 1] + abs(a[i] - a[tel]));
        }
    printf("%lld\n", dp[1][0]);
}