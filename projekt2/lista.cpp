#include <iostream>
using namespace std;

struct Element {
    int dane;
    int priorytet;
    Element* nastepny;
};

class Lista_Priorytetowa {
private:
    Element* head;

public:
    Lista_Priorytetowa() : head(nullptr) {}

    void dodaj(pair<int, int> para) {
        Element* nowyElement = new Element{ para.first, para.second, nullptr };

        if (head == nullptr || para.second > head->priorytet) {
            nowyElement->nastepny = head;
            head = nowyElement;
            return;
        }

        Element* iterator = head;
        while (iterator->nastepny != nullptr && iterator->nastepny->priorytet >= para.second) {
            iterator = iterator->nastepny;
        }

        nowyElement->nastepny = iterator->nastepny;
        iterator->nastepny = nowyElement;
    }

    void usun_pierwszy() {
        if (head == nullptr) return;

        Element* doUsuniecia = head;
        head = head->nastepny;
        delete doUsuniecia;
    }

    int podglad() const {
        if (head == nullptr)
            throw runtime_error("Kolejka jest pusta");
        return head->dane;
    }

    int rozmiar() const {
        int licznik = 0;
        for (Element* it = head; it != nullptr; it = it->nastepny)
            ++licznik;
        return licznik;
    }

    void zmien_priorytet(int szukanaWartosc, int nowyPriorytet) {
        Element* aktualny = head;
        Element* poprzedni = nullptr;

        while (aktualny != nullptr && aktualny->dane != szukanaWartosc) {
            poprzedni = aktualny;
            aktualny = aktualny->nastepny;
        }

        if (aktualny == nullptr)
            return;

        if (poprzedni == nullptr)
            head = aktualny->nastepny;
        else
            poprzedni->nastepny = aktualny->nastepny;

        delete aktualny;

        dodaj({ szukanaWartosc, nowyPriorytet });
    }
};
