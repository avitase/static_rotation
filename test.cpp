#include "static_rotation.hpp"

int main() {
    using namespace static_rotation;
    using R = IndexRotations<4>;
    constexpr auto values = R::values;
    constexpr std::array<std::size_t, 16> expected{
        // clang-format off
        0, 1, 2, 3,
        1, 2, 3, 0,
        2, 3, 0, 1,
        3, 0, 1, 2,
        // clang-format on
    };

    static_assert(R::seq_length == 4);
    static_assert([values, expected]() {
        if (values.size() != expected.size()) return false;
        for (int i = 0; i < values.size(); i++) {
            if (values.at(i) != expected.at(i)) return false;
        }
        return true;
    }());
}
