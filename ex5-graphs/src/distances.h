#ifndef __DISTANCES_H
#define __DISTANCES_H
#include <cmath>

#include "weighted_struct_digraph.h"

// In all of these cases I assume that a and b are of the same type
// and that a is the current node and b is the node I want to go to

//Funktion die luftlinie zwischen 2 häfen berechnet

const double EARTH_RADIUS =
    6371.0;  // Earth's radius in kilometers (use this one)

template <typename T>
float haversine(const WeightedStructDigraph<T> &g, const T &a, const T &b) {
    // I return the geodesic distance between a and b
    // Meaning the distance on a great circle.
    // I use the haversine formula for this.
    ///chnage start AU2
    //haversine formel um echte entfernung auf kugel zu berechen
    //umwandlung länge und breite in radiant
    double lat1 = a.latitude * M_PI / 180.0;
    double lat2 = b.latitude * M_PI / 180.0;
    double dlat = lat2 - lat1;
    double dlon = (b.longitude - a.longitude) * M_PI / 180.0;
    double h = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
    double distance = 2 * EARTH_RADIUS * asin(sqrt(h));
    return static_cast<float>(distance);
    ///change end
}

template <typename T>
float euclidean(const WeightedStructDigraph<T> &sdg, const T &a, const T &b) {
    /*
    I return the euclidean distance between a and b
    S . . . .
    . \ . . .
    . . \ . .
    . . . Z .
    . . . . .
    */
    ///change start AU2
    //geradliniege abstand im 2d raum
    double dx = a.latitude - b.latitude;
    double dy = a.longitude - b.longitude;
    return static_cast<float>(sqrt(dx * dx + dy * dy));
    ///change end
};

template <typename T>
float manhattan(const WeightedStructDigraph<T> &g, const T &a, const T &b) {
    /*
    I return the manhattan distance between a and b
    S - - ┐ .
    . . . | .
    . . . | .
    . . . Z .
    . . . . .
    */
    ///change start AU2
    //manhattan distanz (summe absolute distanz)
    return static_cast<float>(std::abs(a.latitude - b.latitude) + std::abs(a.longitude - b.longitude));
    ///change end
};

template <typename T>
float out_degree(const WeightedStructDigraph<T> &g, const T &a, const T &b) {
    // I return a heuristik which is dependend on the indegree of b
    // meaning the number of edges going out of b
    ///change start AU2
    //anazhl ausgehender kanten von b berechnen und negatives vorzeichen / fur a nicht zulässig
        int index = g.index_of(b);
        return static_cast<float>(-g.get_graph().adj(index).size());
    ///chnage end
};

#endif