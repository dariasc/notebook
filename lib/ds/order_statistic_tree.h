#include "../template.h"
/* -
name = "Order Statistic Tree"
[info]
time = "$O(log n)$"
- */
#include <bits/extc++.h>
using namespace __gnu_pbds;

template <class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;
