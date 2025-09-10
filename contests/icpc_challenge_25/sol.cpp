#include <bits/stdc++.h>
using namespace std;
#define pb push_back

struct option {
  int w, h;
  double score;
  bool is66() { return w == 6 && h == 6; }
};

struct img {
  vector<option> opts;
  int oi66() {
    for(int oi = 0;; oi++)
      if(opts[oi].is66())
        return oi;
  }
  double val66() {
    return opts[oi66()].score;
  }
  int size() { return opts.size(); }
  void pb(option o) { opts.pb(o); }
};

struct group {
  vector<img> imgs;
  int size() { return imgs.size(); }
  void pb(img i) { imgs.pb(i); }
};

vector<group> all;

struct placement {
  int r, c;
  int gi, ii, oi;
  option& opt() { return all[gi].imgs[ii].opts[oi]; }
};

vector<placement> display;

using pii = pair<int, int>;
vector<int> HS = {4, 6, 9, 12};
vector<pii> L = {{6, 6}, {9, 9}, {12, 12}, {6, 12}, {12, 6}, {6, 18}, {18, 6}, {4, 12}, {12, 4}, {6, 4}, {4, 6}, {9, 6}, {6, 9}, {9, 12}, {12, 6}, {14, 6}};

int gn, k, optn, n;

struct group_subset {
  vector<int> subs;
  void pb(int x) { subs.pb(x); }
  int size() { return subs.size(); }
  bool empty() { return subs.empty(); }
};

vector<group_subset> cur;

struct state {
  int i, x, w;
  bool operator< (const state &o) const {
    return make_tuple(i, x, w) < make_tuple(o.i, o.x, o.w);
  }
};

struct dp {
  int gi, h;
  map<state, double> memo;
  map<state, int> chosen;
  set<int> ans;
  int r = 0, c = 0;
  double solve(int i, int x, int w) {
    if(w < 0) return -1./0.;
    if(x == 0) return w == 0? 0 : -1./0.;
    if(w == 0 || i < 0) return -1./0.;
    if(memo.count({i,x, w})) return memo[{i,x, w}];
    double &r = memo[{i,x, w}];
    r = solve(i - 1, x, w);
    chosen[{i, x, w}] = -1;
    for(int oi = 0; oi < all[gi].imgs[cur[gi].subs[i]].size(); oi++) {
      auto a = all[gi].imgs[cur[gi].subs[i]].opts[oi];
      if(a.h == h) {
        double nw = a.score + solve(i - 1, x - 1, w - a.w);
        if(nw > r) {
          r = nw;
          chosen[{i, x, w}] = oi;
        }
      }
    }
    return r;
  }
  
  void build(vector<placement> &my_display, int i, int x, int w) {
    if(x == 0) return;
    int oi = chosen[{i, x, w}];
    if(oi == -1) return build(my_display,  - 1, x, w);
    my_display.emplace_back(r, c, gi, cur[gi].subs[i], oi);
    ans.insert(cur[gi].subs[i]);
    auto a = all[gi].imgs[cur[gi].subs[i]].opts[oi];
    c += a.w;
    return build(my_display, i - 1, x - 1, w - a.w);
  }
};


bool guloso(vector<placement> &my_display, int gi, int x, int h) {
  dp mdp = {gi, h};
  if(mdp.solve(min(cur[gi].size() - 1, 10000), x, k) < 0) return false;
  //cout << "guloso ok gi " << gi << " h " << h << endl;
  mdp.build(my_display, min(cur[gi].size() - 1, 10000), x, k);
  for(int i = 0; i < cur[gi].subs.size(); i++)
    if(mdp.ans.count(cur[gi].subs[i])) {
      if(i != cur[gi].size() - 1) swap(cur[gi].subs[i], cur[gi].subs.back());
      cur[gi].subs.pop_back();
      i--;
    }
  return true;
}

pii get_remove_best_66(int gi) {
  int best = 0;
  for(int idx = 1; idx < cur[gi].subs.size(); idx++)
    if(all[gi].imgs[cur[gi].subs[idx]].val66() > all[gi].imgs[cur[gi].subs[best]].val66())
      best = idx;
  pii ans = {cur[gi].subs[best], all[gi].imgs[cur[gi].subs[best]].oi66()};
  cur[gi].subs.erase(cur[gi].subs.begin() + best);
  return ans;
}

vector<placement> just_do_it() {
  cur.clear();
  cur.resize(gn);
  for(int gi = 0; gi < gn; gi++) {
    cur[gi].subs.reserve(all[gi].size());
    for(int j = 0; j < all[gi].size(); j++)
      cur[gi].pb(j);
  }
  int r = 0;
  vector<placement> my_display;
  for(int gi = 0; gi < gn;) {
    if(cur[gi].empty()) {
      gi++;
      continue;
    }
    if(cur[gi].size() < k / 6) {
      // cout << "[case 1] gi " << gi << " size " << cur[gi].size() << endl;
      int c = 0;
      while(c < k) {
        auto [ii, oi] = get_remove_best_66(gi);
        my_display.emplace_back(r, c, gi, ii, oi);
        c += 6;
        if(cur[gi].empty()) gi++;
      }
    } else {
      // cout << "[case 2] gi " << gi << endl;
      vector<int> hhs = HS;
      random_shuffle(hhs.begin(), hhs.end());
      for(int h : hhs) {
        if(guloso(my_display, gi, k / 6, h)) {
          r += h;
          break;
        }
      }
    }
  }
  return my_display;
}

void output() {
  sort(display.begin(), display.end(), [](placement a, placement b) {
    if(a.gi != b.gi) return a.gi < b.gi;
    return a.ii < b.ii;
  });
  for(placement p : display)
    cout << (p.c+1) << ' ' << (p.r+1) << ' ' << all[p.gi].imgs[p.ii].opts[p.oi].w << ' ' << all[p.gi].imgs[p.ii].opts[p.oi].h << '\n';
}


int main() {
  srand(42);
  cin >> gn >> k;
  for(int i = 0; i < gn; i++) {
    cin >> n;
    group g;
    while(n--) {
      img i;
      cin >> optn;
      while(optn--) {
        option o;
        cin >> o.w >> o.h >> o.score;
        i.pb(o);
      }
      g.pb(i);
    }
    all.pb(g);
  }
  
/*
  int r = 0, c = 0;
  for(int gi = 0; gi < gn; gi++)
    for(int ii = 0; ii < all[gi].size(); ii++)
      for(int oi = 0; oi < all[gi].imgs[ii].size(); oi++) {
        c += 6;
        if(c == k) c = 0, r += 6;
        display.emplace_back(r, c, gi, ii, oi);
      }*/
     display = just_do_it();
  
      output();
}