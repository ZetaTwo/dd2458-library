#include <string>
#include <iostream>
#include <cstdio>
#include "stringmatching.hpp"

int main() {

	while (true) {
		std::string pattern, text;
		std::getline(std::cin, pattern);
		if (pattern.size() <= 0) break;
		std::getline(std::cin, text);
		if (text.size() <= 0) break;

		std::vector<int> hits = rabinkarp(pattern, text);
		for (auto& h : hits) {
			printf("%d ", h);
		}
		printf("\n");
	}
}