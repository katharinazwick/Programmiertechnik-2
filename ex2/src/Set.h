#ifndef __LIST_SET_H__
#define __LIST_SET_H__

#include <stdexcept>
#include <stdio.h>

//Klasse Set impementiert generische Mengen Datenstruktur mit verketteter Liste
template <typename T>
class Set
{
private:
    //jedes Element ist ein Node das einen Wert und einen Zeiger auf den nächsten Knoten speichert
    struct Node {
        T value;
        Node *next;
        Node(const T &val, Node *nxt = nullptr) : value(val), next(nxt) {}
    };

    Node *head; //Zeiger auf den ersten Knoten
    int count; //Anzahl der Elemente

    //löscht Liste durch freigeben der Knoten
    void clear() {
        while (head) {
            Node *tmp = head;
            head = head->next;
            delete tmp;
        }
        count = 0;
    }

    //kopiert Knoten für Knoten in andere Liste
    void copyFrom(const Set<T> &other) {
        if (other.head == nullptr) {
            head = nullptr;
            count = 0;
            return;
        }
        head = new Node(other.head->value);
        Node *curr = head;
        Node *otherCurr = other.head->next;
        while (otherCurr) {
            curr->next = new Node(otherCurr->value);
            curr = curr->next;
            otherCurr = otherCurr->next;
        }
        count = other.count;
    }

public:
    //leere Menge, Speicher aufruemn, Kopie anderer Menge

    // constructor
    Set() : head(nullptr), count(0) {}

    // destructor
    ~Set() {
        clear();
    }
    // copy constructor
    Set(const Set<T> &other) : head(nullptr), count(0) {
        copyFrom(other);
    }
    // copy assignment
    //verhindert Selbstzuweisung und kopiert korrekt nachdem alte Daten gelöscht wurden
    Set<T> &operator=(const Set<T> &other) {
        if (this != &other) {
            clear();          // Clean up current list
            copyFrom(other);  // Copy nodes from 'other'
        }
        return *this;
    }
    //aktuelle Elementenanzahl
    // size
    int size() const
    {
        return count;
    }
    // operator[]
    T operator[](int index) const
    {
        throw std::out_of_range("Index out of range");
    }
    // operator==
    bool operator==(const Set<T> &other) const
    {
        return false;
    }
    // add / neues Element hinzufügen
    Set<T>& add(const T &el)
    {
        // TODO: Implement
        if (contains(el))
            return *this;

        Node *newNode = new Node(el, head);
        head = newNode;
        ++count;
        return *this;
    }
    // remove entfernen
    Set<T>& remove(const T &el)
    {
        // TODO: Implement
        Node *curr = head;
        Node *prev = nullptr;

        while (curr) {
            if (curr->value == el) {
                if (prev)
                    prev->next = curr->next;
                else
                    head = curr->next;

                delete curr;
                --count;
                return *this;
            }
            prev = curr;
            curr = curr->next;
        }
        return *this;
    }
    // contains //guckt ob Element bereits vorhanden
    bool contains(const T &elem) const
    {
        for (Node *curr = head; curr != nullptr; curr = curr->next) {
            if (curr->value == elem)
                return true;
        }
        return false;
    }
};
#endif