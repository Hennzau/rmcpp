#include <rmcpp/explorer/Node.hpp>

rmcpp::explorer::Node::Node (rmcpp::Document* document,
                             rmcpp::explorer::Node* parent)
        : m_document { document },
          m_parent { parent } {
    if (parent) {
        parent->add (this);
    }
}

auto rmcpp::explorer::Node::add (rmcpp::explorer::Node* child) noexcept -> void {
    if (std::find (m_children.cbegin (),
                   m_children.cend (),
                   child) == m_children.cend ()) {
        m_children.emplace_back (child);
    }
}

auto rmcpp::explorer::Node::remove (rmcpp::explorer::Node* child) noexcept -> void {
    const auto it = std::find (m_children.cbegin (),
                               m_children.cend (),
                               child);

    if (it != m_children.cend ()) {
        m_children.erase (it);
    }
}

auto rmcpp::explorer::Node::set (rmcpp::explorer::Node* parent) noexcept -> void {
    if (m_parent) {
        m_parent->remove (this);
    }

    m_parent = parent;
    m_parent->add (this);
}
