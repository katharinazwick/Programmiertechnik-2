#include "generator.h"

void swap(int* data, int i, int j)
{
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

//Array in aufsteigender Reihenfolge
int* generateSorted(int n)
{
    int* data = new int[n];
    for (int i = 0; i < n; i++) {
        data[i] = i;
    }
    return data;
};

//fügt zwei sortiere arrays  zusammen
void merge(int* data, int* left, int* right, int size, int m) {
    int i = 0, j = 0, k = m;
    while (i < m && j < size) {
        if (left[i] <= right[j]) {
            data[k] = left[i];
            i++;
        }
        else {
            data[k] = right[j];
            j++;
        }
    }
}

//trennt array / gerade zuerst / ungerade danach
void separate(int* data, int size) {
    int i = 0, j = 0;
    while (i < size) {
        if (data[i] % 2 == 0) {
            swap(data, i, j);
            j++;
        }
        i++;
    }
}

//umedrehtes array 5,4,3
int* generateWorstCaseBubblesort(int n)
{
    int* data = generateSorted(n);
    for (int i = 0; i < n/2; ++i) swap(data, i, n - 1 - i);
    return data;
};

//teilt in gerade und ungerade und immer weiter zerlegen
int* generateWorstCaseMergesort(int n)
{
    int* data = generateSorted(n);
    if (n <= 2) {
        if (n == 2) swap(data, 0, 1);
        return data;
    }
    // recursively separate
    separate(data, n);
    int mid = n/2;
    generateWorstCaseMergesort(mid);
    generateWorstCaseMergesort(n-mid);
    return data;
};

//sortiertes Array / wenn das erste element als pivot
int* generateWorstCaseQuicksort(int n)
{
    return generateSorted(n);
};

//soriertes array / läuft durch nichts passiert
int* generateBestCaseBubblesort(int n) {
    return generateSorted(n);
}

//sortiertes array / guckt oh sortiert
int* generateBestCaseMergesort(int n) {
    return generateSorted(n);
}

//Pivot liegt in der Mitte ==> optimal
void rearrange(int* data, int lo, int hi) {
    int len = hi - lo + 1;
    if (len <= 2) {
        if (len == 2) swap(data, lo, hi);
        return;
    }
    int mid = lo + len/2;
    swap(data, lo, mid);
    rearrange(data, lo+1, mid);
    rearrange(data, mid+1, hi);
}

int* generateBestCaseQuicksort(int n) {
    int* data = generateSorted(n);
    rearrange(data, 0, n-1);
    return data;
}