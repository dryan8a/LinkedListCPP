#pragma once

template <typename T>
struct UniqueNode
{
    T value;
    std::unique_ptr<UniqueNode> next;

    UniqueNode(T value);
};

template <typename T>
UniqueNode<T>::UniqueNode(T value) : value{ value } {}


template <typename T>
struct UniqueLinkedList
{
    std::unique_ptr<UniqueNode<T>> head;

    ~UniqueLinkedList<T>();

    void Append(T value);

    bool Remove(T value);

    static void DestructorTest();
};

template <typename T>
UniqueLinkedList<T>::~UniqueLinkedList()
{
    while (head != nullptr)
    {
        head = std::move(head->next);
    }
}

template <typename T>
void UniqueLinkedList<T>::Append(T value)
{
    if (head == nullptr)
    {
        head = std::make_unique<UniqueNode<T>>(value);
        return;
    }
    UniqueNode<T>* current = head.get();
    while (current->next != nullptr)
    {
        current = current->next.get();
    }
    current->next = std::make_unique<UniqueNode<T>>(value);
}


template <typename T>
bool UniqueLinkedList<T>::Remove(T value)
{
    if (head->value == value)
    {
        head = std::move(head->next);
        return true;
    }
    UniqueNode<T>* current = head.get();

    while (current->next != nullptr)
    {
        if (current->next->value == value)
        {
            current->next = std::move(current->next->next);
            return true;
        }
        current = current->next.get();
    }
    return false;
}

template <typename T>
void UniqueLinkedList<T>::DestructorTest()
{
    auto list = new UniqueLinkedList<int>{};
    list->Append(0);

    UniqueNode<int>* current = list->head.get();
    for (int i = 1; i < 10000000; i++)
    {
        current->next = std::make_unique<UniqueNode<int>>(i);
        current = current->next.get();
    }
}