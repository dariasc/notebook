#include "../template.h"
/* -
name = "Trie"
source = "https://github.com/programming-team-code/programming_team_code/blob/main/strings/trie.hpp"
[info]
- */
struct Trie {
  const int mn = 'A';
  struct Node {
    array<int, 26> next;
    bool end_of_word = 0;
    Node() { fill(begin(next), end(next), -1); }
  };
  deque<Node> t;
  Trie(): t(1) {}
  void insert(const string& s) {
    int v = 0;
    for (char ch : s) {
      int u = ch - mn;
      if (t[v].next[u] == -1) {
        t[v].next[u] = ssize(t);
        t.emplace_back();
      }
      v = t[v].next[u];
    }
    t[v].end_of_word = 1;
  }
  int find(const string& s) {
    int v = 0;
    for (char ch : s) {
      int u = ch - mn;
      if (t[v].next[u] == -1) return 0;
      v = t[v].next[u];
    }
    return t[v].end_of_word;
  }
};
