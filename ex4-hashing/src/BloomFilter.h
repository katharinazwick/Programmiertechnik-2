#pragma once

#include <array>
#include <functional>
#include <iostream>
#include <vector>

/*
 * Der Code implementiert die wesentlichen Funktionen eines Bloom-Filters mit:

    Internem Bitvektor (std::vector<bool>)

    Anpassbarer Hash-Funktion für mehrere Hash-Werte pro Element

    Methoden zum Hinzufügen (add) und Überprüfen (contains) von Elementen

    Hilfsfunktionen für Indexberechnung und Füllstand
 */


template<typename T, std::size_t N>
class BloomFilter {
private:
    // TODO: Add relevant members here.
    // Hint: I would use a std::vector or std::bitset for the filter
    // then you could be able to get away without using custom constructors /
    // destructors

    ///Datensturkut die prüft ob Element in einer Menge ist / T = Typ der Elemente und N = Anazl Hash Werte key nimmt T und gibt Array N zurücl
    ///
    ///change start
    std::vector<bool> bit_vector; //repräsentiert die bits
    int filter_size; //wie viele bits zur verfügung stehen
    std::function<std::array<long, N>(T & )> key_function;
    ///change end

public:
    BloomFilter(int filter_size,
                std::function<std::array<long, N>(T & )> key_function){
        // TODO: Add implementation.
        ///Konstruktor size gespeichert und vector mit Elementen angelegt alle auf false / initalisiert bloom mi größe
        ///change start
        this->filter_size = filter_size;
        this->bit_vector = std::vector<bool>(filter_size, false);
        this->key_function = key_function;
        ///change end

    }

    // helper function to get the index of a key in the filter
    int key_idx(long key) {
        // TODO: Add implementation.
        // Idea: idx = Key modulo filter size
        // if idx is negative, add filter size
        ///wandet hash wert in index um
        ///change start
        int idx = key % filter_size;
        if (idx < 0) idx += filter_size; //sichert das indext zischen 0 und size - 1 ist
        return idx;
        ///change end
    }

    float fill_ratio() {
        // TODO: Add implementation.
        // fill ratio = number of bits set / total filter size
        ///wieviele bits auf true und anteil der bis als floa zurückgeben / wie voll ist filter
        ///change start
        int count = 0;
        for (bool bit : bit_vector) {
            if (bit) count++;
        }
        return static_cast<float>(count) / filter_size;
        ///chnage end
    }

    void add(T &item) {
        // TODO: Add implementation.
        ///für jedes item werden N werte berechnet / fürjeden wert index im bit vector bestimmt
        ///change start
        std::array<long, N> hashes = key_function(item);
        for (auto h : hashes) {
            int idx = key_idx(h);
            bit_vector[idx] = true;
        }
        ///change end
    }

    bool contains(T &item) {
        // TODO: Add implementation.
        ///n hash werte berechnet  / für jeden prüfen ob bit gesetzt / wenn nicht vorhanden element nicht da
        ///change start
        std::array<long, N> hashes = key_function(item);
        for (auto h : hashes) {
            if (!bit_vector[key_idx(h)]) return false;
        }
        return true;
    }
        ///change en
    }
};
