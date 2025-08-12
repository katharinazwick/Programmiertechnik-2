/******************************************************************************
 *
 * A directed graph, where the vertex names are arbitrary strings.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at
 *https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

//gerichteten Graphen implementieren der mit node struct arbeiten
//Kantengewichte unterstützt, Knoten als Struct speichert
#ifndef __STRUCT_DIGRAPH_H__
#define __STRUCT_DIGRAPH_H__

#include <string>

#include "vlib/edge.h"
#include "vlib/redblack_bst.h"
#include "vlib/weighted_digraph.h"

using namespace std;

// Implements a class representing a directed graph, where the vertex names are
// arbitrary strings
template <typename Node>
class WeightedStructDigraph {
   public:
    ///change start
    //Flughäfen als node struct übergeben, prüfen ob im nodeIndex vorhanden, sonst
    //einem Index zuweisen und im indexNode vector speichern
    explicit WeightedStructDigraph(const Bag<Node>& nodes) {
        int idx = 0;
        for (const auto& node : nodes) {
            if (!contains(node)) {
                nodeIndex_[node] = idx++;
                indexNode_.push_back(node);
            }
        }
        //graphen initalisieren mit passender nazahl knoten
        graph_ = EdgeWeightedDigraph(idx);
    }

    WeightedStructDigraph(const WeightedStructDigraph& other) = default;
    WeightedStructDigraph(WeightedStructDigraph&& other) noexcept = default;
    WeightedStructDigraph& operator=(const WeightedStructDigraph& other) = default;
    WeightedStructDigraph& operator=(WeightedStructDigraph&& other) noexcept = default;
    ~WeightedStructDigraph() = default;
    ///change end
    // bag constructor
    // implement constructor
    // copy constructor
    // move constructor
    // copy assignment
    // move assignment
    // destructor
    // Implementieren Sie die folgenden Methoden aus SymbolGraph:
    // - contains
    // - index_of
    // - name_of
    // - get_graph
    // Zusätzlich brauchen wir:
    // - add_edge
    ///change start
    //node im graphen enthalten mit find(node)? true wenn ja
    bool contains(const Node& node) const {
        return nodeIndex_.find(node) != nodeIndex_.end();
    }

    //welchen index hat knoten im graphen? .at wirft ausnahme wenn key nicht exestiert
    int index_of(const Node& node) const {
        return nodeIndex_.at(node);
    }

    //welcher node gehört zum index? idx = 2 ==> dritten node
    const Node& name_of(int idx) const {
        return indexNode_.at(idx);
    }

    //iteriert über alle kanten lesend
    const EdgeWeightedDigraph& get_graph() const {
        return graph_;
    }

    //fügt gerichtete kante mit from to ein
    void add_edge(const Node& from, const Node& to, double weight) {
        int v = index_of(from);
        int w = index_of(to);
        graph_.addEdge(Edge(v, w, weight));
    }


private:
    std::map<Node, int> nodeIndex_; //verknüpft jeden node struct mit einem index
    std::vector<Node> indexNode_; //umkehrung index in node
    EdgeWeightedDigraph graph_;
    ///chnage end
};

#endif
