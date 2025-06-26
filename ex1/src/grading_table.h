#ifndef GRADING_TABLE_H
#define GRADING_TABLE_H

#include <stdint.h>
#include <stdio.h>
#include <fstream>

class TaskAgent;

class GradingTableEntry {
    public:
        uint32_t mat_no;              /* matriculation number */
        uint16_t series;              /* series */
        uint16_t points;              /* points scored */
        GradingTableEntry *next;
};

class GradingTable {
    public:
    //g_head => erstes Element, g_tail => letztes Element
        GradingTableEntry *g_head, *g_tail;
        struct Iterator {
            using iterator_category = std::forward_iterator_tag;
            using difference_time = std::ptrdiff_t; //Unterschiede zwischen Iteratoren
            using value_type = GradingTableEntry;
            using pointer = GradingTableEntry*;
            using reference = GradingTableEntry&;

            /** 
             * Ein Iterator muss die folgenden Operatoren implementieren:
             * operator* (Muss das Objekt auflösen auf das der Iterator im Momemnt zeigt, nicht auf den Iterator selber)
             * operator-> (Muss den Pointer zurückgeben, der auf das Objekt zeigt)
             * Iterator& operator++ (
             *  Muss ERST den Pointer aktualisieren, so dass er auf das nächste Objekt zeigt und eine Referenz auf das
             * Iteratorobjekt zurückgeben. (Iterator++)
             * )
             * Iterator operator++(int) (
             *  Muss einen Iterator anlegen, der auf das aktuelle Objekt zeigt, 
             *  den aktuellen Pointer auf das nächste Zeigen lassen und den angelegt Iterator zurückgeben (++Iterator)
             * )
             * operator== (
             *  Gibt true zurück, wenn zwei Iteratoren auf dasselbe oder beide das Ende der Liste erreicht haben.
             * )
             * operator!= (
             *  Das Inverse von operator ==.
             * )
            */

            //Objeckt auf das der Iterator zeigt
            reference operator*() const {
                return *m_ptr
            };
            //Zeiger auf dem Objekt
            pointer operator->() {
                return m_ptr
            };
            //bewegt Iterator auf nächster Listenelement + Referenz auf sich selbst
            Iterator& operator++() {
                if(m_ptr) m_ptr = m_ptr->next;
                return *this;
            };
            //kopierten Iterator und bewegt den echten auf das nächste Element
            Iterator operator++(int) {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            };

            //true wenn auf das gleiche Objekt gezeigt wird
            friend bool operator== (const Iterator& a, const Iterator& b) {
                return a.m_ptr == b.m_ptr;
            };
            friend bool operator!= (const Iterator& a, const Iterator& b) {
                return a.m_ptr != b.m_ptr;
            };

            Iterator(pointer ptr) : m_ptr(ptr) {}

            //tatsächlicher Zeiger auf das aktuelle Element
            private:
                pointer m_ptr;
        };

        /**
         * Begin und End müssen jeweils ein Iteratorobjekt zurückgeben:
         * - Begin eines, dass auf das erste Element der Liste zeigt.
         * - Ende eines, dass das Erreichen des Listenendes markiert. Wurde ein Iterator it benutzt,
         *   um die Liste zu traversiren, muss it==list.end() wahr sein wenn dieser Iterator hinter das letzte
         *   Element der Liste gewandert ist.
        */

        //Iterator auf das erste Element
        Iterator begin() {
            return Iterator(g_head);
        };
        Iterator end() {
            return Iterator(nullptr);
        };
        GradingTable(std::ifstream &fp);
        ~GradingTable();
};

#endif /* GRADING_TABLE */