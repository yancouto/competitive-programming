#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

map<string, int> bil;
int getbil(char *s) {
	string st(s);
	if(!bil.count(st)) bil[st] = bil.size() - 1; 
	return bil[st];
}


struct city {
	int i; ll d; int day;
	city(int a=0) : i(a), d(0), day(0) {}
	bool operator < (city o) const { return d < o.d; }
} cs[60009];
struct cmp_d {
	bool operator() (int i, int j) {
		if(cs[i].d == cs[j].d) return cs[i].i < cs[j].i;
		return cs[i].d < cs[j].d;
	}
};
struct cmp_i {
	bool operator() (int i, int j) {
		return cs[i].i < cs[j].i;
	}
};

set<int, cmp_d> rich;
set<int, cmp_i> ind;
map<string, int> cit;
int getcity(char *s) {
	string st(s);
	if(!cit.count(st)) {
		int i = cit.size();
		cit[st] = i;
		cs[i] = city(i);
		ind.insert(i);
		rich.insert(i);
	}
	return cit[st];
}
struct ev {
	int bil, cit;
	ev() {}
	ev(int a, int b) : bil(a), cit(b) {}
};
vector<ev> v[50009];
int mxmon() {
	if(cit.size() == 1) return 0;
	auto it2 = rich.rbegin(); auto it = it2++;
	if(cs[*it].d > cs[*it2].d) return *it;
	return -1;
}
map<int, int> bilcity;

char str1[100], str2[100];
ll mon[10009];
int main() {
	int i, x, n, m, k; ll d;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%s %s %lld", str1, str2, &d);
		int a = getbil(str1), b = getcity(str2);
		rich.erase(b); cs[b].d += d; rich.insert(b);
		bilcity[a] = b; mon[a] = d;
	}
	scanf("%d %d", &m, &k);
	for(i = 0; i < k; i++) {
		scanf("%d %s %s", &x, str1, str2);
		v[x].push_back(ev(getbil(str1), getcity(str2)));
	}
	for(i = 1; i <= m; i++) {
		int mx = mxmon();
		if(mx != -1) { cs[mx].day++; }
		for(ev e : v[i]) {
			int left = bilcity[e.bil];
			rich.erase(left);  cs[left].d -= mon[e.bil];  rich.insert(left);
			rich.erase(e.cit); cs[e.cit].d += mon[e.bil]; rich.insert(e.cit);
			bilcity[e.bil] = e.cit;
		}
	}
	for(auto &e : cit) {
		if(cs[e.second].day == 0) continue;
		printf("%s %d\n", e.first.c_str(), cs[e.second].day);
	}
	return 0;
}
