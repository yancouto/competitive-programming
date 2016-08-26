#include <bits/stdc++.h>
using namespace std;
#define pb push_back

map<string, int> mp;
int get(string s) {
	if(!mp.count(s)) mp[s] = mp.size() - 1;
	return mp[s];
}

vector<int> adj[504];
char s1[50], s2[50], s3[50];
int dist[505];

int main() {
	int i, n;
	cin >> n;
	for(i = 0; i < n; i++) {
		cin >> s1 >> s2 >> s3;
		int i1 = get(s1), i2 = get(s2), i3 = get(s3);
		adj[i1].pb(i2); adj[i1].pb(i3);
		adj[i2].pb(i1); adj[i2].pb(i3);
		adj[i3].pb(i1); adj[i3].pb(i2);
	}
	queue<int> q;
	memset(dist, -1, sizeof dist);
	bool isa = mp.count("Isenbaev");
	int u = get("Isenbaev");
	q.push(u);
	dist[u] = 0;
	while(!q.empty()) {
		u = q.front(); q.pop();
		for(int v : adj[u])
			if(dist[v] == -1) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
	}
	for(auto &e : mp) {
		if(!isa && e.first == "Isenbaev") continue;
		cout << e.first << " ";
		if(dist[e.second] != -1)
			cout << dist[e.second] << '\n';
		else
			cout << "undefined\n";
	}
}
