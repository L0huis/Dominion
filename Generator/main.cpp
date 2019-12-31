#include <iostream>
#include <random>
#include <string>
#include <iterator>
#include <algorithm>
#include <array>

using namespace std;

int main()
{
	array<string, 25> in{
		"Gärten",
		"Burggraben",
		"Kapelle",
		"Keller",
		"Dorf",
		"Holzfäller",
		"Kanzler",
		"Werkstat",
		"Bürokrat",
		"Dieb",
		"Festmahl",
		"Geldverleiher",
		"Miliz",
		"Schmiede",
		"Spion",
		"Thronsaal",
		"Umbau",
		"Bibliothek",
		"Hexe",
		"Jahrmarkt",
		"Laboratorium",
		"Markt",
		"Mine",
		"Ratsversammlung",
		"Abenteurer"
	};
	vector<string> out;


	sample(in.begin(), in.end(), back_inserter(out), 10, mt19937{ random_device{}() });
	for (size_t i = 0; i < 10; i++)
	{
		cout << out[i] << endl;
	}
}