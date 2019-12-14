#include <array>
#include <utility>

namespace static_rotation {
namespace detail {
template <typename N, typename T, T head, T... tail>
class Rotator {
    static_assert(std::is_same_v<typename N::value_type, std::size_t>);

private:
    template <T... a, T... b>
    [[nodiscard]] constexpr static auto join(
        std::integer_sequence<T, a...>,
        std::integer_sequence<T, b...>) noexcept
    {
        return std::integer_sequence<T, a..., b...> {};
    }

    template <T... values>
    [[nodiscard]] constexpr static auto to_array(
        std::integer_sequence<T, values...>) noexcept
    {
        return std::array { values... };
    }

public:
    using next = Rotator<std::integral_constant<typename N::value_type, N::value - 1>,
        T,
        tail...,
        head>;
    constexpr static auto seq = join(std::integer_sequence<T, head, tail...> {}, next::seq);
    constexpr static auto seq_length = sizeof...(tail) + 1;
    constexpr static auto values = to_array(seq);
};

template <typename T, T head, T... tail>
struct Rotator<std::integral_constant<std::size_t, 0>, T, head, tail...> {
    constexpr static auto seq = std::integer_sequence<T> {};
};
} // namespace detail

template <typename T, T... values>
using Rotations = detail::Rotator<std::integral_constant<std::size_t, sizeof...(values)>,
    T,
    values...>;

namespace detail {
template <std::size_t... idxs>
[[nodiscard]] constexpr auto make_index_rotations(
    std::integer_sequence<std::size_t, idxs...>) noexcept
{
    return Rotations<std::size_t, idxs...> {};
}
} // namespace detail

template <std::size_t N>
using IndexRotations = decltype(detail::make_index_rotations(std::make_index_sequence<N> {}));
} // namespace static_rotation
