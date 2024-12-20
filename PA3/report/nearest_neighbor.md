## Nearest Neighbor 解题报告

### 算法原理

对 $d$ 维空间内的 $n$ 个点建立 K-D 树，对于每次询问，在 K-D 树上查找与给出的结点距离最近的结点。

### 细节处理

#### `nth_element` 函数的实现

在建树时，如果每次在维度上选择切割点时选择该维度上的 **中位数**，就可以保证每次分成的左右子树大小尽量相等，这样就需要我们快速得到某一维度上的中位数。而如果对当前维度进行快速排序，则单层的时间复杂度为 $O(n \log n)$，一共有 $\log n$ 层，因此建树的时间复杂度为 $O(n \log^2 n)$。

但借助快速排序的思想，我们可以得到一个期望 $O(n)$ 的得到某一维度上中位数的方法。在快速排序的过程中，我们随机选取中枢，将小于它的部分排在它的左边，大于它的部分排在它的右边。但是由于 K-D Tree **只要求中位数在排序后正确的位置上**，所以我们只需要递归地排序包含中位数的一侧。可以证明（《算法导论（第 3 版）》，9.2 节），这样实现的时间复杂度为期望 $O(n)$。

#### 查询时进行剪枝

先开始在查询操作中，对 K-D 树进行搜索的时候没有进行剪枝，导致了 TLE，于是我查找了 [相关资料](https://oi-wiki.org/ds/kdt/#%E9%82%BB%E5%9F%9F%E6%9F%A5%E8%AF%A2)。

我们可以维护一个子树中的所有结点在每一维上的坐标的 **最小值** 和 **最大值**。假设当前已经找到的最近距离是 `globalMinDist`。如果查询时，碰到一个所有点都包含在内的长方形对应的子树，发现点到该子树的最近距离已经不小于 `globalMinDist`，则在这个子树内一定没有答案。搜索时不进入这个子树，将其剪枝。

### 时空复杂度分析

#### 时间复杂度

建树的时间复杂度为 $O(n \log n)$。即使在搜索中进行剪枝，在最坏情况下单次查询的时间复杂度也为 $O(n^{1 - 1/d})$，故整体的时间复杂度为 $O(n\log n + qn^{1-1/d})$。

在 **数据均匀随机生成** 的情况下，该算法表现良好。

#### 空间复杂度

由于 K-D 树上最多只有 $n$ 个点，且每个点上最多含有 $d$ 维信息（由于本题内 $d \le 5$，故视为常数），故整体的空间复杂度为 $O(n)$。
