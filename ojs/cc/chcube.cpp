#include <cstdio>
#include <string>
#include <map>
using namespace std;
map<string, int> color;
void pre_process() {
	int i = 0;
	for(auto &s : {"black", "blue", "red", "green", "yellow", "orange"})
		color[s] = i++;
}
int adj[6][6] = {
	{0, 0, 1, 1, 1, 1},
	{0, 0, 1, 1, 1, 1},
	{1, 1, 0, 0, 1, 1},
	{1, 1, 0, 0, 1, 1},
	{1, 1, 1, 1, 0, 0},
	{1, 1, 1, 1, 0, 0}
};

bool poss(int c[6]) {
	int i, j, k;
	for(i = 0; i < 6; i++)
		for(j = i + 1; j < 6; j++)
			for(k = j + 1; k < 6; k++)
				if(c[i] == c[j] && c[j] == c[k])
					if(adj[i][j] && adj[i][k] && adj[j][k])
						return true;
	return false;
}


int main() {
	int t, i;
	int c[6];
	char str[20];
	pre_process();
	scanf("%d", &t);
	while(t--) {
		for(i = 0; i < 6; i++) {
			scanf(" %s", str);
			c[i] = color[string(str)];
		}
		printf("%s\n", poss(c)? "YES" : "NO");
	}
	return 0;
}