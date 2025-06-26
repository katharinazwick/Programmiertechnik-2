#include "grading_table.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>


GradingTable::GradingTable(std::ifstream &fp) : g_head(nullptr), g_tail(nullptr){
    /**
     * Lesen Sie die übergebene Datenbank ein und speicher Sie die Daten in einer einfach verketteten Liste (Linked List).
     * 
     * Einige Anmerkungen:
     * Prüfen Sie bei FilePointern immer ob diese offen sind und nicht bereits das Ende der Datei erreicht haben.
     * fp.read liest die als zweiten Parameter übergebene Menge an Bytes in die Speicheradresse ein, die als erstes übergeben wird.
     * fp.read erwartet einen char* als ersten Parameter. Die Funktion reinterpret_cast<char *> wandelt die festgelegten
     * Datentypen in diesen Typ um.
    */

    if (!fp.is_open()) {
        std::cerr << "Datei konnte nicht geöffnet werden." << std::endl;
        return;
    }

    //Schleife bis zum Ende der Dateii
    while (!fp.eof()) {
        //erzeut ein neues Entry-Objekt
        GradingTableEntry *entry = new GradingTableEntry();

        //Einlesen und speichern der Bytes
        fp.read(reinterpret_cast<char *>(&entry->mat_no), sizeof(uint32_t));
        fp.read(reinterpret_cast<char *>(&entry->series), sizeof(uint16_t));
        fp.read(reinterpret_cast<char *>(&entry->points), sizeof(uint16_t));
        entry->next = nullptr;

        if (g_tail) {
            //zeigt auf das hinzugefügte Element
            g_tail->next = entry;
            g_tail = entry;
        } else {
            g_head = g_tail = entry;
        }
    }
}

GradingTable::~GradingTable() {
    /**
     * Hier muss ein Destruktor geschrieben werden, der alle Element der linked List aus dem Speicher entfernt.
    */

    //g_head wird Stück für Stück freigegeben
    GradingTableEntry *current = g_head;
    while (current) {
        GradingTableEntry *next = current->next;
        delete current;
        current = next;
    }
    g_head = g_tail = nullptr;
}