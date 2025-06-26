#pragma once


#ifndef SORTING_H
#define SORTING_H

class Comparator
{
public:
    virtual int compare(int data[], int x, int y); //change to virtual ==> überschreiben möglich
};

class CountingComparator
{
protected:
    Comparator &comp;
    int counter;

public:
    void resetCounter();
    int getCounter() const;
    int compare(int data[], int x, int y);
    explicit CountingComparator(Comparator &comp) : comp(comp), counter(0){}; //explicit ==> typkonvertierung verhinder
};

class SortingAlgorithm
{
protected:
    int *data;
    int size;
    CountingComparator &comp;

public:
    void swap(int i, int j);
    virtual void sort() = 0; //change
    SortingAlgorithm(int *sortData, int dataSize, CountingComparator &comparator) : data(sortData), size(dataSize), comp(comparator){};
    virtual ~SortingAlgorithm() = default; //change to virtual destructor
};

class BubbleSort : public SortingAlgorithm
{
    using SortingAlgorithm::SortingAlgorithm;

public:
    void sort() override;
};

class MergeSort : public SortingAlgorithm
{
    using SortingAlgorithm::SortingAlgorithm;

protected:
    int *aux;

public:
    void sort() override;
    void split(int l, int r);
    void merge(int l, int r, int halfway);
};

class QuickSort : public SortingAlgorithm
{
    using SortingAlgorithm::SortingAlgorithm;

public:
    void sort() override;
    int divide(int l, int r);
    void qs(int l, int r);
};

#endif /* SORTING_H */