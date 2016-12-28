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

const int N = 112345;
int a[N], tr[4 * N];
set<int> s[32];

void build(int i, int l, int r) {
    if(l == r) return (void) (tr[i] = a[l]);
    int m = (l + r) / 2;
    build(2 * i, l, m);
    build(2 * i + 1, m + 1, r);
    tr[i] = min(tr[2*i], tr[2*i + 1]);
}

int get(int i, int l, int r, int ql, int qr) {
    if(l > qr || r < ql) return INT_MAX;
    if(l >= ql && r <= qr) return tr[i];
    int m = (l + r) / 2;
    return min(get(2 * i, l, m, ql, qr), get(2 * i + 1, m + 1, r, ql, qr));
}

void sub(int i, int l, int r, int x, int v) {
    if(l == r) return (void) (tr[i] -= v);
    int m = (l + r) / 2;
    if(x <= m) sub(2 * i, l, m, x, v);
    else sub(2 * i + 1, m + 1, r, x, v);
    tr[i] = min(tr[2*i], tr[2*i + 1]);
}

int main() {
    int i, j, n, q, x, l, r, op;
    scanf("%d %d", &n, &q);
    for(i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        for(j = 0; (1 << j) <= a[i]; j++)
            if((1 << j) & a[i])
                s[j].insert(i);
    }
    build(1, 0, n - 1);
    for(i = 0; i < q; i++) {
        scanf("%d %d %d", &op, &l, &r); l--; r--;
        if(op == 0) printf("%d\n", get(1, 0, n - 1, l, r));
        else {
            scanf("%d", &x);
            for(j = 0; j < 30; j++)
                if(!(x & (1 << j))) {
                    auto il = s[j].lower_bound(l);
                    auto ir = s[j].upper_bound(r);
                    for(; il != ir; il = s[j].erase(il))
                        sub(1, 0, n - 1, *il, (1 << j));
                }
        }
    }
}
