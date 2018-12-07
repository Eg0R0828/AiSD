#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#define L_STD 16	// length standart for drowing;

using namespace std;

template <typename T>
class Atom {	// an element of the array;
public:
	Atom<T>::Atom(T atom, int lvl) {	// constructor;
		data = atom;
		level = lvl;
	}
	Atom<T>::~Atom() {	// destructor;
		data = NULL;
		level = 0;
	}
	// methods;
	void ChgLvl(int lvl) {
		level = lvl;
	}
	int GetLevel() {
		return level;
	}
	T GetData() {
		return data;
	}
private:
	T data;
	int level;
};

void push(char data, int level, vector <Atom <char>>& array) {
	Atom <char> element(data, level);
	array.push_back(element);
}

void PrintForest(vector <Atom <char>>& array) {
	cout << "Forest: ";
	int level = 0;
	for (int i = 0; i < array.size(); i++) {
		if (array[i].GetData() == '#') continue;
		level = array[i].GetLevel();
		cout << "(" << array[i].GetData();
		if ((i + 1) < array.size()) {
			if(array[i + 1].GetData() != '#') for (int lvl = array[i].GetLevel(); lvl >= array[i + 1].GetLevel(); lvl--)
				cout << ")";
			else if((i + 2) < array.size()) for (int lvl = array[i].GetLevel(); lvl >= array[i + 2].GetLevel(); lvl--)
				cout << ")";
		}
	}
	for (int lvl = level; lvl >= 0; lvl--) cout << ")";
	cout << endl << endl;
}

void DrawTree(vector <Atom <char>>& array, int length, int maxlvl) {
	string grid[100];	// a grid with elements for drawing;
	for (int i = 0; i < array.size(); i++) {
		grid[array[i].GetLevel()] += array[i].GetData();
		if ((i + 1) >= array.size() || ((i + 1) < array.size() && (array[i + 1].GetLevel() <= array[i].GetLevel())))
			for (int n = 1; n <= (maxlvl - array[i].GetLevel()); n++)
				for (int k = 0; k < pow(2, n); k++)
					grid[array[i].GetLevel() + n] += '#';
	}
	for (int lvl = 0; lvl <= maxlvl; lvl++, length /= 2){
		for (int n = 0; n < grid[lvl].size(); n++) {
			for (int j = 0; j < length; j++) cout << " ";
			if (!(maxlvl - lvl) || grid[lvl][n] == '#' || grid[lvl + 1][n * 2] == '#')
				for (int j = 0; j < length; j++) cout << " ";
			else for (int j = 0; j < length; j++) cout << "-"; 
			if (grid[lvl][n] != '#') cout << grid[lvl][n];
			else cout << " ";
			if (!(maxlvl - lvl) || grid[lvl][n] == '#' || grid[lvl + 1][n * 2 + 1] == '#')
				for (int j = 0; j < length; j++) cout << " ";
			else for (int j = 0; j < length; j++) cout << "-";
			for (int j = 0; j < length - 1; j++) cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	cout << "Please, enter the bin. tree:" << endl;	// initialization and entering the data;
	string str;
	int level = -1;
	int maxLevel = -1;
	getline(cin, str);
	if (str[0] == '\0') {	// checking an error;
		cout << "\nERROR: Empty line was entered!\n";
		return 0;
	}
	vector <Atom <char>> array;

	for (int i = 0; i < str.size(); i++) {	// reading the line; building the bin. tree;
		if (str[0] != '(') {	// checking an error;
			cout << "\nERROR: The symbol '(' was expected!\n";
			array.clear();
			return 0;
		}
		if (str[i] == '(') {
			level++;
			continue;
		}
		if (str[i] == ')') {
			level--;
			continue;
		}
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') continue;
		if (str[i] == '#') {
			push(str[i], level + 1, array);
			continue;
		}
		push(str[i], level, array);
		if (level > maxLevel) maxLevel = level;
		if (str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '(' && str[i + 1] != ')'
			&& str[i + 1] != '#' && str[i + 1] != '\n') {	// checking an error;
			cout << "\nERROR: The symbol ')' was expected!\n";
			array.clear();
			return 0;
		}
	}

	if (level != -1) {	// checking an errors;
		cout << "\nERROR: Numbers of '(' and ')' aren't equal!\n";
		array.clear();
		return 0;
	}
	if (array.size() == 0) {
		cout << "\nERROR: Empty tree was entered!\n";
		return 0;
	}

	cout << "Bin. tree:\n" << endl;
	DrawTree(array, (maxLevel + 1) * L_STD / 4, maxLevel);	// drawing the bin. tree;

	int n_arr = 0;	// a number of array element;
	level = -1, maxLevel = 0;
	cout << "Processing tree ..." << endl;
	for (int i = 0; i < str.size(); i++) {	// processing the line; building the forest;
		if (str[i] == '(') {
			level++;
			continue;
		}
		if (str[i] == ')') {
			if (str[i + 1] && str[i + 1] == '(') level -= 2;
			continue;
		}
		if (str[i] == ' ' || str[i] == '\n') continue;
		if (str[i] == '#') {
			level--;
			continue;
		}
		if (array[n_arr].GetData() == '#') n_arr++;
		cout << "New level of element '" << array[n_arr].GetData() << "': " << level << endl;
		array[n_arr++].ChgLvl(level);
		if (level > maxLevel) maxLevel = level;
	}
	cout << endl;
	PrintForest(array);	// printing a result;

	cout << "Horizontal detour of the forest: ";
	for (level = 0; level <= maxLevel; level++) {
		for (int i = 0; i < array.size(); i++)
			if (array[i].GetLevel() == level && array[i].GetData() != '#')
				cout << array[i].GetData();
	}
	cout << endl << endl;

    return 0;
}