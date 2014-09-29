// Quick Union Find implementation
// Based on: http://www.cs.princeton.edu/courses/archive/spring07/cos226/lectures/01union-find.pdf
// -----------------------------------------
// Authors: Magnus Olsson  (magolsso@kth.se)
//          Calle Svensson (carlsven@kth.se)

class UnionFind {
public:
  //Construct a union find data structure of N initially disjoint sets
  UnionFind(int N) {
    pos = new int[N];
    size = new int[N];
    for (int i = 0; i < N; i++) {
      pos[i] = i;
      size[i] = 1;
    }
  }

  ~UnionFind() {
    delete[] pos;
    delete[] size;
  }

  // Returns root of element
  int find(int p)	{
    int root = p;
    while (root != pos[root])
      root = pos[root];
    while (p != root) {
      int newp = pos[p];
      pos[p] = root;
      p = newp;
    }
    return root;
  }

  // Union the sets containing x and y
  void unite(int x, int y) {
    int i = find(x);
    int j = find(y);
    if (i == j) return;

    if (size[i] < size[j]) {
      pos[i] = j; size[j] += size[i];
    }
    else {
      pos[j] = i; size[i] += size[j];
    }
  }

  // Checks if x and y are in the same set
  bool connected(int x, int y) {
    return find(x) == find(y);
  }

private:
  int* pos;
  int* size;
};