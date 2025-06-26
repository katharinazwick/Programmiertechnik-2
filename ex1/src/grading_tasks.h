#ifndef GRADING_TASKS_H
#define GRADING_TASKS_H

#include <stdint.h>
#include <stdio.h>
#include <fstream>
#include "grading_table.h"

const int CONST_MAX_EXPECTED_RESULTS = 39;

/**
 * In dieser Datei fehlen an mehreren Stellen wichtige Schlüsselwörter, damit die Vererbung zwischen
 * den einzelnen Agenten einwandfrei funktioniert. Fügen Sie sie ein!
 * 
 * Während es nicht zwingend erforderlich ist, kann das Schlüsselwort "override" hinter der Parameterliste einer Funktion
 * genutzt werden, um zu markieren, dass diese eine Methode der Basisklasse überschreiben soll. Dies löst einen Fehler aus,
 * sollte keine Funktion überschrieben werden. Dies kann z.B. passieren, wenn die Parameterliste nicht identisch ist, oder
 * der Name falsch übernommen wurde. Fügen sie auch das Wort override bei allen Deklarationen ein, bei denen es richtig ist.
*/

class TaskAgent {
    protected:
        GradingTable* table;
    public:
    // virtual ermöglicht das spätere überschreiben einer Methode
        virtual void performTask() {};
        TaskAgent(GradingTable* table): table{table} {};
        virtual ~TaskAgent() {};
};

class IteratingTaskAgent: public TaskAgent {  
    using TaskAgent::TaskAgent;
    public:
    //override nutzen um Methode zu überschreiben
        void performTask() override;
        int visit(GradingTableEntry *current) {};
        int* visitAll();
};

class ReducingTaskAgent: public TaskAgent {
    using TaskAgent::TaskAgent;
    public:
        void performTask() override;
        int reduce(GradingTableEntry *current, int value);
        int reduceAll();
};

class TaskA: public IteratingTaskAgent {
    using IteratingTaskAgent::IteratingTaskAgent;
    public:
        int visit(GradingTableEntry *current);
};

class TaskB: public IteratingTaskAgent {
    using IteratingTaskAgent::IteratingTaskAgent;
    public:
        int visit(GradingTableEntry *current);
};

class TaskC: public ReducingTaskAgent {
    using ReducingTaskAgent::ReducingTaskAgent;
    public:
        int reduce(GradingTableEntry *current, int value);
};

class TaskD: public ReducingTaskAgent {
    using ReducingTaskAgent::ReducingTaskAgent;
    public:
        int reduce(GradingTableEntry *current, int value);
};

class TaskE: public ReducingTaskAgent {
    using ReducingTaskAgent::ReducingTaskAgent;
    public:
        int reduce(GradingTableEntry *current, int value);
};

#endif /* GRADING_TASKS */