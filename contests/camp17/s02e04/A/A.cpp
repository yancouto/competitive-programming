#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

const int N = 5e7+7;
const int M = 1000;
char inp[N];
char * str;
int nw, st;
char field[20];
int ty[M];
vector<deque<string> > sorter[M];
string line[M];
int p[M];

vector<deque<string> > author;
string title, journal, publisher, pages;
string year, number, volume;
int pp;

void getpage (char * str) {
	char aux[300];
	sscanf(str, "%[0-9-]", aux);
	pages = aux;
	pp = 0;
	for (int i = 0; i < pages.size(); i++)
		if (pages[i] == '-')
			pp = 1;
}

void mount () {
	sorter[nw] = author;
	deque<string> auxdeq;
	while (auxdeq.size() < 11)
		auxdeq.push_back("");
	auxdeq.push_back(title);

	string vltmp = "";
	for (int i = volume.size(); i < 8; i++)
		vltmp += "0";
	vltmp += volume;
	auxdeq.push_back(vltmp);
	sorter[nw].push_back(auxdeq);
	p[nw] = nw;

	line[nw] = "";
	bool ok = 0;
	for (deque<string> aut : author) {
		if (ok) line[nw] += ", ";
		line[nw] += aut[0];
		for (int i = 1; i < aut.size(); i++) {
			line[nw] += string(" ");
			line[nw] += aut[i][0];
			line[nw] += string(".");
		}
		ok = 1;
	}

	if (!ty[nw]) {
		line[nw] += " ";
		line[nw] += title;
		line[nw] += " ";
		line[nw] += "// ";
		line[nw] += journal;
		if (volume != "") {
			line[nw] += ", ";
			line[nw] += volume;
		}
		if (number != "") {
			line[nw] += " (";
			line[nw] += number;
			line[nw] += ")";
		}
		line[nw] += " -- ";
		line[nw] += year;
		if (pp == 1) {
			line[nw] += " -- pp. ";
			line[nw] += pages;
		} else if (pp == 0) {
			line[nw] += " -- p. ";
			line[nw] += pages;
		}
	} else {
		line[nw] += " ";
		line[nw] += title;
		if (volume != "") {
			line[nw] += ", Vol. ";
			line[nw] += volume;
		}
		line[nw] += " -- ";
		line[nw] += publisher;
		line[nw] += ", ";
		line[nw] += year;
	}
	
	nw++;
	author.clear();
	title = journal = publisher = pages = "";
	year = number = volume = "";
	pp = -1;
}

int getinpos (char * str) {
	int k = 0;
	while (str[k] != '"') k++;
	return k+1;
}

void getaut (char * str) {
	char aux[300];
	deque<string> aut;
	string ls;
	bool ok = 0;

	while (str[0] != '"') {
		sscanf(str, " %[a-zA-Z]", aux);
		str += strlen(aux) + ok;
		ok = 1;
		if (strcmp(aux, "and") == 0) {
			aut.push_front(ls);
			author.push_back(aut);
			ls = "";
			aut.clear();
		} else {
			if (ls != "")
				aut.push_back(ls);
			ls = aux;
		}
	}
	aut.push_front(ls);
	author.push_back(aut);
	sort(author.begin(), author.end());
}

void getname (char * str, string & to) {
	char aux[300];
	int i = 0;
	for (i = 0; str[i] != '"'; i++)
		aux[i] = str[i];
	aux[i] = '\0';
	to = aux;
}

void getint (char * str, string & to) {
	char aux[300];
	int i = 0;
	for (i = 0; str[i] != '"'; i++)
		aux[i] = str[i];
	aux[i] = '\0';
	to = aux;
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("bibtex.in", "r", stdin);
	freopen("bibtex.out", "w", stdout);
#endif

	fread(inp, N, 1, stdin);
	year = number = volume = "";
	pp = -1;
	bool noread = 1;

	str = inp;

	while (noread) {
		noread = 0;

		while (isspace(str[0])) str++;
		if (!str[0]) continue;

		if (st == 0) {
			if (str[0] == '@') {
				ty[nw] = (str[1] == 'b');
				st = 1;
				while(!isspace(str[0])) str++;
				noread = 1;
			} else {
			}
		} else {
			if (str[0] == '{') {
				str++;
				noread = 1;
			} else if (str[0] == '}') {
				st = 0;
				mount();
				str++;
				noread = 1;
			} else {
				sscanf(str, " %s", field);
				int in = getinpos(str);
				if (ty[nw]) { // book
					if (field[0] == 'a')
						getaut(str+in);
					else if (field[0] == 't')
						getname(str+in, title);
					else if (field[0] == 'v')
						getint(str+in, volume);
					else if (field[0] == 'p')
						getname(str+in, publisher);
					else if (field[0] == 'y')
						getint(str+in, year);
				} else {
					if (field[0] == 'a')
						getaut(str+in);
					else if (field[0] == 't')
						getname(str+in, title);
					else if (field[0] == 'j')
						getname(str+in, journal);
					else if (field[0] == 'y')
						getint(str+in, year);
					else if (field[0] == 'v')
						getint(str+in, volume);
					else if (field[0] == 'n')
						getint(str+in, number);
					else if (field[0] == 'p')
						getpage(str+in);
				}
				int out = getinpos(str+in);
				str += in+out;
				while(isspace(*str)) str++;
				if(str[0] == ',') str++;
				noread = 1;
			}
		}
	}

	sort(p, p+nw, [] (int i, int j) {
		return sorter[i] < sorter[j];
	});

	for (int i = 0; i < nw; i++)
		printf("[%d] %s\n", i+1, line[p[i]].c_str());
}
