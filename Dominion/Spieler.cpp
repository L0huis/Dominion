#include "Spieler.h"

Spieler::Spieler(std::vector<std::shared_ptr<Karte>> pDeck, unsigned int pSeed)
{
	deck = pDeck;
	seed = pSeed;
	mischen();
}

Spieler::~Spieler()
{
	hand.clear();
	deck.clear();
}

void Spieler::mischen()
{
	std::shuffle(deck.begin(), deck.end(), std::default_random_engine(++seed));
	nachziehstapel_groesse = deck.size();
}

void Spieler::nachziehen(const size_t anzahl)
{
	for (size_t i = 0; i < anzahl; i++)
	{
		if (deck.size() == 0)
			break;
		if (nachziehstapel_groesse <= 0)
			mischen();
		hand.push_back(deck.front());
		deck.erase(deck.begin());
		nachziehstapel_groesse--;
	}
}

bool Spieler::ablegen(std::shared_ptr<Karte> karte)
{
	if (karte)
	{
		deck.push_back(karte);
		return true;
	}
	return false;
}

void Spieler::aufraeumen()
{
	for (auto& karte : hand)
		deck.push_back(karte);

	hand.clear();
}

void Spieler::fuellen()
{
	geld = 0;
	aktionen = 1;
	kaeufe = 1;

	nachziehen(5);
}
