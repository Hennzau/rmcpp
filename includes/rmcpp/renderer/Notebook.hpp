#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <rmcpp/renderer/Page.hpp>

#include <rmcpp/Document.hpp>

namespace rmcpp::renderer {
    class Notebook {
        public:

            Notebook (const char* path,
                      Document* document);

            ~Notebook () = default;

            [[nodiscard]] auto pages_count () const noexcept { return m_pages_count; }

            [[nodiscard]] auto UUID () const noexcept { return m_UUID; }

            [[nodiscard]] auto& pages () const noexcept { return m_pages; }

        private:
            std::uint32_t     m_pages_count;
            std::vector<Page> m_pages;
    };
}