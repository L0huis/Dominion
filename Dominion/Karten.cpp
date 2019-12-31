#include "Karten.h"

std::string Karte::to_string() const
{
	switch (id)
	{
	case Karten_ID::GAERTEN: return std::string("Gaerten");
	case Karten_ID::KUPFER: return std::string("Kupfer");
	case Karten_ID::SILBER: return std::string("Silber");
	case Karten_ID::GOLD: return std::string("Gold");
	case Karten_ID::ANWESEN: return std::string("Anwesen");
	case Karten_ID::HERZOGTUM: return std::string("Herzogtum");
	case Karten_ID::PROVINZ: return std::string("Provinz");
	case Karten_ID::FLUCH: return std::string("Fluch");
	case Karten_ID::BURGGRABEN: return std::string("Burggraben");
	case Karten_ID::KAPELLE: return std::string("Kapelle");
	case Karten_ID::KELLER: return std::string("Keller");
	case Karten_ID::DORF: return std::string("Dorf");
	case Karten_ID::HOLZFAELLER: return std::string("Holzfaeller");
	case Karten_ID::KANZLER: return std::string("Kanzler");
	case Karten_ID::WERKSTATT: return std::string("Werkstatt");
	case Karten_ID::BUEROKRAT: return std::string("Buerokrat");
	case Karten_ID::DIEB: return std::string("Dieb");
	case Karten_ID::FESTMAHL: return std::string("Festmahl");
	case Karten_ID::GELDVERLEIHER: return std::string("Geldverleiher");
	case Karten_ID::MILIZ: return std::string("Miliz");
	case Karten_ID::SCHMIEDE: return std::string("Schmiede");
	case Karten_ID::SPION: return std::string("Spion");
	case Karten_ID::THRONSAAL: return std::string("Thronsaal");
	case Karten_ID::UMBAU: return std::string("Umbau");
	case Karten_ID::BIBLIOTHEK: return std::string("Bibliothek");
	case Karten_ID::HEXE: return std::string("Hexe");
	case Karten_ID::JAHRMARKT: return std::string("Jahrmarkt");
	case Karten_ID::LABORATORIUM: return std::string("Laboratorium");
	case Karten_ID::MARKT: return std::string("Markt");
	case Karten_ID::MINE: return std::string("Mine");
	case Karten_ID::RATSVERSAMMLUNG: return std::string("Ratsversammlung");
	case Karten_ID::ABENTEURER: return std::string("Abenteurer");
	default: return std::string("Undef");
	}
}

bool Karte::operator==(const Karte& rhs) const
{
	return id == rhs.id;
}

bool Karte::operator==(const Karten_ID& rhs) const
{
	return id == rhs;
}

void Aktionskarte::aktion(Spieler& ausspieler, std::vector<Spieler>& mitspieler)
{
	ausspieler.nachziehen(karten);
	ausspieler.aktionen += aktionen;
	ausspieler.kaeufe += kaeufe;
	ausspieler.geld += geld;
}

bool Aktionskarte::operator < (const Aktionskarte& rhs) const
{
	if (karten != rhs.karten)
		return karten < rhs.karten;
	else if (geld != rhs.geld)
		return geld < rhs.geld;
	else if (kaeufe != rhs.kaeufe)
		return kaeufe < rhs.kaeufe;
	else if (aktionen != rhs.aktionen)
		return aktionen < rhs.aktionen;
	else
		return preis < rhs.preis;
}