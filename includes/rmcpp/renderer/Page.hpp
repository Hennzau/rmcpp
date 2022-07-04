#pragma once

#include <cstdint>
#include <vector>

#include <rmcpp/renderer/Layer.hpp>

namespace rmcpp::renderer {
    class Page {
        public:

            explicit Page (std::vector<Layer> layers)
                    : m_layers_count { layers.size () },
                      m_layers { std::move (layers) } {}

            [[nodiscard]] auto layers_count () const noexcept { return m_layers_count; }

            [[nodiscard]] auto& layers () const noexcept { return m_layers; }

        private:

            std::uint32_t      m_layers_count;
            std::vector<Layer> m_layers;
    };
}