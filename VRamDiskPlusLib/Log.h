#pragma once

#include <iostream>

template <class A, class... Args>
void Log(A&& arg, Args&&... args) {
	std::cout << arg;
	if constexpr (sizeof...(Args) > 0)
		Log(args...);
	else
		std::cerr << std::endl;
}

template <class A, class... Args>
void LogCommaSeparated(A&& arg, Args&&... args) {
	std::cout << arg;
	if constexpr (sizeof...(Args) > 0)
	{
		std::cerr << ", ";
		Log(args...);
	}
	else
		std::cerr << std::endl;
}
