#include <iostream>
#include <algorithm>
#include <stdexcept>

class DynamicArray
{
private:
    int *data;
    int size;
    int capacity;

    void resize(int newCapacity)
    {
        int *newData = new int[newCapacity];
        std::copy(data, data + size, newData);
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Konstruktor - inicjalizuje tablicę o podanej początkowej pojemności (n)
    DynamicArray(int initialCapacity = 2) : size(0), capacity(initialCapacity)
    {
        if (initialCapacity <= 0)
        {
            throw std::invalid_argument("Początkowa pojemność tablicy musi być dodatnia.");
        }
        data = new int[capacity];
    }

    // Destruktor - zwalnia zablokowaną pamięć (niszczy tablicę)
    ~DynamicArray()
    {
        delete[] data;
    }

    // --- Dodawanie elementów ---
    // Na początek struktury
    void addAtBeginning(int value)
    {
        if (size == capacity)
        {
            resize(capacity * 2); // Podwojenie rozmiaru, jeśli brakuje miejsca
        }
        // Przesuwamy elementy w prawo, aby zrobić miejsce dla nowego elementu na początku
        for (int i = size; i > 0; --i)
        {
            data[i] = data[i - 1];
        }
        data[0] = value;
        size++;
    }

    // Na koniec struktury
    void addAtEnd(int value)
    {
        if (size == capacity)
        {
            resize(capacity * 2); // Podwojenie rozmiaru jeśli potrzeba
        }
        data[size] = value;
        size++;
    }

    // Na wybrany indeks w tablicy
    void addAtIndex(int index, int value)
    {
        if (index < 0 || index > size)
        {
            throw std::out_of_range("Nieprawidłowy indeks do dodania elementu.");
        }
        if (size == capacity)
        {
            resize(capacity * 2);
        }
        // Przesunięcie elementów w prawo od indeksu
        for (int i = size; i > index; --i)
        {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
    }

    // --- Usuwanie elementów ---
    // Z początku listy
    void deleteFromBeginning()
    {
        if (size == 0)
        {
            std::cerr << "Tablica jest pusta, nie można usunąć elementu." << std::endl;
            return;
        }
        // Przesuwamy wszystkie elementy w lewo poza usuwanym elementem
        for (int i = 0; i < size - 1; ++i)
        {
            data[i] = data[i + 1];
        }
        size--;
    }

    // Z końca listy
    void deleteFromEnd()
    {
        if (size == 0)
        {
            std::cerr << "Tablica jest pusta, nie można usunąć elementu." << std::endl;
            return;
        }
        size--;
    }

    // Z wybranego indeksu
    void deleteAtIndex(int index)
    {
        if (size == 0)
        {
            std::cerr << "Tablica jest pusta, nie można usunąć elementu." << std::endl;
            return;
        }
        if (index < 0 || index > size)
        {
            throw std::out_of_range("Nieprawidłowy indeks do usunięcia elementu.");
        }
        // Przesuwamy elementy w lewo od indeksu
        for (int i = index; i < size - 1; ++i)
        {
            data[i] = data[i + 1];
        }
        size--;
    }

    // --- Wyszukiwanie danego elementu ---
    // Zwraca indek pierwszego znalezionego elementu lub -1, jeśli nie znaleziono
    int search(int value) const
    {
        for (int i = 0; i < size; ++i)
        {
            if (data[i] == value)
            {
                return i;
            }
        }
        return -1; // Nie znaleziono
    }

    // --- Metody pomocnicze ---
    int getSize() const
    {
        return size;
    }

    int getCapacity() const
    {
        return capacity;
    }

    void print() const
    {
        for (int i = 0; i < size; ++i)
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};
