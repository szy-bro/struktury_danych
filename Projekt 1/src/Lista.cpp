#include <iostream>
#include <stdexcept>

struct Node
{
    int data;
    Node *next;

    Node(int val) : data(val), next(nullptr) {} // Konstruktor węzła
};

class LinkedList
{
private:
    Node *head; // Wskaznik na poczatek listy
    int size;   // Rozmiar listy

public:
    // Konstrukor pustej listy
    LinkedList() : head(nullptr), size(0) {}

    // Destruktor
    ~LinkedList()
    {
        Node *current = head;
        Node *nextNode = nullptr;
        while (current != nullptr)
        {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // --- Dodwanie elementów ---
    // Na początek listy
    void addAtBeginning(int value)
    {
        Node *newNode = new Node(value); // Tworzenie nowego węzła
        newNode->next = head;            // Ustawienie węzła jako pierwszego w liscie
        head = newNode;
        size++;
    }

    // Na koniec listy
    void addAtEnd(int value)
    {
        Node *newNode = new Node(value); // Tworzenie nowego węzła
        if (head == nullptr)
        {
            head = newNode; // Jesli lista jest pusta, to nowy węzł jest pierwszy
        }
        else
        {
            Node *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode; // Dodanie węzła na koniec listy
        }
        size++;
    }

    // Na wybrany indeks
    void addAtIndex(int index, int value)
    {
        if (index < 0 || index > size)
        {
            throw std::out_of_range("Nieprawidłowy indeks do dodania elementu.");
        }
        if (index == 0)
        {
            addAtBeginning(value);
        }
        else
        {
            Node *newNode = new Node(value);
            Node *current = head;
            for (int i = 0; i < index - 1; ++i)
            {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            size++;
        }
    }

    // --- Usuwanie elementów ---
    // Z początku listy
    void deleteFromBeginning()
    {
        if (head == nullptr)
        {
            throw std::runtime_error("Lista jest pusta.");
        }
        Node *temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    // Z konca listy
    void deleteFromEnd()
    {
        if (head == nullptr)
        {
            throw std::runtime_error("Lista jest pusta.");
        }
        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            size--;
            return;
        }
        Node *current = head;
        while (current->next->next != nullptr)
        {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
        size--;
    }

    // Z wybranego indeksu
    void deleteAtIndex(int index)
    {
        if (head == nullptr)
        {
            throw std::runtime_error("Lista jest pusta.");
        }
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("Nieprawidłowy indeks do usuniecia elementu.");
        }
        if (index == 0)
        {
            deleteFromBeginning();
        }
        else
        {
            Node *current = head;
            for (int i = 0; i < index - 1; ++i)
            {
                current = current->next;
            }
            Node *temp = current->next;
            current->next = temp->next;
            delete temp;
            size--;
        }
    }

    // --- Wyszukiwanie zadanego elementu ---
    // Zwraca indeks pierwszego znalezionego elementu lub -1, jezeli nie znaleziono
    int search(int value) const
    {
        Node *current = head;
        int index = 0;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;
    }

    // --- Metody pomocnicze ---
    // Zwraca rozmiar listy
    int getSize() const
    {
        return size;
    }

    // Wypisuje zawartosc listy
    void print() const
    {
        Node *current = head;
        while (current != nullptr)
        {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};