#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Wezel {
    int klucz;
    int waga;
};

class Tablica_Priorytetowa {
private:
    vector<Wezel> zbior;

    void sortuj() {
        sort(zbior.begin(), zbior.end(), [](const Wezel& lhs, const Wezel& rhs) {
            return lhs.waga > rhs.waga;
            });
    }

public:
    void dodaj(pair<int, int> para) {
        zbior.emplace_back(Wezel{ para.first, para.second });
        sortuj();
    }

    void usun_pierwszy() {
        if (!zbior.empty())
            zbior.erase(zbior.begin());
    }

    int podglad() const {
        if (zbior.empty())
            throw runtime_error("Struktura jest pusta");
        return zbior.front().klucz;
    }

    int rozmiar() const {
        return static_cast<int>(zbior.size());
    }

    void zmien_priorytet(int klucz, int nowa_waga) {
        for (auto& w : zbior) {
            if (w.klucz == klucz) {
                w.waga = nowa_waga;
                break;
            }
        }
        sortuj();
    }
};
