#include <rmcpp/explorer/View.hpp>

rmcpp::explorer::View::View (rmcpp::explorer::Tree* tree)
        : m_tree { tree } {
    m_array.resize (m_tree->height (m_tree->root ()));

    for (auto& line: m_array) {
        line.resize (m_tree->breadth (m_tree->root ()));
    }

    fill (m_array,
          m_tree->root ());
}

auto rmcpp::explorer::View::fill (std::vector<std::vector<Node*>>& tree,
                                  rmcpp::explorer::Node* root,
                                  std::uint64_t offset,
                                  std::uint64_t depth) -> void {
    tree[depth][offset + m_tree->half_breadth (root)] = root;

    const auto result = std::div (root->children ().size (),
                                  2);

    for (auto i = 0u; i < root->children ().size (); i++) {
        fill (tree,
              root->children ()[i],
              offset,
              depth + 1);

        offset += m_tree->breadth (root->children ()[i]);

        if (i == result.quot - 1 && result.rem == 0) {
            offset++;
        }
    }
}

auto rmcpp::explorer::View::decoration (const std::vector<std::vector<Node*>>& tree,
                                        const rmcpp::explorer::Node* node,
                                        std::uint64_t row,
                                        std::uint64_t column) noexcept -> std::string {
    if (node) {
        const auto& brothers = node->parent ()->children ();
        auto index = 0u;

        while (node != brothers[index]) {
            index++;
        }

        if (index == 0) {
            return tree[row - 1][column] == nullptr ? "┌" : "─";
        }

        if (index == node->parent ()->children ().size () - 1) {
            return "└";
        }

        return tree[row - 1][column] == nullptr ? "├" : "┼";
    }

    const auto previous = std::find_if (tree[row].rbegin () + tree[row].size () - column,
                                        tree[row].rend (),
                                        [] (const auto& value) { return value != nullptr; });

    const auto after = std::find_if (tree[row].begin () + column + 1,
                                     tree[row].end (),
                                     [] (const auto& value) { return value != nullptr; });

    if (previous != tree[row].rend () && after != tree[row].end ()) {
        if ((*previous)->parent () == (*after)->parent ()) {
            return tree[row - 1][column] == nullptr ? "│" : "┤";
        }
    }

    return " ";
}

auto rmcpp::explorer::View::format (const std::vector<std::vector<Node*>>& tree,
                                    const rmcpp::explorer::Node* node,
                                    std::uint64_t row,
                                    std::uint64_t column,
                                    std::uint64_t root) noexcept -> std::string {
    if (row == 0) {
        return node == nullptr ? std::string (root + 1,
                                              ' ') : node->document ()->visible_name () + " : [" +
                                                     std::to_string (node->document ()->type ()) + ']';
    }

    auto pad = 0u;
    for (const auto& line: tree[row]) {
        if (!tree[row].empty ()) {
            pad = std::max<std::uint64_t> (pad,
                                           line == nullptr ? 0 : line->document ()->visible_name ().size () +
                                                                 std::to_string (line->document ()->type ()).size () +
                                                                 1);
        }
    }

    auto deco = std::string { decoration (tree,
                                          node,
                                          row,
                                          column) };
    if (node == nullptr) {
        return deco + std::string (pad + 1,
                                   ' ');
    }

    for (auto i = 0u; i < pad - (node->document ()->visible_name ().size () +
                                 std::to_string (node->document ()->type ()).size () + 1); i++) {
        deco += "─";
    }

    return deco + ' ' + node->document ()->visible_name () + " : [" + std::to_string (node->document ()->type ()) + ']';
}

auto rmcpp::explorer::View::to_string () const noexcept -> std::string {
    auto result = std::string {};

    for (auto i = 0u; i < m_array[0].size (); i++) {
        for (auto j = 0u; j < m_array.size (); j++) {
            result += format (m_array,
                              m_array[j][i],
                              j,
                              i,
                              m_tree->root ()->document ()->visible_name ().size () + 1 +
                              std::to_string (m_tree->root ()->document ()->type ()).size ()) + " ";
        }

        result += "\n";
    }

    return result;
}
