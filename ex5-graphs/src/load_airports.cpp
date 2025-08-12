#include "weighted_struct_digraph.h"

struct Airport {
    ///change start
    //struct mit relevanten infos operatoren für nodeindex
    int id;
    std::string iata;
    std::string name;
    std::string city;
    std::string country;
    double latitude;
    double longitude;

    bool operator<(const Airport& other) const {
        return iata < other.iata;
    }
    bool operator>(const Airport& other) const {
        return iata > other.iata;
    }
    bool operator==(const Airport& other) const {
        return iata == other.iata;
    }
    ///chnage end
};

WeightedStructDigraph<Airport>* load_data(std::string airports_file,
                                          std::string routes_file) {
    ///chnage start
    //airport.csv öffnen und jede zeile lesen
    //infos in object füllen
    Bag<Airport> bag;
    std::ifstream aifs(airports_file);
    std::string line;

    while (std::getline(aifs, line)) {
        std::stringstream ss(line);
        Airport ap;
        std::string field;

        std::getline(ss, field, ','); ap.id = std::stoi(field);
        std::getline(ss, ap.name, ',');
        std::getline(ss, ap.city, ',');
        std::getline(ss, ap.country, ',');
        std::getline(ss, ap.iata, ',');
        std::getline(ss, field, ','); // ICAO
        std::getline(ss, field, ','); ap.latitude = std::stod(field);
        std::getline(ss, field, ','); ap.longitude = std::stod(field);

        if (!ap.iata.empty() && ap.iata != "\\N") {
            bag.add(ap); //ungültiges filtern
        }
    }
    ///change end
    WeightedStructDigraph<Airport>* sdg = new WeightedStructDigraph<Airport>();

    ///change start
    //routes.csv öfnnen und lesen / Flugzeit
    //airport object erstellen, wenn beide airports im graph kante mit gewicht hinzufügen
    sdg->initialize_nodes(bag);

    std::ifstream rifs(routes_file);
    while (std::getline(rifs, line)) {
        std::stringstream ss(line);
        std::string airline, airline_id, src_code, src_id;
        std::string dst_code, dst_id, stops, equipment, time_str;

        std::getline(ss, airline, ',');
        std::getline(ss, airline_id, ',');
        std::getline(ss, src_code, ',');
        std::getline(ss, src_id, ',');
        std::getline(ss, dst_code, ',');
        std::getline(ss, dst_id, ',');
        std::getline(ss, stops, ',');
        std::getline(ss, equipment, ',');
        std::getline(ss, time_str, ',');

        if (src_code.empty() || dst_code.empty() || time_str.empty()) continue;

        double time = std::stod(time_str);
        Airport src{0, src_code};
        Airport dst{0, dst_code};

        if (sdg->contains(src) && sdg->contains(dst)) {
            sdg->add_edge(src, dst, time);
        }
    }
    ///change end
    return sdg;
}