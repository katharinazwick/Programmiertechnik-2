# Lösung für Aufgabe 3

Bei Abgabe sollte diese Datei die Ausgabe der main.cpp in ihrer Implementierung enthalten.

Jeweils eine durch unsere Lösung generierte Beispielfolge ist :

    a) Bubble: 9876543210
    b) Merge: 0246853719
    c) Quick: 0123456789

# Lösung für Aufgabe 4

Comparing worst cases 
BS, n=10, counts= 45
BS, n=100, counts= 4950
BS, n=1000, counts= 499500
QS, n=10, counts= 54
QS, n=100, counts= 5049
QS, n=1000, counts= 500499
MS, n=10, counts= 23
MS, n=100, counts= 374
MS, n=1000, counts= 5112
Comparing best cases 
BS, n=10, counts= 9
BS, n=100, counts= 99
BS, n=1000, counts= 999
QS, n=10, counts= 32
QS, n=100, counts= 856
QS, n=1000, counts= 14088
MS, n=10, counts= 9
MS, n=100, counts= 99
MS, n=1000, counts= 999


Im Großen und Ganzen stimmen die Werte mit der Theorie überein. 
Für Bubble-Sort gilt ja sogar für den Worst-Case die Abschätzung von  N(N-1)/2 Vergleichen, und unser Resultat mit 499500 Vergleichen passt so ziemlich perfekt, der Bestcase von n ist mit 999 Vergleichen auch gegeben. 
Für Quick-Sort lässt sich sagen, dass wir mit dem Worst-Case 500499 und Best-Case 14088 was n*log(n) = 1000*log(1000) = 10000, auch grob im Rahmen, wenn auch etwas darüber ist, vielleicht lässt sich das mit einem konstanten Faktor erklären, eventuell ist die Wahl des Pivot-Elements ausschlaggebend.
Merge sort jedoch hat Merge Sort hat theoretisch immer eine Zeitkomplexität von O(n log n), man sieht jedoch große abweichungen im Best und Worstcase. Dennoch muss man sagen, dass sich beides im Rahmen von 10.000 Vergleichen bewegt und somit der Theorie entspricht.

Die Anzahl der Vergleiche ist für diese Art von Experiment eine passable Metrik, wenn man auch eine Dinge beachten muss. Zum Einen ist diese Metrik beim Sortieren gut geeignet, da beim Sortieren Vergleiche eine zentrale Operation darstellen. Jedoch werden solche Dinge wie Speicherzugriffe, oder die Optimierung für Cache-Zugriffe gänzlich ignoriert, was problematisch wäre, wenn die Anzahl der Vergleichsoperationen die einzige Metrik zur Bewertung des Programms zugezogen werden würde. Was beispielsweise darüberhinaus interessant wäre, wäre die CPU oder sogar Wallclock-Time. 
