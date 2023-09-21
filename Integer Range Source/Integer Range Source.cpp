#include <algorithm>
#include <numeric>
#include <string>
#include <type_traits>

template<typename _T, typename T = std::enable_if_t<std::is_integral<_T>::value || std::is_floating_point<_T>::value>>
class Range {
	T first;
	T last;
	T step;

public:
	Range(T _last) : Range(0, _last) {};
	Range(T _first, T _last, T _step = 1): first(_first), last(_last), step(_step) {};
	T begin() {
		return first;
	}
	constexpr T end() {
		return last + step;
	}
	//operator++() {}
};