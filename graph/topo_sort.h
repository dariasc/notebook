#include "../template.h"
/* -
name = "topological_sort"
[info]
time = "$O(V + E)$"
- */
vec<int> topoSort(const vec<vec<int>> &gr){
  vec<int> indeg(gr.size()), ret;
  for (auto &li : gr)
    for (int x : li)
      indeg[x]++;
  queue<int> q;
  for (int i = 0; i < gr.size(); i++)
    if (indeg[i] == 0) q.push(i); 
  while (!q.empty()) {
    int i = q.front();
    ret.push_back(i);
    q.pop();
    for (int x : gr[i])
      if (--indeg[x] == 0)
        q.push(x);
  }
  return ret;
}
