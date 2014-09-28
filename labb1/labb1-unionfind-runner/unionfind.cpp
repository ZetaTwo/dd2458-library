#include <cstdio>
using namespace std;

#include "unionfind.hpp"

#ifdef _WIN32
#define scanf scanf_s
#endif

int main() {
	int N, Q;
	scanf("%d %d\n", &N, &Q);

  UnionFind unionfind(N);

  char c;
  int a, b;
	while (Q--) {
    c = fgetc(stdin);
    scanf("%d %d\n", &a, &b);

		if (c == '=') {
      unionfind.unite(a, b);
		} else {
      if (unionfind.connected(a, b)) {
				printf("yes\n");
			} else {
        printf("no\n");
      }
		}
	}
}
