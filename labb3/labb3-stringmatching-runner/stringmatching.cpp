#include <iostream>
#include <string>
using namespace std;

const unsigned long long PRIME_BASE = 256ULL;
const unsigned long long PRIME_MOD = 72057594037927931ULL;

void rabinkarp(string needle, string hs) {
	int n = needle.size();
	long long nhash = 0, hshash = 0, pow = 1;

	for (int i = 0; i < n; i++) {
		nhash = (nhash*PRIME_BASE + needle[i]) % PRIME_MOD;
		pow = (pow * PRIME_BASE) % PRIME_MOD;
	}

	for (int i = 0; i < hs.size(); i++) {
		hshash = (hshash*PRIME_BASE + hs[i]) % PRIME_MOD; //add last letter

		//remove first character, if needed
		if (i >= n) {
			hshash -= (pow * hs[i-n]) % PRIME_MOD;
			if (hshash < 0)
				hshash += PRIME_MOD;
		}

		if (i >= n-1 && nhash == hshash) { // && needle == hs.substr(i-n+1, n) )
			printf("%d ", i-n+1);
		}
	}
}

int main() {

	while (true) {
		string pattern, text;
		getline(cin, pattern);
		if (pattern.size() <= 0) break;
		getline(cin, text);
		if (text.size() <= 0) break;

		rabinkarp(pattern, text);
		printf("\n");
	}
}