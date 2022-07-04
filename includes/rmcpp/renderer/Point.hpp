#pragma once

namespace rmcpp::renderer {
    class Point {
        public:

            enum Coords {
                MIN_X = 0u, MAX_X = 1404u, MIN_Y = 0u, MAX_Y = 1872u,
            };

            static constexpr float MIN_P = 0.0f;
            static constexpr float MAX_P = 1.0f;

            static constexpr float MIN_DIR = 0.0f;
            static constexpr float MAX_DIR = 3.1415926535f * 2.0f;

            Point (float x,
                   float y,
                   float speed,
                   float direction,
                   float width,
                   float pressure)
                    : m_x { x },
                      m_y { y },
                      m_speed { speed },
                      m_direction { direction },
                      m_width { width },
                      m_pressure { pressure } {}

            [[nodiscard]] auto x () const { return m_x; }

            [[nodiscard]] auto y () const { return m_y; }

            [[nodiscard]] auto speed () const { return m_speed; }

            [[nodiscard]] auto direction () const { return m_direction; }

            [[nodiscard]] auto width () const { return m_width; }

            [[nodiscard]] auto pressure () const { return m_pressure; }

        private:

            float m_x;
            float m_y;
            float m_speed;
            float m_direction;
            float m_width;
            float m_pressure;

    };
}