#include "pch.h"
#include "../Dominion/Karten.h"
#include "../Dominion/Kartenstapel.h"
#include "../Dominion/Karten.cpp"
#include "../Dominion/Spieler.cpp"

TEST(Karten, KartenTest)
{
	size_t size = 10;
	Stapel<Burggraben> stapel(size);

	auto a = stapel.karte_ziehen();
	EXPECT_EQ(a->id, Karten_ID::BURGGRABEN);

	for (int i = 1; i < size; i++)
		stapel.karte_ziehen();

	EXPECT_TRUE(stapel.ist_leer());
	EXPECT_EQ(stapel.karte_ziehen(), nullptr);
}

TEST(Karten, Kombinationen)
{
	std::vector<std::shared_ptr<Karte>> karten {
		std::make_shared<Dorf>(Dorf()),
		std::make_shared<Anwesen>(Anwesen()),
		std::make_shared<Laboratorium>(Laboratorium()),
		std::make_shared<Burggraben>(Burggraben()),
		std::make_shared<Kupfer>(Kupfer()),
		std::make_shared<Markt>(Markt()),
		std::make_shared<Holzfaeller>(Holzfaeller())
	};

	std::vector<std::shared_ptr<Karte>> expected {
		std::make_shared<Kupfer>(Kupfer()),
		std::make_shared<Anwesen>(Anwesen()),
		std::make_shared<Burggraben>(Burggraben()),
		std::make_shared<Holzfaeller>(Holzfaeller()),
		std::make_shared<Dorf>(Dorf()),
		std::make_shared<Markt>(Markt()),
		std::make_shared<Laboratorium>(Laboratorium())
	};

	auto start_aktionskarten = std::partition(karten.begin(), karten.end(), [](std::shared_ptr<Karte> a)
	{
		return a->typ != Karte_Typ::AKTIONSKARTE;
	});

	std::sort(start_aktionskarten, karten.end(), [](std::shared_ptr<Karte> a, std::shared_ptr<Karte> b)
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

	for (size_t i = 0; i < karten.size(); i++)
		EXPECT_EQ(karten[i]->to_string(), expected[i]->to_string()) << "Index was: " << i;
}