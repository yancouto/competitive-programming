
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
#define mn first
#define tot second
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 212345;

int n, q;
int b[N], c[N];

pii seg[N << 2];

pii merge(pii a, pii b) {
    return pii(min(a.mn, b.mn + a.tot), a.tot + b.tot);
}

void build(int i, int l, int r) {
    if(l == r) {
        seg[i] = pii(b[l % n] - c[l % n], b[l % n] - c[l % n]);
        return;
    }
    int m = (l + r) / 2;
    build(2 * i, l, m);
    build(2 * i + 1, m + 1, r);
    seg[i] = merge(seg[2 * i], seg[2 * i + 1]);
}

void upd(int i, int l, int r, int p) {
    if(l == r) {
        seg[i] = pii(b[l % n] - c[l % n], b[l % n] - c[l % n]);
        return;
    }
    int m = (l + r) / 2;
    if(p <= m) upd(2 * i, l, m, p);
    else upd(2 * i + 1, m + 1, r, p);
    seg[i] = merge(seg[2 * i], seg[2 * i + 1]);
}

int look_for_mn_idx(int i, int l, int r, ll cur_health) {
    if(l == r) return l;
    int m = (l + r) / 2;
    if (cur_health + seg[2 * i].mn < 0) return look_for_mn_idx(2 * i, l, m, cur_health);
    else return look_for_mn_idx(2 * i + 1, m + 1, r, cur_health + seg[2 * i].tot);
}

// if neg, stopped there, otherwise, cur health
ll mx(int i, int l, int r, int ql, ll cur_health) {
    if(l >= ql) {
        if (seg[i].mn + cur_health < 0) {
            return -look_for_mn_idx(i, l, r, cur_health) - 1;
        } else return seg[i].tot + cur_health;
    }
    int m = (l + r) / 2;
    if (ql > m) return mx(2 * i + 1, m + 1, r, ql, cur_health);
    ll ans = mx(2 * i, l, m, ql, cur_health);
    if (ans < 0) return ans; // already found stopping place
    return mx(2 * i + 1, m + 1, r, ql, ans);
}


int main() {
    scanf("%d %d", &n, &q);
    for(int i = 0; i < n; i++) scanf("%d", &b[i]);
    for(int i = 0; i < n; i++) scanf("%d", &c[i]);
    build(1, 0, 2 * n - 1);
    while(q--) {
        int q2, i, x;
        scanf("%d %d", &q2, &i); i--;
        if(q2 == 1) {
            ll ans = mx(1, 0, 2 * n - 1, i, 0);
            if (ans < 0) printf("%lld\n", (-ans - 1) % n + 1);
            else puts("-1");
        } else {
            scanf("%d", &x);
            if(q2 == 2) b[i] = x;
            else c[i] = x;
            upd(1, 0, 2 * n - 1, i);
            upd(1, 0, 2 * n - 1, i + n);
        }
    }
}