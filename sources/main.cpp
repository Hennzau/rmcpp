#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>
#include <robin_hood/robin_hood.hpp>

#include <rmcpp/Document.hpp>
#include <rmcpp/FileManager.hpp>

#include <rmcpp/explorer/Tree.hpp>
#include <rmcpp/explorer/View.hpp>

static constexpr auto path = R"(E:\Documents\Cours\reMarkable\xochitl 07062022)";

int main () {
    auto documents = rmcpp::from (path);

    /*for (const auto& doc: documents) {
        std::cout << doc->visible_name () << " | " << (doc->parent () ? doc->parent ()->visible_name () : "ROOT")
                  << std::endl;
    }*/

    auto tree = rmcpp::explorer::Tree (&documents);

    const auto viewer = rmcpp::explorer::View (&tree);

    auto output = std::ofstream { "test.txt " };
    output << viewer.to_string();

    return 0;
}
