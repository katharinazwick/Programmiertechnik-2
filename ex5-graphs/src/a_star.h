
#include <functional>
#include <vector>

#include "vlib/bag.h"
#include "vlib/index_min_pq.h"
#include "weighted_struct_digraph.h"

template <typename T>
Bag<T> a_star(
    const WeightedStructDigraph<T>& sdg, const T& source, const T& dest,
    std::function<float(const WeightedStructDigraph<T>&, const T&, const T&)>
        heuristic) {
    // TODO: Implementieren Sie hier den A*-Algorithmus
    // Bedenken Sie, dass die Distamzmaße aus distances.h nicht in Stunden sind
    // und umgewandelt werden müssen und daher nicht _direkt_ genutzt werden
    // können.
    ///change start
    //kürzesten pfad von source nach dest + heuristikfunktion
    Bag<T> path;
    const auto& graph = sdg.get_graph(); //graph + anzahl knoten
    int V = graph.V();

    std::unordered_map<int, double> dist; //aktuell bekannte miminalele kosten zu knoten
    std::unordered_map<int, int> edgeTo; //vorgängerknoten
    std::vector<bool> visited(V, false); //makiert bearbeitete knotne
    IndexMinPQ<double> pq(V); //prioritätswarteschlange sortiert

    int s = sdg.index_of(source); //umwandlung struct knoten in integer indizies
    int d = sdg.index_of(dest);

    //distanz bekommt unendlich außer s = 0
    for (int v = 0; v < V; ++v) dist[v] = std::numeric_limits<double>::infinity();
    dist[s] = 0.0;
    pq.insert(s, 0.0);

    //hole knoten v mit kleinstem g + h wert
    //wenn v ziel abrehcne sonst v makieren
    while (!pq.isEmpty()) {
        int v = pq.delMin();
        if (v == d) break;
        visited[v] = true;

        //für nachbar w prüfen ob besserer weg verfügbar
        //wenn ja: neue distanz speichern, vorgänger setztn h(n) berechen
        for (const Edge& e : graph.adj(v)) {
            int w = e.to();
            if (visited[w]) continue;

            double newDist = dist[v] + e.weight();
            if (newDist < dist[w]) {
                dist[w] = newDist;
                edgeTo[w] = v;
                double h = heuristic(sdg, sdg.name_of(w), dest);
                //wert in schalnge aktualisieren
                if (pq.contains(w)) pq.decreaseKey(w, newDist + h);
                else pq.insert(w, newDist + h);
            }
        }
    }

    //kein pfasd gefunden wenn ziel nicht erreciht
    if (dist[d] == std::numeric_limits<double>::infinity()) return path;

    //von ziel nach start aufbauen
    for (int at = d; at != s; at = edgeTo[at]) {
        path.add(sdg.name_of(at));
    }
    path.add(sdg.name_of(s));
    return path;
    ///chnage end
}