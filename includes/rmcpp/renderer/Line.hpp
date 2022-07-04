#pragma once

#include <cstdint>
#include <vector>

#include <rmcpp/renderer/Point.hpp>

namespace rmcpp::renderer {
    class Line {
        public:

            enum Brushes {
                /*
                * | Brush Type    | Pressure  |   Speed   |   Tilt    |
                * | ------------- |:---------:|:---------:|:---------:|
                * | Ballpoint pen |     X     |           |           |
                * | Marker pen    |     X     |           |     X     |
                * | Fine_liner pen|           |           |           |
                * | Sharp pencil  |           |           |           |
                * | Tilt pencil   |     X     |           |     X     |
                * | Brush         |     X     |     X     |     X     |
                */

                PEN_1 = 2u, PEN_2 = 3u,

                FINE_LINER = 4u,

                PENCIL_SHARP = 7u, PENCIL_TILT = 1u,

                BRUSH = 0u, HIGHLIGHTER = 5u,

                RUBBER = 6u,

                UNKNOWN_BRUSH = 7u,

                RUBBER_AREA = 8u,

                ERASE_ALL = 9u,

                SELECTION_BRUSH = 10u, SELECTION_BRUSH_2 = 11u,

                FINE_LINE_1 = 12u, FINE_LINE_2 = 13u, FINE_LINE_3 = 14u
            };

            enum Colors {
                BLACK = 0u, GREY = 1u, WHITE = 2u, BLUE = 3u, RED = 4u
            };

            static constexpr float SMALL = 1.875f;
            static constexpr float MID   = 2.0f;
            static constexpr float LARGE = 2.125f;

            explicit Line (std::int32_t brush_type = 1,
                           std::int32_t color = 0,
                           std::int32_t unknown_line_attribute = 0,
                           float brush_base_size = 2.125,
                           std::vector<Point> points = {})
                    : m_brush_type { brush_type },
                      m_color { color },
                      m_unknown_line_attribute { unknown_line_attribute },
                      m_brush_base_size { brush_base_size },
                      m_points_count { points.size () },
                      m_points { std::move (points) } {}

            [[nodiscard]] auto brush_type () const { return m_brush_type; }

            [[nodiscard]] auto color () const { return m_color; }

            [[nodiscard]] auto unknown_line_attribute () const { return m_unknown_line_attribute; }

            [[nodiscard]] auto brush_base_size () const { return m_brush_base_size; }

            [[nodiscard]] auto points_count () const { return m_points_count; }

            [[nodiscard]] const auto& points () const { return m_points; }

        private:
            std::int32_t m_brush_type;
            std::int32_t m_color;
            std::int32_t m_unknown_line_attribute;

            float m_brush_base_size;

            std::uint32_t      m_points_count;
            std::vector<Point> m_points;
    };
}