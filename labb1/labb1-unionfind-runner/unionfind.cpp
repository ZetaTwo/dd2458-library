#include <cstdio>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#ifdef _WIN32
inline int getchar_unlocked() { return getchar(); }
#endif

inline void inp(int *n) { //fast input function
    *n = 0;
	int ch = getchar_unlocked();
	int sign = 1;
	while(ch < '0' || ch > '9') {
		if (ch == (int)'=' || ch == (int)'?') {
			*n = ch;
			break;
		}
		ch = getchar_unlocked();
	}
	while(ch >= '0' && ch <= '9')
		(*n) = ((*n)<<3) + ((*n)<<1) + ch - '0', ch = getchar_unlocked();
	// *n = (*n)*sign; // no negative numbers in this problem
}

unordered_set<int>** sets = new unordered_set<int>*[1000001];
int* pos = new int[1000001];

int main() {
	int N, Q;
	scanf("%d %d\n", &N, &Q);

	for (int i = 0; i <= N; i++) {
		sets[i] = new unordered_set<int>({i});
		pos[i] = i;
	}

	// char c;
	int c, a, b;
	while (Q--) {
		inp(&c);
		inp(&a);
		inp(&b);
		auto seta = sets[ pos[a] ];
		auto setb = sets[ pos[b] ];
		if (c == (int)'=') {

			if (a == b || seta == setb) continue;

			if (setb->size() > seta->size()) {
				int bpos = pos[b];
				for (int x : *seta) {
					setb->insert(x);
					pos[x] = bpos;
				}

			} else { // a larger than b
				int apos = pos[a];
				for (int x : *setb) {
					seta->insert(x);
					pos[x] = apos;
				}
			}

		} else if (c == (int)'?') {

			if (a == b) {
				printf("yes\n");
				continue;
			}
			if (seta == setb)
				printf("yes\n");
			else
				printf("no\n");
		}
	}
}
