#include "Spiel.h"

Spiel::Spiel(size_t _anzahl_spieler, unsigned long long seed) : anzahl_spieler(_anzahl_spieler)
{
	kupfer = Stapel<Kupfer>(60 + 7);
	silber = Stapel<Silber>(40);
	gold = Stapel<Gold>(30);
	anwesen = Stapel<Anwesen>((size_t)(anzahl_spieler <= 2 ? 8 : 12) + 3);
	herzogtum = Stapel<Herzogtum>(anzahl_spieler <= 2 ? 8 : 12);
	provinz = Stapel<Provinz>(anzahl_spieler <= 2 ? 8 : 12);
	fluch = Stapel<Fluch>((anzahl_spieler - 1) * 10);
	gaerten = Stapel<Gaerten>(10);
	burggraben = Stapel<Burggraben>(10);
	kapelle = Stapel<Kapelle>(10);
	keller = Stapel<Keller>(10);
	dorf = Stapel<Dorf>(10);
	holzfaeller = Stapel<Holzfaeller>(10);
	kanzler = Stapel<Kanzler>(10);
	werkstatt = Stapel<Werkstatt>(10);
	buerokrat = Stapel<Buerokrat>(10);
	dieb = Stapel<Dieb>(10);
	festmahl = Stapel<Festmahl>(10);
	geldverleiher = Stapel<Geldverleiher>(10);
	miliz = Stapel<Miliz>(10);
	schmiede = Stapel<Schmiede>(10);
	spion = Stapel<Spion>(10);
	thronsaal = Stapel<Thronsaal>(10);
	umbau = Stapel<Umbau>(10);
	bibliothek = Stapel<Bibliothek>(10);
	hexe = Stapel<Hexe>(10);
	jahrmarkt = Stapel<Jahrmarkt>(10);
	laboratorium = Stapel<Laboratorium>(10);
	markt = Stapel<Markt>(10);
	mine = Stapel<Mine>(10);
	ratsversammlung = Stapel<Ratsversammlung>(10);
	abenteurer = Stapel<Abenteurer>(10);

	statistik = std::vector<Statistik>(anzahl_spieler);

	engine = std::mt19937_64(seed);
	percent = std::uniform_real_distribution<double>(0, 1);
	cost2 = std::discrete_distribution<unsigned int>({ 1, 1 });
	cost3 = std::discrete_distribution<unsigned int>({ 3, 1, 1, 1 });
	cost4 = std::discrete_distribution<unsigned int>({ 1, 1 });
	cost5 = std::discrete_distribution<unsigned int>({ 1, 1, 1, 1, 1 });

	mitspieler.reserve(anzahl_spieler);
	std::vector<std::shared_ptr<Karte>> start_deck {
		kupfer.karte_ziehen(),
		kupfer.karte_ziehen(),
		kupfer.karte_ziehen(),
		kupfer.karte_ziehen(),
		kupfer.karte_ziehen(),
		kupfer.karte_ziehen(),
		kupfer.karte_ziehen(),
		anwesen.karte_ziehen(),
		anwesen.karte_ziehen(),
		anwesen.karte_ziehen()
	};
	for (size_t i = 0; i < anzahl_spieler; i++)
	{
		mitspieler.push_back(Spieler(start_deck, i));
	}
}

bool Spiel::ist_spiel_vorbei() const
{
	int leere_stapel = 0;
	if (burggraben.ist_leer()) leere_stapel++;
	if (kapelle.ist_leer()) leere_stapel++;
	if (keller.ist_leer()) leere_stapel++;
	if (dorf.ist_leer()) leere_stapel++;
	if (holzfaeller.ist_leer()) leere_stapel++;
	if (kanzler.ist_leer()) leere_stapel++;
	if (werkstatt.ist_leer()) leere_stapel++;
	if (buerokrat.ist_leer()) leere_stapel++;
	if (dieb.ist_leer()) leere_stapel++;
	if (festmahl.ist_leer()) leere_stapel++;
	if (geldverleiher.ist_leer()) leere_stapel++;
	if (miliz.ist_leer()) leere_stapel++;
	if (schmiede.ist_leer()) leere_stapel++;
	if (spion.ist_leer()) leere_stapel++;
	if (thronsaal.ist_leer()) leere_stapel++;
	if (umbau.ist_leer()) leere_stapel++;
	if (bibliothek.ist_leer()) leere_stapel++;
	if (hexe.ist_leer()) leere_stapel++;
	if (jahrmarkt.ist_leer()) leere_stapel++;
	if (laboratorium.ist_leer()) leere_stapel++;
	if (markt.ist_leer()) leere_stapel++;
	if (mine.ist_leer()) leere_stapel++;
	if (ratsversammlung.ist_leer()) leere_stapel++;
	if (abenteurer.ist_leer()) leere_stapel++;
	return provinz.ist_leer() || leere_stapel >= 3;
}

void Spiel::simulieren()
{
	for (unsigned int zug_nummer = 1; !ist_spiel_vorbei(); zug_nummer++)
	{
		for (unsigned int spieler_nummer = 0; spieler_nummer < anzahl_spieler; spieler_nummer++)
		{
			Spieler& spieler = mitspieler[spieler_nummer];
			statistik[spieler_nummer].anzahl_zuege++;
		#ifdef DEBUG
			std::cout << "Zug: " << zug_nummer << " Spieler: " << spieler_nummer + 1 << '\n';
		#endif

			spieler.fuellen();

		#ifdef DEBUG
			std::sort(spieler.hand.begin(), spieler.hand.end(), [](std::shared_ptr<Karte> a, std::shared_ptr<Karte> b)
			{
				return a->id < b->id;
			});
			std::cout << "Hand vor Aktionen: ";
			for (auto& k : spieler.hand)
				std::cout << k->to_string() << ", ";
			std::cout << "\n";
		#endif

			// Aktionsphase

			std::vector<std::shared_ptr<Karte>> gespielte_karten;

			for (; spieler.aktionen > 0; spieler.aktionen--)
			{
				auto start_aktionskarten = std::partition(spieler.hand.begin(), spieler.hand.end(), [](std::shared_ptr<Karte> a)
				{
					return a->typ != Karte_Typ::AKTIONSKARTE;
				});

				// Keine Aktionskarten vorhanden
				if (start_aktionskarten == spieler.hand.end())
					break;

				std::sort(start_aktionskarten, spieler.hand.end(), [](std::shared_ptr<Karte> a, std::shared_ptr<Karte> b)
				{
					auto ak_a = std::static_pointer_cast<Aktionskarte>(a);
					auto ak_b = std::static_pointer_cast<Aktionskarte>(b);

					if (ak_a->aktionen > 0 && ak_b->aktionen > 0)
						return ak_a->karten < ak_b->karten;
					else if (ak_a->aktionen > 0 || ak_b->aktionen > 0)
						return ak_a->aktionen < ak_b->aktionen;
					else
						return ak_a->geld < ak_b->geld;
				});

				auto ak = std::static_pointer_cast<Aktionskarte>(spieler.hand.back());
				gespielte_karten.push_back(spieler.hand.back());
				spieler.hand.pop_back();
				ak->aktion(spieler, mitspieler);

			#ifdef DEBUG
				std::cout << "Gespielt: " << ak->to_string() << '\n';
			#endif
			}

			for (auto k : gespielte_karten)
				spieler.ablegen(k);

			gespielte_karten.clear();

			// Kaufphase

		#ifdef DEBUG
			std::sort(spieler.hand.begin(), spieler.hand.end(), [](std::shared_ptr<Karte> a, std::shared_ptr<Karte> b)
			{
				return a->id < b->id;
			});
			std::cout << "Hand vor Kauf: ";
			for (auto k : spieler.hand)
				std::cout << k->to_string() << ", ";
			std::cout << "\n";
		#endif

			for (auto k : spieler.hand)
			{
				if (k->typ == Karte_Typ::GELDKARTE)
				{
					statistik[spieler_nummer].geldkarten_auf_hand += 1;
					spieler.geld += std::static_pointer_cast<Geldkarte>(k)->geld;
				}
				if (k->typ == Karte_Typ::PUNKTEKARTE)
				{
					statistik[spieler_nummer].punktekarten_auf_hand += 1;
					statistik[spieler_nummer].punkte_auf_hand += std::static_pointer_cast<Punktekarte>(k)->punkte;
				}
			}

			statistik[spieler_nummer].geld_auf_hand += spieler.geld;

		#ifdef DEBUG
			std::cout << "Geld: " << spieler.geld << " Kaeufe: " << spieler.kaeufe << '\n';
		#endif

			for (; spieler.kaeufe > 0; spieler.kaeufe--)
			{
				switch (spieler.geld)
				{
				case 0:
				case 1:
					goto Kupfer;
				case 2:
					goto Geld2;
				case 3:
					goto Geld3;
				case 4:
					goto Geld4;
				case 5:
					goto Geld5;
				case 6:
				case 7:
					goto Gold;
				default:
					goto Provinz;
				}

			Geld2:
				if (anwesen.ist_leer() && burggraben.ist_leer())
				{
					goto Kupfer;
				}

				switch (cost2(engine))
				{
				case 0:
					goto Anwesen;
				case 1:
					goto Burggraben;
				}

			Geld3:
				if (silber.ist_leer() && dorf.ist_leer() && holzfaeller.ist_leer() && kanzler.ist_leer())
				{
					goto Geld2;
				}

				switch (cost3(engine))
				{
				case 0:
					goto Silber;
				case 1:
					goto Dorf;
				case 2:
					goto Holzfaeller;
				case 3:
					goto Kanzler;
				}

			Geld4:
				if (gaerten.ist_leer() && schmiede.ist_leer())
				{
					goto Geld3;
				}

				switch (cost4(engine))
				{
				case 0:
					goto Gaerten;
				case 1:
					goto Schmiede;
				}

			Geld5:
				if (herzogtum.ist_leer() && laboratorium.ist_leer() && markt.ist_leer() && ratsversammlung.ist_leer() && jahrmarkt.ist_leer())
				{
					goto Geld4;
				}

				switch (cost5(engine))
				{
				case 0:
					goto Herzogtum;
				case 1:
					goto Laboratorium;
				case 2:
					goto Markt;
				case 3:
					goto Ratsversammlung;
				case 4:
					goto Jahrmarkt;
				}

			Kupfer:
				spieler.ablegen(kupfer.karte_ziehen());
			#ifdef DEBUG
				std::cout << "Gekauft: Kupfer\n";
			#endif
				continue;

			Anwesen:
				if (!spieler.ablegen(anwesen.karte_ziehen()))
					goto Geld2;
				spieler.geld -= 2;
			#ifdef DEBUG
				std::cout << "Gekauft: Anwesen\n";
			#endif
				continue;
			Burggraben:
				if (!spieler.ablegen(burggraben.karte_ziehen()))
					goto Geld2;
				spieler.geld -= 2;
			#ifdef DEBUG
				std::cout << "Gekauft: Burggraben\n";
			#endif
				continue;

			Silber:
				if (!spieler.ablegen(silber.karte_ziehen()))
					goto Geld3;
				spieler.geld -= 3;
			#ifdef DEBUG
				std::cout << "Gekauft: Silber\n";
			#endif
				continue;
			Dorf:
				if (!spieler.ablegen(dorf.karte_ziehen()))
					goto Geld3;
				spieler.geld -= 3;
			#ifdef DEBUG
				std::cout << "Gekauft: Dorf\n";
			#endif
				continue;
			Holzfaeller:
				if (!spieler.ablegen(holzfaeller.karte_ziehen()))
					goto Geld3;
				spieler.geld -= 3;
			#ifdef DEBUG
				std::cout << "Gekauft: Holzfaeller\n";
			#endif
				continue;
			Kanzler:
				if (!spieler.ablegen(kanzler.karte_ziehen()))
					goto Geld3;
				spieler.geld -= 3;
			#ifdef DEBUG
				std::cout << "Gekauft: Kanzler\n";
			#endif
				continue;

			Gaerten:
				if (!spieler.ablegen(gaerten.karte_ziehen()))
					goto Geld4;
				spieler.geld -= 4;
			#ifdef DEBUG
				std::cout << "Gekauft: Gaerten\n";
			#endif
				continue;
			Schmiede:
				if (!spieler.ablegen(schmiede.karte_ziehen()))
					goto Geld4;
				spieler.geld -= 4;
			#ifdef DEBUG
				std::cout << "Gekauft: Schmiede\n";
			#endif
				continue;

			Herzogtum:
				if (!spieler.ablegen(herzogtum.karte_ziehen()))
					goto Geld5;
				spieler.geld -= 5;
			#ifdef DEBUG
				std::cout << "Gekauft: Herzogtum\n";
			#endif
				continue;
			Laboratorium:
				if (!spieler.ablegen(laboratorium.karte_ziehen()))
					goto Geld5;
				spieler.geld -= 5;
			#ifdef DEBUG
				std::cout << "Gekauft: Laboratorium\n";
			#endif
				continue;
			Markt:
				if (!spieler.ablegen(markt.karte_ziehen()))
					goto Geld5;
				spieler.geld -= 5;
			#ifdef DEBUG
				std::cout << "Gekauft: Markt\n";
			#endif
				continue;
			Ratsversammlung:
				if (!spieler.ablegen(ratsversammlung.karte_ziehen()))
					goto Geld5;
				spieler.geld -= 5;
			#ifdef DEBUG
				std::cout << "Gekauft: Ratsversammlung\n";
			#endif
				continue;
			Jahrmarkt:
				if (!spieler.ablegen(jahrmarkt.karte_ziehen()))
					goto Geld5;
				spieler.geld -= 5;
			#ifdef DEBUG
				std::cout << "Gekauft: Jahrmarkt\n";
			#endif
				continue;

			Gold:
				if (!spieler.ablegen(gold.karte_ziehen()))
					goto Geld5;
				spieler.geld -= 6;
			#ifdef DEBUG
				std::cout << "Gekauft: Gold\n";
			#endif
				continue;

			Provinz:
				if (!spieler.ablegen(provinz.karte_ziehen()))
					goto Gold;
				spieler.geld -= 8;
			#ifdef DEBUG
				std::cout << "Gekauft: Provinz\n";
			#endif
				continue;
			}
		#ifdef DEBUG
			std::cout << '\n';
		#endif

			spieler.aufraeumen();
		}
	}

	for (int i = 0; i < anzahl_spieler; i++)
	{
		statistik[i].geld_auf_hand /= (double)statistik[i].anzahl_zuege;
		statistik[i].punkte_auf_hand /= (double)statistik[i].anzahl_zuege;
		statistik[i].geldkarten_auf_hand /= (double)statistik[i].anzahl_zuege;
		statistik[i].punktekarten_auf_hand /= (double)statistik[i].anzahl_zuege;
		statistik[i].deck_groesse = mitspieler[i].deck.size();

		for (auto k : mitspieler[i].deck)
		{
			if (k->typ == Karte_Typ::GELDKARTE)
			{
				statistik[i].geld_im_deck += std::static_pointer_cast<Geldkarte>(k)->geld;
				statistik[i].geldkarten_im_deck++;
			}
			if (k->typ == Karte_Typ::PUNKTEKARTE)
			{
				statistik[i].punkte_im_deck += std::static_pointer_cast<Geldkarte>(k)->geld;
				statistik[i].punktekarten_im_deck++;
			}
			if (k->typ == Karte_Typ::GAERTEN)
			{
				statistik[i].punkte_im_deck += statistik[i].deck_groesse / 10;
			}

			statistik[i].karten_im_deck[(int)k->id]++;
		}
	}
}


std::ostream& operator<<(std::ostream& os, const Spiel& spiel)
{
	os << "Spieler,Anzahl Zuege,Deck Groesse,Geld im Deck,Geldkarten im Deck,Geld auf Hand,Geldkarten auf Hand,Punkte im Deck,Punktekarten im Deck,Punkte auf Hand,Punktekarten auf Hand,Kupfer,Silber,Gold,Anwesen,Herzogtum,Provinz,Fluch,Gaerten,Burggraben,Kapelle,Keller,Dorf,Holzfaeller,Kanzler,Werkstatt,Buerokrat,Dieb,Festmahl,Geldverleiher,Miliz,Schmiede,Spion,Thronsaal,Umbau,Bibliothek,Hexe,Jahrmarkt,Laboratorium,Markt,Mine,Ratsversammlung,Abenteurer,\n";

	for (int i = 0; i < spiel.anzahl_spieler; i++)
	{
		os	<< i + 1 << ','
			<< spiel.statistik[i].anzahl_zuege << ','
			<< spiel.statistik[i].deck_groesse << ','
			<< spiel.statistik[i].geld_im_deck << ','
			<< spiel.statistik[i].geldkarten_im_deck << ','
			<< spiel.statistik[i].geld_auf_hand << ','
			<< spiel.statistik[i].geldkarten_auf_hand << ','
			<< spiel.statistik[i].punkte_im_deck << ','
			<< spiel.statistik[i].punktekarten_im_deck << ','
			<< spiel.statistik[i].punkte_auf_hand << ','
			<< spiel.statistik[i].punktekarten_auf_hand << ',';

		for (int k = 0; k < (int)Karten_ID::SIZE; k++)
			os << spiel.statistik[i].karten_im_deck[k] << ',';

		os << '\n';
	}

	return os;
}
