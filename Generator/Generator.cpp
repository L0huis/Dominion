
#include <iostream>
#include <random>
#include <string>
#include <iterator>
#include <algorithm>
#include <array>

using namespace std;

array<string, 25> aktionskarten{
	"G�rten",
	"Burggraben",
	"Kapelle",
	"Keller",
	"Dorf",
	"Holzf�ller",
	"Kanzler",
	"Werkstat",
	"B�rokrat",
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


int main()
{
	std::string in = "abcdefgh", out;
	std::sample(in.begin(), in.end(), std::back_inserter(out),
		5, std::mt19937{ std::random_device{}() });
	std::cout << "five random letters out of " << in << " : " << out << '\n';
}
