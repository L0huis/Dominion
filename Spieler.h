#pragma once

#include "Karten.h"

#include <algorithm>
#include <memory>
#include <random>
#include <vector>
struct Karte;

class Spieler
{
private:
	unsigned long long seed;

public:
	Spieler(std::vector<std::shared_ptr<Karte>> pDeck, unsigned int pSeed);
	~Spieler();

public:
	size_t nachziehstapel_groesse = 0;
	std::vector<std::shared_ptr<Karte>> deck;
	std::vector<std::shared_ptr<Karte>> hand;
	int geld = 0;
	int aktionen = 1;
	int kaeufe = 1;

public:
	bool ablegen(std::shared_ptr<Karte> karte);
	void nachziehen(const size_t anzahl);
	void aufraeumen();
	void fuellen();
	void mischen();
};