#include <memory>

#include <rmcpp/Document.hpp>

rmcpp::Document::Document (rmcpp::Document::Type type,
                           std::string visible_name,
                           std::string logical_name,
                           const rmcpp::Document* parent)
        : m_type { type },
          m_visible_name { std::move (visible_name) },
          m_logical_name { std::move (logical_name) },
          m_parent { parent } {}

void rmcpp::Document::set (const rmcpp::Document* parent) {
    m_parent = parent;
}

