#include <rmcpp/explorer/Tree.hpp>

#include <robin_hood/robin_hood.hpp>

rmcpp::explorer::Tree::Tree (std::vector<std::unique_ptr<rmcpp::Document>>* documents)
        : m_documents { documents } {
    m_root = std::make_unique<Node> (&rmcpp::Root,
                                     nullptr);

    /* Construction */

    auto pointers = robin_hood::unordered_map<const Document*,
                                              Node*> {};

    for (const auto& doc: *m_documents) {
        pointers[doc.get ()] = add (doc.get (),
                                    nullptr);
    }

    for (auto& node: m_children) {
        const auto parent = node->document ()->parent ();

        if (parent) {
            node->set (pointers[parent]);
        } else {
            node->set (m_root.get ());
        }
    }
}

auto rmcpp::explorer::Tree::add (rmcpp::Document* document,
                                 Node* parent) -> rmcpp::explorer::Node* {
    m_children.emplace_back (std::make_unique<Node> (document,
                                                     parent));

    return m_children.back ().get ();
}

auto rmcpp::explorer::Tree::height (rmcpp::explorer::Node* root) const noexcept -> std::uint64_t {
    auto result = std::uint64_t { 0u };

    for (const auto& child: root->children ()) {
        result = std::max (height (child),
                           result);
    }

    return result + 1;
}

auto rmcpp::explorer::Tree::breadth (rmcpp::explorer::Node* root) const noexcept -> std::uint64_t {
    auto result = std::uint64_t { 0u };

    for (const auto& child: root->children ()) {
        result += breadth (child);
    }

    return (result / 2) * 2 + 1;
}

auto rmcpp::explorer::Tree::half_breadth (rmcpp::explorer::Node* root) const noexcept -> std::uint64_t {
    const auto half   = root->children ().size () / 2;
    auto       result = std::uint64_t { 0u };

    for (auto i = 0u; i < half; i++) {
        result += breadth (root->children ()[i]);
    }

    if (root->children ().size () & 1) {
        result += half_breadth (root->children ()[half]);
    }

    return result;
}
