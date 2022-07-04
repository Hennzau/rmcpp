#pragma once

#include <vector>
#include <memory>

#include <rmcpp/Document.hpp>

namespace rmcpp {
    std::vector<std::unique_ptr<rmcpp::Document>> from (const char* const path) noexcept;
}