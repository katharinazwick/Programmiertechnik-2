#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>

#include "BloomFilter.h"
#include "hash.h"
/*
 * Bloom Filter Anzahl zeichneketten abzuschätzen
 * Schlüsselfunktion / Klasse / main
 */
int main(int argc, char **argv) {
    // TODO: Implement the CLI here
    ///change start
    if (argc != 2) {
        std::cerr << "Usage: ./bloom_cli <path-to-fasta>" << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }
//liest datei zeichenweise / ignoriert leerzeichen usw / baut string
    std::string sequence;
    char c;
    while (infile.get(c)) {
        if (!isspace(c)) {
            sequence += c;
        }
    }
//verwendet 7 hashfunktionen
    const int k = 12;
    const int filter_size = 30'000'000;
    BloomFilter<std::string, 7> filter(
            filter_size,
            [](std::string &s) { return hash_key<std::string, 7>(s); });

    int unique_kmers = 0;
//iteriert durch 12mer / prüft ob neu / wenn hinzufügen und den zähler erhöhen unique
    for (size_t i = 0; i + k <= sequence.size(); ++i) {
        std::string kmer = sequence.substr(i, k);
        if (!filter.contains(kmer)) {
            filter.add(kmer);
            unique_kmers++;
        }
    }

    std::cout << "Estimated number of unique 12-mers: " << unique_kmers << std::endl;
    //geschätzte anzhal
    ///change end
    return 0;
}