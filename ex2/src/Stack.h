#ifndef __LIST_STACK_H__
#define __LIST_STACK_H__

#include <stdexcept>

//Aufgabe 1
/*
 * Stack soll mit verketteter Liste dynamisch werden
 * length(empty) = 0 (leere stack länge 0)
 * length(push(S, x)) = length(S) + 1 (wenn hinzufügen, erhöht länge um 1)
 * length soll unterstütz werden heißt, länge aktualisieren bei push or pop
 */
// Implements a stack with a linked list
//Stack mit verketteter Liste / Datenstruktur bei der letztes zuerst raus (LIFO)
template <typename T>
class Stack
{
    // stores the stack elements as a linked list
    //enthält data und Zeiger auf nächstes Element / head ist pointer auf Anfang
    struct List
    {
        T data;
        List *next;
    } *head;
    
    //TODO add variable to store current capacity!
    int size = 0;
    // copys an existing list
    //rekursion für jedes Element neuer Knoten
    const List *deep_copy_list(const List *new_head)
    {
        if (new_head)
        {
            auto tail = deep_copy_list(new_head->next);
            return (new List(new_head->data, tail));
            //erst Kopie vom Rest, dann neuer Knoten
        }

        return (nullptr);
    }

    // frees the list and sets the head to NULL
    void free_list()
    {
        while (head)
        {
            List *tmp = head->next;
            delete head;
            head = tmp;
        }
        return;
    }

public:
    // constructor
    Stack() : head(nullptr) {}

    // copy constructor
    Stack(const Stack &s) { head = deep_copy_list(s.head); }

    // move constructor
    Stack(Stack &&s) : head(s.head) { s.head = nullptr; }

    // copy assignment
    Stack &operator=(const Stack &s)
    {
        // free the existing stack
        free_list();
        // copy the stack passed in
        head = deep_copy_list(s.head);
        return (*this);
    }

    // move assignment
    Stack &operator=(Stack &&s)
    {
        // free the existing stack
        free_list();

        head = s.head;
        s.head = nullptr;
        return (*this);
    }

    // destructor
    ~Stack()
    {
        free_list();
    }

    // is_empty method
    const bool is_empty(void)
    {
        return (head == nullptr);
    }

    const int length(void)
    {
        //TODO
        return size;
    }

    // push method
    void push(const T &x)
    {
        List *new_head = new List;
        new_head->data = x;
        new_head->next = head;
        head = new_head;

        //TODO add required logic according to new axioms!
        size++;
    }

    // pop method
    T pop()
    {
        if (is_empty())
            throw std::logic_error("Calling pop on an empty stack");

        List *tmp = head->next;
        T ret_value = head->data;
        delete head;
        head = tmp;

        return (ret_value);

        //TODO add required logic according to new axioms!
        size--;

    }

    // top method
    //kostanten verweis auf das oberste Element zurück ohne es zu entfernen
    const T &top()
    {
        if (is_empty())
            throw std::logic_error("Calling top on an empty stack");

        return (head->data);
    }
};

#endif
