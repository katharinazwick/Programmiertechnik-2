#include "sorting.h"

//aufgabe 1
//Standart Vergleichslogik
 int Comparator::compare(int *data, int x, int y) {
    if (data[x] < data[y]) return -1;
    if (data[x] > data[y]) return 1;
    return 0;
}

//inernen Zähler auf null setzen um mit neuer Sortierung zu starten
void CountingComparator::resetCounter() {
    counter = 0;
}

//gibt Zähler zurück (Anzahl vergleiche)
int CountingComparator::getCounter() const {
    return counter;
}
//aufgabe 2
//jeder Vergelich wird gezäht
int CountingComparator::compare(int *data, int x, int y) {
    ++counter;
    return comp.compare(data, x, y);
}

//tausch
void SortingAlgorithm::swap(int i, int j) {
    int x = data[i];
    data[i] = data[j];
    data[j] = x;
}

//aufgabe 2
//von l-r Paare tauschen bis Ende, dann erneut
void BubbleSort::sort()
{
    for (int end = size - 1; end > 0; --end) {
        bool swapped = false;
        for (int i = 0; i < end; ++i) {
            if (comp.compare(data, i, i + 1) > 0) {
                swap(i, i + 1);
                swapped = true;
            }
        }
        if (!swapped) break; // Array ist bereits sortiert
    }
}

//Array in zwei Hälften sortieren
void MergeSort::split(int lo, int hi)
{
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;
    split(lo, mid);
    split(mid + 1, hi);
    merge(lo, mid, hi);
}
//div and c

//sortierte Hälften zusammenfügen //jedes Vergleich zwischen
//in zwei Hälften teilen und soritert zusammenfügen
void MergeSort::merge(int lo, int mid, int hi) {
    // Optimierung: wenn bereits sortiert, nichts tun
    if (comp.compare(data, mid, mid + 1) <= 0) {
        return;
    }
    // Kopieren in Hilfsarray
    for (int k = lo; k <= hi; ++k) {
        aux[k] = data[k];
    }
    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; ++k) {
        if (i > mid) { //links fertig weier mi rechts
            data[k] = aux[j++];
        } else if (j > hi) { //rechts fertig weiter mi links
            data[k] = aux[i++];
        } else if (comp.compare(aux, i, j) <= 0) {
            data[k] = aux[i++]; //beide noch nicht ferig
        } else {
            data[k] = aux[j++];
        }
    }
}

void MergeSort::sort()
{
    // Initialisiert das Hilfsarray und startet den Sortiervorgang durch Aufruf von split()
    aux = new int[size];
    split(0, size - 1);
    delete[] aux;
}

//wählt erstes Element als Pivot / i sucht nach E > P / j  nach E <= P / dann swap
int QuickSort::divide(int lo, int hi)
{
    int pivotIndex = lo;
    int i = lo + 1;
    int j = hi;
    while (true) {
        //Vergleich in compare wird gezählt
        while (i <= j && comp.compare(data, i, pivotIndex) <= 0) {
            ++i;
        }
        while (j > lo && comp.compare(data, j, pivotIndex) > 0) {
            --j;
        }
        if (i >= j) break;
        swap(i, j);
    }
    swap(lo, j);
    return j;
}

//soritert Teilbereiche
//teile das array solange bis alles sortiert
void QuickSort::qs(int lo, int hi)
{
    if (lo >= hi) return;
    int p = divide(lo, hi);
    qs(lo, p - 1);
    qs(p + 1, hi);
}

void QuickSort::sort()
{
    // Startet den Sortiervorgang durch Aufruf von qs()
    qs(0, size - 1);
};

//Pivot wählen und alles kleiner und größer sortieren