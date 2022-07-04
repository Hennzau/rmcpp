#pragma once

#include <vector>
#include <memory>

#include <rmcpp/explorer/Node.hpp>

#include <rmcpp/Document.hpp>

namespace rmcpp::explorer {
    class Tree {
        public:

            explicit Tree (std::vector<std::unique_ptr<rmcpp::Document>>* documents);

            ~Tree () = default;

            auto add (Document* document,
                      Node* parent) -> Node*;

            auto height (Node* root) const noexcept -> std::uint64_t;

            auto breadth (Node* root) const noexcept -> std::uint64_t;

            auto half_breadth (Node* root) const noexcept -> std::uint64_t;

            [[nodiscard]] auto* root () const noexcept { return m_root.get (); }

            [[nodiscard]] auto* root () noexcept { return m_root.get (); }

        private:
            std::unique_ptr<Node>              m_root;
            std::vector<std::unique_ptr<Node>> m_children;

            std::vector<std::unique_ptr<rmcpp::Document>>* m_documents;
    };
}