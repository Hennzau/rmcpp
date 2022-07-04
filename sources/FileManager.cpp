#include <filesystem>
#include <fstream>

#include <string_view>

#include <nlohmann/json.hpp>
#include <robin_hood/robin_hood.hpp>

#include <rmcpp/FileManager.hpp>

std::vector<std::unique_ptr<rmcpp::Document>> rmcpp::from (const char* const path) noexcept {
    auto documents = std::vector<std::unique_ptr<rmcpp::Document>> {};

    auto pointers = robin_hood::unordered_map<std::string,
                                              rmcpp::Document*> {};

    auto parents = robin_hood::unordered_map<rmcpp::Document*,
                                             std::string> {};

    for (const auto& entry: std::filesystem::directory_iterator (path)) {
        if (entry.path ().extension () == ".metadata") {
            auto input = std::ifstream { entry.path () };
            auto json  = nlohmann::json {};

            input >> json;

            if (json["parent"] == "trash") {
                continue;
            }

            auto last = entry.path ().filename ().string ().find_last_of ('.');
            auto raw  = entry.path ().filename ().string ().substr (0,
                                                                    last);

            auto temporary = rmcpp::Document::Type::Notebook;

            if (json["type"] == "CollectionType") {
                temporary = rmcpp::Document::Type::Folder;
            } else if (json["type"] == "DocumentType" and std::filesystem::exists (raw + ".pdf")) {
                temporary = rmcpp::Document::Type::AnnotatedPDF;
            }

            auto& doc = documents.emplace_back (std::make_unique<rmcpp::Document> (temporary,
                                                                                   json["visibleName"],
                                                                                   raw,
                                                                                   nullptr));

            pointers[raw]       = doc.get ();
            parents[doc.get ()] = json["parent"];
        }
    }

    for (const auto& [key, val]: parents) {
        if (not val.empty ()) {
            key->set (pointers[val]);
        }
    }

    return documents;
}