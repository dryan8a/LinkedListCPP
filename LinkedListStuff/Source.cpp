#include <memory>
#include <iostream>
#include "UniqueLinkedList.h"
#include "SharedLinkedList.h"

int main()
{
    UniqueLinkedList<int>::DestructorTest();
    std::cout << "Unique Done" << std::endl;

    SharedLinkedList<int>::DestructorTest();
    std::cout << "Shared Done" << std::endl;
}