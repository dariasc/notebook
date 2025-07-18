/* -
name = "Binary Search"
[info]
description = "Returns first $x in [\"lo\", \"hi\")$ that is false. `lo` and `hi` must be of the same type or there is weird behaviour."
- */
ll res = *ranges::partition_point(views::iota(lo, hi),
  [&](ll x) -> bool { return x < 0; });
