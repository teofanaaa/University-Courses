#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<utility>
#include<string>
#include<queue>
using namespace std;
ifstream f;
ofstream g;
typedef struct Nod{
	char caracter;
	int frecventa;
	Nod *left, *right;
	Nod(char data, int frecv) {
		this->caracter = data;
		this->frecventa = frecv;
		this->left = NULL;
		this->right = NULL;
	}
};

int cauta(vector <pair<char, int>>& varf, char c) {
	for (int i = 0; i < varf.size(); i++)
		if (varf[i].first == c)
			return i;
	return -1;
}


void citire(vector <pair<char, int>>& varf) {
	f.open("input.txt");
	int dim,poz;
	char c;
	string line;
	while (!f.eof()) {
		getline(f,line);
		while (!line.empty()) {
			c = line[0];
			if (cauta(varf, c) == -1) varf.push_back(make_pair(c, 1));
			else {
				poz = cauta(varf, c);
				dim = varf[poz].second;
				dim += 1;
				varf.erase(varf.begin() + poz);
				varf.push_back(make_pair(c, dim));
			}
			line.erase(line.begin());
		}
	}
	f.close();
}

struct compare {
	bool operator()(Nod* l, Nod*r) {
		return l->frecventa > r->frecventa;
	}
};

priority_queue<Nod*, vector<Nod*>, compare> Huffman(vector <pair<char, int>>& varf) {
	priority_queue<Nod*, vector<Nod*>, compare> coada;
	Nod* left, *right,*top;
	for (int i = 0; i < varf.size(); i++)
		coada.push(new Nod(varf[i].first, varf[i].second));
	while (coada.size() !=1 ) {
		left = coada.top();
		coada.pop();
		right = coada.top();
		coada.pop();
		top = new Nod('^', left->frecventa + right->frecventa);
		top->left = left;
		top->right = right;
		coada.push(top);
	}
	return coada;
}

void printCod(vector<pair<char, string>>& cod, Nod* root, string str) {
	if (root == NULL)
		return;
	if (root->caracter != '^') {
		cout << root->caracter << ": " << str << endl;
		cod.push_back(make_pair(root->caracter, str));
	}
	printCod(cod, root->left, str + "0");
	printCod(cod, root->right, str + "1");
}

void afisareInFisier(vector<pair<char, string>> cod) {
	f.open("input.txt");
	g.open("output.txt");
	string line;
	char c;
	while (!f.eof()) {
		getline(f, line);
		while (line.size()!=0) {
			c = line[0];
			auto it = find_if(cod.begin(), cod.end(), [&c](pair<char, string> arg) {return arg.first == c; });
			g << (*it).second;
			line.erase(line.begin());
		}
	}

	f.close();
	g.close();


}

int main()
{
	vector <pair<char, int>> varf;
	vector<pair<char, string>> cod;
	citire(varf);
	Nod *root;
	priority_queue<Nod*, vector<Nod*>, compare> q;
	q=Huffman(varf);
	root = q.top();
	printCod(cod, root, "");
	afisareInFisier(cod);
    return 0;
}

