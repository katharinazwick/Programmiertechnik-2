#include "Set.h"
#include <iostream>

//Aufgabe 3:
/*
 * Implementierte Methode für eine Set Datenstruktur mit linked List
 * Axiome von Mengen (keine Duplikate, Reihenfolge egal)
 * Rule of Three:
 * Copy Konstruktor and Assignment
 * Destruktor
 * Set Klasse umplemtieren für Schnittmenge, Vereinigung und Mengendifferenz
 */
template <typename T>
//Schnittmenge: ELemente die in beiden Mengen sind
Set<T> intersection(Set<T> &a, Set<T> &b)
{
    // TODO: Implement me.
    Set<T> result;
    for (int i = 0; i < a.size(); ++i) {
        T val = a[i];
        if (b.contains(val)) {
            result = result.add(val);
        }
    }
    return result;
}

template <typename T>
//Vereinigungsmenge: alle Elemente aus a und b (Duplikate durch add vermieden)
Set<T> union_(Set<T> &a, Set<T> &b)
{
    // TODO: Implement me.
    Set<T> result;
    for (int i = 0; i < a.size(); ++i) {
        result = result.add(a[i]);
    }
    for (int i = 0; i < b.size(); ++i) {
        result = result.add(b[i]);
    }
    return result;
}

template <typename T>
//Differenz: alles in a was nicht in b
Set<T> difference(Set<T> &a, Set<T> &b)
{
    // TODO: Implement me.
    Set<T> result;
    for (int i = 0; i < a.size(); ++i) {
        T val = a[i];
        if (!b.contains(val)) {
            result = result.add(val);
        }
    }
    return result;
}

//legt Menge 1,2,3 and und gibt set size: 3 aus
int main() {
    Set<int> s;
    s = s.add(1).add(2).add(3);

    std::cout << "Set size: " << s.size() << std::endl;
}