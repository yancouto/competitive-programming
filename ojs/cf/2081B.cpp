#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1e9 + 7;
inline ll mod(ll x) { return x % modn; }

const int N = 212345;
int a[N];

struct seg {
    int mn, mx, sz;
};

int main() {
    int i, n;
    for_tests(t, tt) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) scanf("%d", &a[i]);
        vector<seg> all;
        seg cur = {a[0], a[0], 1};
        for(i = 1; i < n; i++) {
            if (a[i] > cur.mx) {
                cur.mx = a[i];
                cur.sz++;
            } else {
                all.pb(cur);
                cur = {a[i], a[i], 1};
            }
        }
        all.pb(cur);
        int tot = all.size() - 1;
        vector<seg> st;
        for(seg s : all) {
            st.pb(s);
            while(st.size() >= 3) {
                seg sl = st[st.size() - 3], sm = st[st.size() - 2], sr = st.back();
                for(i = 0; i < 3; i++) st.pop_back();
                if (sr.mn - sl.mx >= sm.sz) {
                    tot--;
                    st.pb(seg{sl.mn, sr.mx, sl.sz + sm.sz + sr.sz});
                } else if (st.size() >= 1 && (sl.mx > sm.mn)) {
                    tot--;
                    seg sll = st.back(); st.pop_back();
                    st.pb(seg{sll.mn, sll.mx + sl.sz, sll.sz + sl.sz});
                    st.pb(seg{sr.mn - sm.sz, sr.mx, sm.sz + sr.sz});
                } else {
                    st.pb(sl); st.pb(sm); st.pb(sr); break;
                }
            }
        }
        printf("%d\n", tot);
    }
}