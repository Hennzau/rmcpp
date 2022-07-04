#include <iostream>
#include <fstream>
#include <filesystem>

#include <nlohmann/json.hpp>
#include <robin_hood/robin_hood.hpp>

#include <rmcpp/Document.hpp>
#include <rmcpp/FileManager.hpp>

#include <rmcpp/explorer/Tree.hpp>
#include <rmcpp/explorer/View.hpp>

#include <rmcpp/renderer/Notebook.hpp>

static constexpr auto path = R"(E:\Documents\Cours\reMarkable\xochitl 07062022)";

auto get_path (const rmcpp::Document* document) -> std::string {
    if (not document->parent ()) {
        return "root/" + document->visible_name ();
    }

    return get_path (document->parent ()) + "/" + document->visible_name ();
}

int main () {

    /* retrieving documents data */

    auto documents = rmcpp::from (path);

    auto tree = rmcpp::explorer::Tree (&documents);

    /* tree viewer */
    /*
    const auto viewer = rmcpp::explorer::View (&tree);
    auto       output = std::ofstream { "tree.txt " };
    output << viewer.to_string ();
    */

    /* recreating folder structure */

    auto waiting = std::vector<rmcpp::explorer::Node*> { tree.root () };
    auto already = std::vector<rmcpp::explorer::Node*> { tree.root () };

    while (not waiting.empty ()) {
        auto node = waiting.back ();
        waiting.pop_back ();

        if (std::find (already.begin (),
                       already.end (),
                       node) == already.end ()) {

            if (node->document ()->type () == rmcpp::Document::Folder) {
                /*std::filesystem::create_directories (get_path (node->document ()));*/
            } else if (node->document ()->type () == rmcpp::Document::AnnotatedPDF) {
                /*std::filesystem::copy_file (std::string (path) + "/" + node->document ()->logical_name () + ".pdf",
                                            get_path (node->document ()) + ".pdf"); */
            } else {

            }

            already.emplace_back (node);
        }

        for (auto& child: node->children ()) {
            if (std::find (already.begin (),
                           already.end (),
                           child) == already.end ()) {
                waiting.emplace_back (child);
            }
        }
    }

    return 0;
}
