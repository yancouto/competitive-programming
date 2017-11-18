#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef pair<ll, ll> pii;

const int N = 112345;
string book[N];
int bn;
string sep = "---###---###---###---###---###---###---###---###---###---###---###---###---";

vector<string> pg[N];
vector<int> oc[N];
int pn;
int mp[256], boc[256];
int p[N], mrk[N];

int main() {
	int i, j, k;
	while(true) {
		getline(cin, book[bn++]);
		//printf("book line %d\n", bn);
		if(book[bn - 1] == sep) break;
	}
	int tn = 0;
	for(i = 0; i < 256; i++) mp[i] = -1;
	i = 0;
	for(char c : "eariotnslcudpmhgbfywkvxzjq") mp[c] = i++;
	int lc = i;
	while(tn < bn) {
		oc[pn].resize(lc, 0);
		while(tn < bn) {
			string x;
			getline(cin, x);
			if(x == sep) break;
			tn++;
			//printf("pg %d line total %d\n", pn, tn);
			pg[pn].pb(x);
		}
		for(i = 0; i < 30 && i < pg[pn].size(); i++)
			for(char c : pg[pn][i])
				if(mp[c] != -1)
					oc[pn][mp[c]]++;
		pn++;
	}
	pg[pn - 1].pop_back();

	int ii = 0;
	for(i = 0; i < bn - 2;) {
		int mn = INT_MAX, mi = -1;
		for(int k = 0; k < lc; k++) boc[k] = 0;
		for(int k = 0; k < 30 && i + k < bn; k++)
			for(char c : book[i + k])
				if(mp[c] != -1)
					boc[mp[c]]++;
		//printf("for i = %d -- %s\n", i, book[i].c_str());
		for(j = 0; j < pn; j++) {
			if(mrk[j]) continue;
			int sum = 0;
			for(k = 0; k < lc; k++)
				if(oc[j][k] > boc[k]) {
					//printf("pg %d (%d > %d) || (%d < %d - 15)\n", j, oc[j][k], boc[k], oc[j][k], boc[k]);
					break;
				} else {
					//printf("pg %d sum += (%d - %d)^2\n", j, boc[k], oc[j][k]);
					sum += (boc[k] - oc[j][k]) * (boc[k] - oc[j][k]);
				}
			//printf("pg %d ok = %d sum = %d\n", j, k == lc, sum);
			if(k == lc && sum < mn) {
				mn = sum;
				mi = j;
			}
		}
		assert(mi >= 0);
		//printf("mi = %d\n", mi);
		mrk[mi] = 1;
		p[mi] = ii++;
		i += pg[mi].size();
		//printf("size %d\n", pg[mi].size());
	}
	for(i = 0; i < pn; i++)
		printf("%d%c", p[i] + 1, " \n"[i == pn - 1]);
}
