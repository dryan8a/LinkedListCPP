#pragma once
#include <memory>
#include <iostream>

template <typename T>
struct SharedNode
{
    T value;
    std::shared_ptr<SharedNode> next;

    SharedNode(T value);
};

template <typename T>
SharedNode<T>::SharedNode(T value) : value{ value } {}


template <typename T>
struct SharedLinkedList
{
    std::shared_ptr<SharedNode<T>> head;

    ~SharedLinkedList();

    void Append(T value);
   
    bool Remove(T value);

    static void DestructorTest();
};

template <typename T>
SharedLinkedList<T>::~SharedLinkedList()
{
    while (head != nullptr)
    {
        head = std::move(head->next);
    }
}

template <typename T>
void SharedLinkedList<T>::Append(T value)
{
    if (head == nullptr)
    {
        head = std::make_shared<SharedNode<T>>(value);
        return;
    }

    std::weak_ptr<SharedNode<T>> current = head;
    while (current.lock()->next != nullptr)
    {
        current = current.lock()->next;
    }
    current.lock()->next = std::make_shared<SharedNode<T>>(value);
}

template <typename T>
bool SharedLinkedList<T>::Remove(T value)
{
    if (head->value == value)
    {
        head = std::move(head->next);
        return true;
    }
    std::weak_ptr<SharedNode<T>> current = head;

    while (current.lock()->next != nullptr)
    {
        if (current.lock()->next->value == value)
        {
            current.lock()->next = std::move(current.lock()->next->next);
            return true;
        }
        current = current.lock()->next;
    }
    return false;
}

template <typename T>
void SharedLinkedList<T>::DestructorTest()
{
    auto list = new SharedLinkedList<int>{};
    list->Append(0);
    std::weak_ptr<SharedNode<int>> current = list->head;
    for (int i = 1; i < 10000000; i++)
    {
        current.lock()->next = std::make_shared<SharedNode<int>>(i);
        current = current.lock()->next;
    }
}