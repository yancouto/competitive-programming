#include <bits/stdc++.h>
using namespace std;
#define valx first
#define vali second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 11234;
const int M = 5123;

int n, m, w;
int p[N], pre[N];
int dp[N][3];
// mx[i][j] = max(dp[i - k][j] - pre[i - k]) for 0 <= k <= w-2
int mx[N][3];

int main() {
    scanf("%d %d %d", &n, &m, &w);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
        pre[i] = p[i] + pre[i - 1];
    }
    for(int mi = 0; mi <= m; mi++) {
        for(int i = 1; i <= n; i++) {
            int &d = dp[i][mi % 3];
            d = dp[i - 1][mi % 3];
            if (i >= w && mi > 0)
                d = max(d, dp[i - w][(mi - 1) % 3] + pre[i] - pre[i - w]);
            if (w > 1 && i > w && mi > 1)
                d = max(d, mx[i - w - 1][(mi - 2) % 3] + pre[i]);
        }
        if (w < 2 || mi >= m - 1) continue;
        // calculate mx
        deque<pii> dq;
        for(int i = 0; i <= n; i++) {
            int val = dp[i][mi % 3] - pre[i];
            while(!dq.empty() && dq.back().valx <= val) dq.pop_back();
            dq.pb(pii(val, i));
            while(dq.front().vali < i - (w - 2)) dq.pop_front();
            mx[i][mi % 3] = dq.front().valx;
        }
    }
    printf("%d\n", dp[n][m % 3]);
}