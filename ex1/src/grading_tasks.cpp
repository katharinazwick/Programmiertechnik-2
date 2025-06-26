#include <stdio.h>
#include <fstream>

#include "grading_table.h"
#include "grading_tasks.h"

void IteratingTaskAgent::performTask() {
    /***
     * Diese Funktion sollte visitAll aufrufen, und die Ergebnisse via printf ausgeben.
    */
    int* results = visitAll();

    for (int i = 0; i < CONST_MAX_EXPECTED_RESULTS; ++i) {
        if (results[i] != 0) {
            printf("%d\n", results[i]);
        }
    }

    delete[] results;
};

int *IteratingTaskAgent::visitAll() {
    /**
     * Diese Funktion sollte ein int-Array von der Länge CONST_MAX_EXPECTED_RESULTS anlegen,
     * und dieses mit den Zwischenergebnissen füllen, die beim besuchen jedes Elements der Liste mit visit() zurückgegeben werden.
     * Die Liste sollte mit 0 initialisiert sein. Ein Rückgabewert von visit() sollte nur dann eingetragen werden,
     * wenn dieser != 0 ist.
     * 
     * Der implementierte Iterator kann genutzt werden indem mit for über die GradingTable iteratiert wird:
     * for (GradingTableEntry el : *table) {}
     * 
     * Die Funktion sollte einen Zeiger auf die Liste zurückgeben.
    */
    //erstellt ein dynamisches Array das mit 0 initalisiert ist
    int *results = new int[CONST_MAX_EXPECTED_RESULTS]();
    int i = 0;
    for (GradingTableEntry &el: *table) {
        int result = visit(&el);
        if (result != 0 && i < CONST_MAX_EXPECTED_RESULTS) {
            results[i++] = result;
        }
    }
    return results;
};

void ReducingTaskAgent::performTask() {
    /***
     * Diese Funktion sollte reduceAll aufrufen, und die Ergebnisse via printf ausgeben.
    */

    int result = reduceAll();
    printf("%d\n", result);
};

int ReducingTaskAgent::reduceAll() {
    /**
     * Diese Funktion sollte eine Variable vom Typ int anlegen, und diese dem Reduce-Schema folgend,
     * iterativ aktualisieren. Dazu sollte reduce mit jedem Element der GradingTable und dem aktuellen Wert
     * des Zwischenspeichers aufgerufen werden. Der Rückgabewert ist dann der neue Wert des Zwischenspeichers.
     * 
     * Der finale Wert des Zwischenspeichers sollte zurückgegeben werden.
    */

    //durch Tabelle laufen und Wert aktalisieren
    int value = 0;
    for (GradingTableEntry &el: *table) {
        value = reduce(&el, value);
    }
    return value;
};

//gibt Matrikelnr, Seriennr. und Punkte aus
int TaskA::visit(GradingTableEntry *current) {
    printf("%d hat in %d %d Punkt(e) erreicht.\n", current->mat_no, current->series, current->points);
    return 1;
};

//nur Einträge bei denen Punkte unter 10 sind
int TaskB::visit(GradingTableEntry *current) {
    if (current->points < 10) {
        printf("%d %d\n", current->mat_no, current->points);
        return 1;
    }
    return 0;
}

//Anzahl der Einträge
int TaskC::reduce(GradingTableEntry *current, int value) {
    return value + 1;
}

//höchtste Punktzahl
int TaskD::reduce(GradingTableEntry *current, int value) {
    return (current->points > value) ? current->points : value;
}

//summiert alle Punkte in Serie 3
int TaskE::reduce(GradingTableEntry *current, int value) {
    if (current->series == 3) {
        return value + current->points;
    }
    return value;
};
