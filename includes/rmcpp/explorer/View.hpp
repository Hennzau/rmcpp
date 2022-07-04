#pragma once

#include <rmcpp/Document.hpp>

#include <rmcpp/explorer/Tree.hpp>

namespace rmcpp::explorer {
    class View {
        public:

            explicit View (Tree* tree);

            auto to_string () const noexcept -> std::string;

        private:

            auto fill (std::vector<std::vector<Node*>>& tree,
                       Node* root,
                       std::uint64_t offset = 0,
                       std::uint64_t depth = 0) -> void;

            static auto decoration (const std::vector<std::vector<Node*>>& tree,
                                    const Node* node,
                                    std::uint64_t row,
                                    std::uint64_t column) noexcept -> std::string;

            static auto format (const std::vector<std::vector<Node*>>& tree,
                                const Node* node,
                                std::uint64_t row,
                                std::uint64_t column,
                                std::uint64_t root) noexcept -> std::string;

            Tree* m_tree;
            std::vector<std::vector<Node* >> m_array;
    };
}