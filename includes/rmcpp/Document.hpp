#pragma once

#include <string>

namespace rmcpp {
    class Document {
        public:

            enum Type {
                Folder, Notebook, AnnotatedPDF
            };

            Document (Type type,
                      std::string visible_name,
                      std::string logical_name,
                      const Document* parent);

            void set (const Document* parent);

            [[nodiscard]] auto& type () const noexcept { return m_type; }

            [[nodiscard]] auto& parent () const noexcept { return m_parent; }

            [[nodiscard]] auto& visible_name () const noexcept { return m_visible_name; }

            [[nodiscard]] auto& logical_name () const noexcept { return m_logical_name; }

        private:

            Type m_type;

            std::string m_visible_name;
            std::string m_logical_name;

            const Document* m_parent;
    };

    [[maybe_unused]] static Document Root = Document { rmcpp::Document::Type::Folder,
                                                       "ROOT",
                                                       "ROOT",
                                                       nullptr };
}