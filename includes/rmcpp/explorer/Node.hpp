#pragma once

#include <vector>

#include <rmcpp/Document.hpp>

namespace rmcpp::explorer {
    class Node {
        public:

            Node (Document* document,
                  Node* parent);

            ~Node () = default;

            auto add (rmcpp::explorer::Node* child) noexcept -> void;

            auto remove (rmcpp::explorer::Node* child) noexcept -> void;

            auto set (rmcpp::explorer::Node* parent) noexcept -> void;

            [[nodiscard]] auto& document () noexcept { return m_document; }

            [[nodiscard]] auto& document () const noexcept { return m_document; }

            [[nodiscard]] auto& parent () noexcept { return m_parent; }

            [[nodiscard]] auto& parent () const noexcept { return m_parent; }

            [[nodiscard]] auto& children () noexcept { return m_children; }

            [[nodiscard]] auto& children () const noexcept { return m_children; }

        private:
            Document* m_document;
            Node    * m_parent;

            std::vector<Node*> m_children;
    };
}