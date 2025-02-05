// count: frequency array such that count[val] = number of elements with weight "val"
// complexity: O(n*sqrt(bound)) if sum of elements is bounded.
vector<int> fastknapsack(const vector<int> &count) {
    vector<vector<int>> counts(count.size());
    for (int i = 1; i < count.size(); ++i) {
        int cur = count[i], j = i;
        for (; cur >= 3; j *= 2) {
            int carry = (cur - 1) / 2;
            for (int x = 0; x < cur - 2 * carry; ++x) {
                counts[j].push_back(j / i);
            }
            cur = carry;
        }
        for (int x = 0; x < cur; ++x) {
            counts[j].push_back(j / i);
        }
    }
    vector<int> knapsack(count.size(), 1e9); // knapsack[sum] is minimum number of elements to achieve "sum"
    knapsack[0] = 0;
    for (int i = 1; i < counts.size(); ++i) {
        for (int number: counts[i]) {
            for (int j = (int) knapsack.size() - 1 - i; j >= 0; --j) {
                knapsack[j + i] = min(knapsack[j + i], knapsack[j] + number);
            }
        }
    }
    return knapsack;
}
