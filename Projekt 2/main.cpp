#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>
using namespace std;
using namespace chrono;

#include "lista.cpp"
#include "tablica.cpp"

const int ROZMIAR_TESTU = 10000;

template <typename TypStruktury>
void testujWydajnosc(const string& etykieta) {
    TypStruktury struktura;

    auto t0 = high_resolution_clock::now();
    for (int i = 0; i < ROZMIAR_TESTU; ++i)
        struktura.dodaj({ i, rand() % 100 });
    auto t1 = high_resolution_clock::now();
    long czas_dod = duration_cast<milliseconds>(t1 - t0).count();

    t0 = high_resolution_clock::now();
    for (int i = 0; i < ROZMIAR_TESTU; ++i)
        struktura.rozmiar();
    t1 = high_resolution_clock::now();
    long czas_liczba = duration_cast<milliseconds>(t1 - t0).count();

    t0 = high_resolution_clock::now();
    for (int i = 0; i < ROZMIAR_TESTU; ++i)
        struktura.podglad();
    t1 = high_resolution_clock::now();
    long czas_podglad = duration_cast<milliseconds>(t1 - t0).count();

    t0 = high_resolution_clock::now();
    for (int i = 0; i < ROZMIAR_TESTU; ++i)
        struktura.zmien_priorytet(i, rand() % 100);
    t1 = high_resolution_clock::now();
    long czas_aktualizacja = duration_cast<milliseconds>(t1 - t0).count();

    t0 = high_resolution_clock::now();
    for (int i = 0; i < ROZMIAR_TESTU; ++i)
        struktura.usun_pierwszy();
    t1 = high_resolution_clock::now();
    long czas_usun = duration_cast<milliseconds>(t1 - t0).count();

    cout << "\n=== Wyniki testu: " << etykieta << " ===\n";
    cout << "Dodanie elementow      : " << czas_dod << " ms\n";
    cout << "Podglad elementow      : " << czas_podglad << " ms\n";
    cout << "Liczenie elementow     : " << czas_liczba << " ms\n";
    cout << "Zmiana priorytetow     : " << czas_aktualizacja << " ms\n";
    cout << "Usuniecie elementow    : " << czas_usun << " ms\n";
}

int main() {
    testujWydajnosc<Lista_Priorytetowa>("Lista priorytetowa");
    testujWydajnosc<Tablica_Priorytetowa>("Tablica priorytetowa");
    return 0;
}
