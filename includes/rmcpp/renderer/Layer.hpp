#pragma once

#include <cstdint>
#include <vector>

#include <rmcpp/renderer/Line.hpp>

namespace rmcpp::renderer {
    class Layer {
        public:

            explicit Layer (std::vector<Line> lines)
                    : m_lines_count { lines.size () },
                      m_lines { std::move (lines) } {}

            [[nodiscard]] auto lines_count () const noexcept { return m_lines_count; }

            [[nodiscard]] auto& lines () const noexcept { return m_lines; }

        private:
            std::uint32_t     m_lines_count;
            std::vector<Line> m_lines;
    };
}