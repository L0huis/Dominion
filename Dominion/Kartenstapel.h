#pragma once

#include <memory>

template<class T>
class Stapel
{
private:
	size_t anzahl;
	std::shared_ptr<T> karte;

public:
	Stapel(size_t _anzahl = 10);
	std::shared_ptr<T> karte_ziehen();
	bool ist_leer() const;
};

template<class T>
inline Stapel<T>::Stapel(size_t _anzahl) : anzahl(_anzahl)
{
	karte = std::make_shared<T>();
}

template<class T>
inline std::shared_ptr<T> Stapel<T>::karte_ziehen()
{
	if (anzahl == 0)
		return nullptr;
	--anzahl;
	return karte;
}

template<class T>
inline bool Stapel<T>::ist_leer() const
{
	return anzahl <= 0;
}
