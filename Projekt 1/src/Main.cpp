#include <iostream>
#include "linked_list.cpp"
#include "dynamic_list.cpp"
#include <chrono>
#include <thread>

int main()
{
    std::chrono::seconds timespan(3);

    std::cout << "--- Testy DynamicArray ---" << std::endl;
    DynamicArray arr(3);
    arr.print();

    arr.addAtEnd(10);
    arr.addAtEnd(20);
    arr.print();

    arr.addAtBeginning(5);
    arr.print();

    arr.addAtIndex(2, 15);
    arr.print();

    try
    {
        arr.addAtIndex(6, 100);
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Wyjątek: " << e.what() << std::endl;
        std::this_thread::sleep_for(timespan);
    }

    std::cout << "Szukamy 15: index = " << arr.search(15) << std::endl;
    std::cout << "Szukamy 99: index = " << arr.search(99) << std::endl;

    arr.deleteFromEnd();
    arr.print();

    arr.deleteFromBeginning();
    arr.print();

    arr.deleteAtIndex(1);
    arr.print();

    std::cout << "--- Testy LinkedList ---" << std::endl;
    LinkedList list;
    list.print();

    list.addAtEnd(100);
    list.addAtEnd(200);
    list.print();

    list.addAtBeginning(50);
    list.print();

    list.addAtIndex(1, 75);
    list.print();

    try
    {
        list.addAtIndex(3, 1000);
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Wyjątek: " << e.what() << std::endl;
    }

    std::cout << "Szukamy 200: index = " << list.search(200) << std::endl;
    std::cout << "Szukamy 99: index = " << list.search(99) << std::endl;

    list.deleteFromEnd();
    list.print();

    list.deleteFromBeginning();
    list.print();

    list.deleteAtIndex(1);
    list.print();

    return 0;
}