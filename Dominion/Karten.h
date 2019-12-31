#pragma once

#include <string>
#include <vector>

#include "Spieler.h"
class Spieler;

enum class Karte_Typ
{
	AKTIONSKARTE,
	GELDKARTE,
	PUNKTEKARTE,
	GAERTEN,
	UNDEF
};

enum class Karten_ID
{
	KUPFER,
	SILBER,
	GOLD,
	ANWESEN,
	HERZOGTUM,
	PROVINZ,
	FLUCH,
	GAERTEN,
	BURGGRABEN,
	KAPELLE,
	KELLER,
	DORF,
	HOLZFAELLER,
	KANZLER,
	WERKSTATT,
	BUEROKRAT,
	DIEB,
	FESTMAHL,
	GELDVERLEIHER,
	MILIZ,
	SCHMIEDE,
	SPION,
	THRONSAAL,
	UMBAU,
	BIBLIOTHEK,
	HEXE,
	JAHRMARKT,
	LABORATORIUM,
	MARKT,
	MINE,
	RATSVERSAMMLUNG,
	ABENTEURER,
	SIZE
};

struct Karte
{
	Karten_ID id;
	int preis;
	Karte_Typ typ;

	Karte() : id(Karten_ID::SIZE), preis(-1), typ(Karte_Typ::UNDEF) { }
	Karte(Karten_ID _id, int _preis, Karte_Typ _typ) : id(_id), preis(_preis), typ(_typ) { }

	virtual std::string to_string() const;

	bool operator == (const Karte& rhs) const;
	bool operator == (const Karten_ID& rhs) const;
};

struct Geldkarte : public Karte
{
	int geld;

	Geldkarte() : Karte(), geld(0) { }
	Geldkarte(Karten_ID _id, int _preis, int _geld) : Karte(_id, _preis, Karte_Typ::GELDKARTE), geld(_geld) { }
};

struct Punktekarte : public Karte
{
	int punkte;

	Punktekarte() : Karte(), punkte(0) { }
	Punktekarte(Karten_ID _id, int _preis, int _punkte) : Karte(_id, _preis, Karte_Typ::PUNKTEKARTE), punkte(_punkte) { }
};

struct Aktionskarte : public Karte
{
	int karten;
	int aktionen;
	int kaeufe;
	int geld;

	Aktionskarte() : Karte(), karten(0), aktionen(0), kaeufe(0), geld(0) { }
	Aktionskarte(Karten_ID _id, int _preis, int _karten, int _aktionen, int _kaeufe, int _geld) : Karte(_id, _preis, Karte_Typ::AKTIONSKARTE), karten(_karten), aktionen(_aktionen), kaeufe(_kaeufe), geld(_geld) { }

	virtual void aktion(Spieler& ausspieler, std::vector<Spieler>& mitspieler);

	bool operator < (const Aktionskarte& rhs) const;
};

struct Gaerten : public Karte
{
	Gaerten() : Karte(Karten_ID::GAERTEN, 4, Karte_Typ::GAERTEN) { }
};

struct Kupfer : public Geldkarte
{
	Kupfer() : Geldkarte(Karten_ID::KUPFER, 0, 1) { }
};

struct Silber : public Geldkarte
{
	Silber() : Geldkarte(Karten_ID::SILBER, 3, 2) { }
};

struct Gold : public Geldkarte
{
	Gold() : Geldkarte(Karten_ID::GOLD, 6, 2) { }
};

struct Anwesen : public Punktekarte
{
	Anwesen() : Punktekarte(Karten_ID::ANWESEN, 2, 1) { }
};

struct Herzogtum : public Punktekarte
{
	Herzogtum() : Punktekarte(Karten_ID::HERZOGTUM, 5, 3) { }
};

struct Provinz : public Punktekarte
{
	Provinz() : Punktekarte(Karten_ID::PROVINZ, 8, 6) { }
};

struct Fluch : public Punktekarte
{
	Fluch() : Punktekarte(Karten_ID::FLUCH, 0, -1) { }
};

struct Burggraben : public Aktionskarte
{
	Burggraben() : Aktionskarte(Karten_ID::BURGGRABEN, 2, 2, 0, 0, 0) { }
};

struct Kapelle : public Aktionskarte
{
	Kapelle() : Aktionskarte(Karten_ID::KAPELLE, 2, 0, 0, 0, 0) { }
};

struct Keller : public Aktionskarte
{
	Keller() : Aktionskarte(Karten_ID::KELLER, 2, 0, 1, 0, 0) { }
};

struct Dorf : public Aktionskarte
{
	Dorf() : Aktionskarte(Karten_ID::DORF, 3, 1, 2, 0, 0) { }
};

struct Holzfaeller : public Aktionskarte
{
	Holzfaeller() : Aktionskarte(Karten_ID::HOLZFAELLER, 3, 0, 0, 1, 2) { }
};

struct Kanzler : public Aktionskarte
{
	Kanzler() : Aktionskarte(Karten_ID::KANZLER, 3, 0, 0, 0, 2) { }
};

struct Werkstatt : public Aktionskarte
{
	Werkstatt() : Aktionskarte(Karten_ID::WERKSTATT, 3, 0, 0, 0, 0) { }
};

struct Buerokrat : public Aktionskarte
{
	Buerokrat() : Aktionskarte(Karten_ID::BUEROKRAT, 4, 0, 0, 0, 0) { }
};

struct Dieb : public Aktionskarte
{
	Dieb() : Aktionskarte(Karten_ID::DIEB, 4, 0, 0, 0, 0) { }
};

struct Festmahl : public Aktionskarte
{
	Festmahl() : Aktionskarte(Karten_ID::FESTMAHL, 4, 0, 0, 0, 0) { }
};

struct Geldverleiher : public Aktionskarte
{
	Geldverleiher() : Aktionskarte(Karten_ID::GELDVERLEIHER, 4, 0, 0, 0, 0) { }
};

struct Miliz : public Aktionskarte
{
	Miliz() : Aktionskarte(Karten_ID::MILIZ, 4, 0, 0, 0, 2) { }
};

struct Schmiede : public Aktionskarte
{
	Schmiede() : Aktionskarte(Karten_ID::SCHMIEDE, 4, 3, 0, 0, 0) { }
};

struct Spion : public Aktionskarte
{
	Spion() : Aktionskarte(Karten_ID::SPION, 4, 1, 1, 0, 0) { }
};

struct Thronsaal : public Aktionskarte
{
	Thronsaal() : Aktionskarte(Karten_ID::THRONSAAL, 4, 0, 0, 0, 0) { }
};

struct Umbau : public Aktionskarte
{
	Umbau() : Aktionskarte(Karten_ID::UMBAU, 4, 0, 0, 0, 0) { }
};

struct Bibliothek : public Aktionskarte
{
	Bibliothek() : Aktionskarte(Karten_ID::BIBLIOTHEK, 5, 0, 0, 0, 0) { }
};

struct Hexe : public Aktionskarte
{
	Hexe() : Aktionskarte(Karten_ID::HEXE, 5, 2, 0, 0, 0) { }
};

struct Jahrmarkt : public Aktionskarte
{
	Jahrmarkt() : Aktionskarte(Karten_ID::JAHRMARKT, 5, 0, 2, 1, 2) { }
};

struct Laboratorium : public Aktionskarte
{
	Laboratorium() : Aktionskarte(Karten_ID::LABORATORIUM, 5, 2, 1, 0, 0) { }
};

struct Markt : public Aktionskarte
{
	Markt() : Aktionskarte(Karten_ID::MARKT, 5, 1, 1, 1, 1) { }
};

struct Mine : public Aktionskarte
{
	Mine() : Aktionskarte(Karten_ID::MINE, 5, 0, 0, 0, 0) { }
};

struct Ratsversammlung : public Aktionskarte
{
	Ratsversammlung() : Aktionskarte(Karten_ID::RATSVERSAMMLUNG, 5, 4, 0, 1, 0) { }
};

struct Abenteurer : public Aktionskarte
{
	Abenteurer() : Aktionskarte(Karten_ID::ABENTEURER, 6, 0, 0, 0, 0) { }
};