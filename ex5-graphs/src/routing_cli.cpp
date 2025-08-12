#include <iostream>
#include <string>

//A algorithmus zur pfadsuche auf graphen implementieren
//kommandozeilen programm
int main(int argc, char* argv[]) {
    // TODO: Implementieren Sie das CLI hier.
    ///change start
    //beide flughäfen codes da?
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " SRC DST" << std::endl;
        return 1;
    }

    //datei laden und argumente lesen
    std::string src_code = argv[1];
    std::string dst_code = argv[2];

    WeightedStructDigraph<Airport>* sdg = load_data("data/airports.csv", "data/routes.csv");

    //objecte erstellen
    Airport src{0, src_code};
    Airport dst{0, dst_code};

    //wenn flughafen nicht exestiert
    if (!sdg->contains(src) || !sdg->contains(dst)) {
        std::cout << "-\ninf" << std::endl;
        return 0;
    }

    auto path = a_star(*sdg, src, dst, euclidean<Airport>);

    //a algorithmus mit euclidean hueristik / kein pfad gefunden
    if (path.is_empty()) {
        std::cout << "-\ninf" << std::endl;
    } else {
        //pfad verarbeiten und ausgeben
        std::vector<std::string> route;
        float total = 0.0;
        std::vector<Airport> nodes;

        for (const auto& airport : path) nodes.push_back(airport);
        std::reverse(nodes.begin(), nodes.end()); //pfad umdrehen

        for (size_t i = 0; i < nodes.size(); ++i) {
            route.push_back(nodes[i].iata);
            if (i + 1 < nodes.size()) {
                total += sdg->get_graph().weight( //reisezeit in h summieren
                        sdg->index_of(nodes[i]),
                        sdg->index_of(nodes[i + 1])
                );
            }
        }

        for (size_t i = 0; i < route.size(); ++i) {
            std::cout << route[i];
            if (i + 1 < route.size()) std::cout << "-";
        }
        std::cout << "\n" << total << std::endl;
    }
    ///change end
    return 0;
}