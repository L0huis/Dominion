#pragma once

#include "Karten.h"
#include "Kartenstapel.h"
#include "Spieler.h"

#include <iostream>
#include <memory>
#include <random>
#include <vector>

#define DEBUG

struct Statistik
{
	double geld_auf_hand = 0;
	double geldkarten_auf_hand = 0;
	double punkte_auf_hand = 0;
	double punktekarten_auf_hand = 0;
	unsigned int anzahl_zuege = 0;
	unsigned int deck_groesse = 0;
	int geld_im_deck = 0;
	unsigned int geldkarten_im_deck = 0;
	int punkte_im_deck = 0;
	unsigned int punktekarten_im_deck = 0;
	unsigned int karten_im_deck[(int)Karten_ID::SIZE]{ 0 };
};

class Spiel
{
private:
	const size_t anzahl_spieler;

	// Geldkarten
	Stapel<Kupfer> kupfer;
	Stapel<Silber> silber;
	Stapel<Gold> gold;

	// Punktekarten
	Stapel<Anwesen> anwesen;
	Stapel<Herzogtum> herzogtum;
	Stapel<Provinz> provinz;
	Stapel<Fluch> fluch;

	Stapel<Gaerten> gaerten;

	// Aktionskarten
	// 2 Geld
	Stapel<Burggraben> burggraben;
	Stapel<Kapelle> kapelle;
	Stapel<Keller> keller;
	// 3 Geld
	Stapel<Dorf> dorf;
	Stapel<Holzfaeller> holzfaeller;
	Stapel<Kanzler> kanzler;
	Stapel<Werkstatt> werkstatt;
	// 4 Geld
	Stapel<Buerokrat> buerokrat;
	Stapel<Dieb> dieb;
	Stapel<Festmahl> festmahl;
	Stapel<Geldverleiher> geldverleiher;
	Stapel<Miliz> miliz;
	Stapel<Schmiede> schmiede;
	Stapel<Spion> spion;
	Stapel<Thronsaal> thronsaal;
	Stapel<Umbau> umbau;
	// 5 Geld
	Stapel<Bibliothek> bibliothek;
	Stapel<Hexe> hexe;
	Stapel<Jahrmarkt> jahrmarkt;
	Stapel<Laboratorium> laboratorium;
	Stapel<Markt> markt;
	Stapel<Mine> mine;
	Stapel<Ratsversammlung> ratsversammlung;
	// 6 Geld
	Stapel<Abenteurer> abenteurer;

	std::vector<Statistik> statistik;

	std::mt19937_64 engine;
	std::uniform_real_distribution<double> percent;
	std::discrete_distribution<unsigned int> cost2;
	std::discrete_distribution<unsigned int> cost3;
	std::discrete_distribution<unsigned int> cost4;
	std::discrete_distribution<unsigned int> cost5;

	std::vector<Spieler> mitspieler;

public:
	Spiel(size_t _anzahl_spieler = 2, unsigned long long seed = 0);

private:
	bool ist_spiel_vorbei() const;

public:
	void simulieren();

public:
	friend std::ostream& operator<<(std::ostream& os, const Spiel& spiel);
};
