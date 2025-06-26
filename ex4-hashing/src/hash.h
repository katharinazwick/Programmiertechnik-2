#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename T, std::size_t N>
std::array<long, N> hash_key(const T& a) {
    // TODO: Implement me
    ///change
    std::array<long, N> hashes; //array zum specihern hash werte
    std::hash<T> hasher; //objekt
    long current = hasher(a); //berechnet hashwert

    for (std::size_t i = 0; i < N; ++i) {
        hashes[i] = current; //speichert hash an position i
        current = std::hash < long > {}(current); //neuen hashwert basierend auf alt
    } //fehlt!!!!!!
    return hashes;
    ///change
}
