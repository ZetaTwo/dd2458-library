// KTH DD2458 popuph14
// authors: magolsso@kth.se
//          carlsven@kth.se

#include <string>
#include <vector>

const unsigned long long PRIME_BASE = 256ULL;
const unsigned long long PRIME_MOD = 72057594037927931ULL;

// implementation of the linear time rabin-karp string searching algorithm
std::vector<int> rabinkarp(std::string needle, std::string hs) {
	std::vector<int> hits;
	int n = needle.size();
	long long nhash = 0, hshash = 0, pow = 1;

	// calculate needle hash
	for (int i = 0; i < n; i++) {
		nhash = (nhash * PRIME_BASE + needle[i]) % PRIME_MOD;
		pow = (pow * PRIME_BASE) % PRIME_MOD;
	}

	// perform rolling hash across the text
	for (int i = 0; i < hs.size(); i++) {
		hshash = (hshash*PRIME_BASE + hs[i]) % PRIME_MOD; //add last letter

		//remove first character, if needed
		if (i >= n) {
			hshash -= (pow * hs[i-n]) % PRIME_MOD;
			if (hshash < 0)
				hshash += PRIME_MOD;
		}

		// hashes match
		if (i >= n-1 && nhash == hshash) { // && needle == hs.substr(i-n+1, n) ) // should check but wasn't necessary
			hits.push_back(i-n+1);
		}
	}
	return hits;
}