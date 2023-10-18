#include "gtest/gtest.h"
#include "../Integer Range Source/Integer Range Source.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <ostream>
#include <iterator>

TEST(int_test, forward_step_1) {
	std::vector<int> expected{ 0,1,2,3,4,5 };
	std::vector<int> result{};
	for (auto i : Range<int>(6)) {
		result.push_back(i);
	}
	EXPECT_EQ(true, expected == result);
}

TEST(int_test, reverse_step_1) {
	std::vector<int> expected{ 5,4,3,2,1 };
	std::vector<int> result{};
	for (auto i : Range<int>(5, 0, -1)) {
		result.push_back(i);
	}
	EXPECT_EQ(true, expected == result);
}

TEST(int_test, forward_step_2) {
	std::vector<int> expected{ 0,2,4,6,8,10,12 };
	std::vector<int> result{};
	for (auto i : Range<int>(0, 14, 2)) {
		result.push_back(i);
	}
	EXPECT_EQ(true, expected == result);
}

TEST(int_test, reverse_step_2) {
	std::vector<int> expected{ 10,8,6,4,2 };
	std::vector<int> result{};
	for (auto i : Range<int>(10, 0, -2)) {
		result.push_back(i);
	}
	EXPECT_EQ(true, expected == result);
}



constexpr double EPS = 10e-6;
TEST(double_test, forward_step_01) {
	std::vector<double> expected{ 0,0.1,0.2,0.3,0.4,0.5 };
	std::vector<double> result{};
	for (auto i : Range<double>(0, 0.6, 0.1)) {
		result.push_back(i);
	}
	std::for_each(expected.begin(), expected.end(), [&result](auto a) {
		static int index = 0;
		EXPECT_NEAR(a, result.at(index++), EPS);
		});
}

TEST(double_test, forward_step_02) {
	std::vector<double> expected{ 0,0.2,0.4,0.6,0.8 };
	std::vector<double> result{};
	for (auto i : Range<double>(0, 1, 0.2)) {
		result.push_back(i);
	}
	std::for_each(expected.begin(), expected.end(), [&result](auto a) {
		static int index = 0;
		EXPECT_NEAR(a, result.at(index++), EPS);
		});
}

TEST(double_test, reverse_step_01) {
	std::vector<double> expected{ 0.5,0.4,0.3,0.2,0.1 };
	std::vector<double> result{};
	for (auto i : Range<double>(0.5, 0, -0.1)) {
		result.push_back(i);
	}
	std::for_each(expected.begin(), expected.end(), [&result](auto a) {
		static int index = 0;
		EXPECT_NEAR(a, result.at(index++), EPS);
		});
}

TEST(double_test, reverse_step_02) {
	std::vector<double> expected{ 1,0.8,0.6,0.4,0.2 };
	std::vector<double> result{};
	for (auto i : Range<double>(1, 0, -0.2)) {
		result.push_back(i);
	}
	std::for_each(expected.begin(), expected.end(), [&result](auto a) {
		static int index = 0;
		EXPECT_NEAR(a, result.at(index++), EPS);
		});
}



TEST(float_test, forward_step_01) {
	std::vector<float> expected{ 0,0.1,0.2,0.3,0.4,0.5 };
	std::vector<float> result{};
	for (auto i : Range<float>(0, 0.6, 0.1)) {
		result.push_back(i);
	}
	std::for_each(expected.begin(), expected.end(), [&result](auto a) {
		static int index = 0;
		EXPECT_NEAR(a, result.at(index++), EPS);
		});
}

TEST(float_test, forward_step_02) {
	std::vector<float> expected{ 0,0.2,0.4,0.6,0.8 };
	std::vector<float> result{};
	for (auto i : Range<float>(0, 1, 0.2)) {
		result.push_back(i);
	}
	std::for_each(expected.begin(), expected.end(), [&result](auto a) {
		static int index = 0;
		EXPECT_NEAR(a, result.at(index++), EPS);
		});
}

TEST(float_test, reverse_step_01) {
	std::vector<float> expected{ 0.5,0.4,0.3,0.2,0.1 };
	std::vector<float> result{};
	for (auto i : Range<float>(0.5, 0, -0.1)) {
		result.push_back(i);
	}
	std::for_each(expected.begin(), expected.end(), [&result](auto a) {
		static int index = 0;
		EXPECT_NEAR(a, result.at(index++), EPS);
		});
}

TEST(float_test, reverse_step_02) {
	std::vector<float> expected{ 1,0.8,0.6,0.4,0.2 };
	std::vector<float> result{};
	for (auto i : Range<float>(1, 0, -0.2)) {
		result.push_back(i);
	}
	std::for_each(expected.begin(), expected.end(), [&result](auto a) {
		static int index = 0;
		EXPECT_NEAR(a, result.at(index++), EPS);
		});
}