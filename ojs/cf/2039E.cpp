#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 998244353;
inline ll mod(ll x) { return x % modn; }

const int N = 1123456;

int n;

ll memo[1123456];
ll sum[1123456];

// Array already has two inversions, so all ways to add are kinda unique
ll solve(int actions) {
    // TODO: memoize
    if (actions == 0) return 1;
    ll &tot = memo[actions];
    if (tot != -1) return tot;
    tot = 1; // all equal values on the right
    // How many equal values on the right before adding another inversion(s)
    solve(actions - 1);
    tot = mod(tot + ll(n - actions) * sum[actions - 1]);

    // for(int i = 0; i < actions; i++)
        // tot = mod(tot + ll(n - actions) * solve(actions - i - 1));
    //printf("solve(%d) = %lld\n", actions, tot);
    sum[actions] = mod(sum[actions - 1] + tot);
    return tot;
}

// arr is 0000010 and adds 1s to the right 0+ times then a 1 on the left of the last 0
ll add_second_inversion(ll zeros_on_the_left, int actions) {
    // TODO: memoize
    ll tot = 1; // only 1s on the right
    solve(actions-1);
    tot = mod(tot + ll(zeros_on_the_left+1) * sum[actions - 1]);
    // for(int i = 0; i < actions; i++)
    //     tot = mod(tot + ll(zeros_on_the_left + 1) * solve(actions - i - 1));
    //printf("add_second_inversion(%lld, %d) = %lld\n", zeros_on_the_left, actions, tot);
    return tot;
}

// arr is 01 and I will add 0s on the left 0+ times then a 0 on the right
ll start(int actions) {
    ll tot = 1; // only 0s on the right
    for(int i = 0; i < actions; i++)
        tot = mod(tot + add_second_inversion(1 + i, actions - i - 1));
    //printf("start(%d) = %lld\n", actions, tot);
    return tot;
}

int main() {
    sum[0] = 1;
    for_tests(t, tt) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
            memo[i] = -1;
        printf("%lld\n", start(n - 2));
    }
}