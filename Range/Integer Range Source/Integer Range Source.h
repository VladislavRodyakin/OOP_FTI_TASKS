#pragma once

#include <algorithm>
#include <cmath>
#include <string>
#include <type_traits>
#include <exception>
template<typename T>
class Range_iterator {
	const T& start, stop, step;
	size_t index;
public:
	Range_iterator(const T& _start, const T& _stop, const T& _step, size_t _index) :
		start(_start), stop(_stop), step(_step), index(_index) {};
	Range_iterator& operator++() {
		index++;
		return *this;
	}
	bool operator!=(Range_iterator& other) {
		return index != other.index;
	}
	T operator*() const {
		return start + (step * index);
	}
};

template<typename T, typename _T = std::enable_if_t<std::is_integral<T>::value || std::is_floating_point<T>::value>>
class Range {
	T first;
	T last;
	T step;

public:
	//Range(const T& _first, const T& _last) : Range(_first, _last) {};
	Range(const T& _last) : Range(0, _last) {};
	Range(const T& _first, const T& _last, const T& _step = 1) : first(_first), last(_last), step(_step) {
		if ((first < last && step < 0) || (first > last && step > 0) || step == 0) {
			throw std::exception("Invalid range.");
		}
	}

	//iterator funcs
	Range_iterator<T> begin() const {
		return Range_iterator<T>(first, last, step, 0);
	}
	Range_iterator<T> end() const {
		return Range_iterator<T>(first, last, step, std::ceil((last - first) / step));
	}
	//operator++() {}
};
