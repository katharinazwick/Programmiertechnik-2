#pragma once


#ifndef GENERATOR_H
#define GENERATOR_H

static inline void swap(int* data, int i, int j);

static inline void merge(int* data, int* left, int* right, int size, int m);
static inline void separate(int* data, int size);
int* generateSorted(int n);
//static: Funktion auf die Datei beschränkt, inline: verhindert Mehrfachdefinitionen
//gut beim einbinden
int* generateWorstCaseMergesort(int n);
int* generateWorstCaseQuicksort(int n);
int* generateWorstCaseBubblesort(int n);
int* generateBestCaseMergesort(int n);
int* generateBestCaseQuicksort(int n);
int* generateBestCaseBubblesort(int n);

#endif /* GENERATOR_H */