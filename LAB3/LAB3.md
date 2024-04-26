## LAB3 报告

### Splay 树

#### 辅助函数

**判断子节点是左孩子还是右孩子**

若 $x$ 为自己父节点的左孩子，则返回 $0$；若 $x$ 为自己父节点的右孩子，则返回 $1$。

```cpp
inline int son(int x) {
    return x == ch[fa[x]][1];
}
```

**连接操作**

连接操作是为了将节点 $p$ 设置为 $f$ 的 $o$ 孩子。若 $o$ 为 $0$ 则为左孩子；若 $o$ 为 $1$ 则为右孩子。

```cpp
inline void connect(int p, int f, int o) {
    ch[f][o] = p;
    fa[p] = f;
}
```

由于上述两个辅助函数不涉及递归且代码量较小，故使用 `inline` 进行内联优化。

#### 旋转操作

通过 `connect()` 和 `son()`，我们可以方便地写出 `rotate()` 函数。它可以自适应地往另一个方向旋转节点 $p$。

![Splay-rotate](https://img.picgo.net/2023/12/04/Splay-rotate337e533e9dae03e6.png)

```cpp
// 旋转 p（及其父节点 f 之间的边）
void rotate(int p) {
    int f = fa[p], g = fa[f];
    bool o1 = son(p), o2 = son(f);
    connect(ch[p][o1 ^ 1], f, o1);
    connect(f, p, o1 ^ 1);
    connect(p, g, o2);
    pushup(f), pushup(p);
}
```

#### 伸展操作

通过 `son()` 和 `rotate()`，我们可以方便地写出 `splay()` 函数。它可以自适应地向根伸展节点 $p$。

一共有四种情况，前两种为 $p, f, g$ 共线的情况，后两种为 $p, f, g$ 不共线的情况。

1. $p, f, g$ 共线的情况

   ![Splay-f-p-1](https://img.picgo.net/2023/12/04/Splay-f-p-18ad99dbe86f075af.png)

   ![Splay-f-p-2](https://img.picgo.net/2023/12/04/Splay-f-p-2a15ab8e2a4025d6b.png)

2. $p, f, g$ 不共线的情况

   ![Splay-p-p-1](https://img.picgo.net/2023/12/04/Splay-p-p-1250bf5796bf0e651.png)

   ![Splay-p-p-2](https://img.picgo.net/2023/12/04/Splay-p-p-2e45acf9961ed8561.png)

```cpp
// 将 p 伸展至 tar
void splay(int p, int tar) {
    int tarfa = fa[tar];
    while(fa[p] != tarfa) {
        int f = fa[p], g = fa[f];
        if(tarfa != g)
            son(p) ^ son(f) ? rotate(p) : rotate(f);
        rotate(p);
    }
    if(tar == rt)
        rt = p;
}
```

#### 插入操作

以 $p$ 为根的子树中插入值为 $v$ 的节点，如果 $v > \text{dat}(p)$ ，则在右子树中插入；反之则在左子树中插入。递归处理上述两种情况即可。最后，将新插入的节点伸展至根即可。

```cpp
void insert(int v) {
    if (!rt) {
        rt = make(0, v);
        return;
    }
    int p = rt;
    while (true) {
        // 若 v > dat[p]，则在右子树中插入；反之则在左子树中
        int &nxt = ch[p][v > dat[p]];
        if (!nxt) {
            nxt = make(p, v);
            // 将新插入的节点伸展至根
            splay(nxt, rt);
            break;
        }
        p = nxt;
    }
}
```

#### 删除操作

首先找到值为 $v$ 的节点 $p$，然后将其伸展至根；其次找到 $p$ 的后继 $rs$，将其伸展至根。由于第二次伸展操作并不会改变 $p$ 的左子树，因此直接设置 $p$ 的左孩子的父节点为 $p$ 的后继 $rs$ 即可。通过这样的操作， $p$ 就被“架空”了，从而等价于将 $p$ 从平衡树中删除。

需要注意的是，如果将 $p$ 伸展至根后没有左子树或右子树，则直接将另外一个子树作为新的根即可。

```cpp
void remove(int v) {
    int p = rt;
    while (true) {
        if (dat[p] == v)
            break;
        p = ch[p][v > dat[p]];
    }
    // 将待删除节点伸展至根
    splay(p, rt);
    // 如果根没有左子树或右子树
    if (!ch[p][0] || !ch[p][1]) {
        rt = ch[p][0] + ch[p][1];
        fa[rt] = 0;
        return;
    }
    // 找到后继节点
    int rs = ch[p][1];
    while (ch[rs][0])
        rs = ch[rs][0];
    // 将 rs 伸展至根
    splay(rs, rt);
    // 设置 p 的左孩子的父节点为 rs
    connect(ch[p][0], rs, 0);
    // 设置 rs 为新的根节点
    connect(rs, 0, 1);
    // 更新 rs 相关信息
    pushup(rs);
}
```

#### 求不大于 $v$ 的最大值操作

从根节点开始，假设当前节点为 $p$，查询的值为 $v$。如果 $\text{dat}(p) \le v$，满足题意，则更新最终答案 $\text{ret} \gets \max\{\text{ret}, \text{dat}(p)\}$，并进入左子树继续寻找；否则进入右子树进行寻找。

初始化时设置 $\text{ret} \gets -1$，这样，如果树中没有满足题意的点，则 $\text{ret}$ 不会被更新，导致返回 $-1$。

```cpp
int query(int v) {
    int p = rt, ret = -1, f = 0;
    while (p) {
        // 如果 dat[p] <= v，满足题意，则可以更新答案
        if (dat[p] <= v)
            ret = std::max(ret, dat[p]);
        // 设置最近访问节点
        f = p;
        // 若 v > dat[p]，则在右子树中继续查找；反之则在左子树中
        p = ch[p][v > dat[p]];
    }
    // 将最近访问的节点（f）伸展至根
    splay(f, rt);
    return ret;
}
```

#### 时间复杂度分析

设以 $p$ 为根的子树大小为 $\text{size}(p)$，定义以 $p$ 为根的子树 $S = \text{subtree}(p)$ 拥有的势能为 $\Phi(p) = \sum\limits_{u \in \text{subtree(p)}}\log\left(\text{size}(u)\right)$。现在我们需要证明一个引理：

> 在对节点 $p$ 的伸展过程中，每一步调整所需时间均不超过以 $p$ 为根的子树 $S$ 的势能变化的 $3$ 倍，即 $3(\Phi'(p)-\Phi(p))$。

**情况 1：Zig**
$$
\begin{aligned}
t & = 1 + \Delta\Phi(f) + \Delta\Phi(p) \\
& \le 1 + \Phi'(p)-\Phi(p) \\
\end{aligned}
$$
**情况 2：Zig-Zag**
$$
\begin{aligned}
t & = 2 + \Delta\Phi \\
& = 2 + \Delta\Phi(p) + \Delta\Phi(f) + \Delta\Phi(g) \\
& = 2 + \Phi'(p) - \Phi(p) + \Phi'(f) - \Phi(f) + \Phi'(g) - \Phi(g) \\
& = 2 + \Phi'(g) + \Phi'(f) - \Phi(f) - \Phi(p) \\
& \le 2 + \Phi'(g) + \Phi'(f) - 2\Phi(p) \\
& \le 2 + 2\Phi'(p) - 2 - 2\Phi(p) \\
& \le 2(\Phi'(p)-\Phi(p))
\end{aligned}
$$
**情况 3：Zig-Zig**
$$
\begin{aligned}
t & = 2 + \Delta\Phi \\
& = 2 + \Delta\Phi(p) + \Delta\Phi(f) + \Delta\Phi(g) \\
& = 2 + \Phi'(p) - \Phi(p) + \Phi'(f) - \Phi(f) + \Phi'(g) - \Phi(g) \\
& = 2 + \Phi'(g) + \Phi'(f) - \Phi(f) - \Phi(p) \\
& \le 2 + \Phi'(g) + \Phi'(f) - 2\Phi(p) \\
& \le 2 + \Phi'(g) + \Phi'(p) - 2\Phi(p) \\
& \le 3(\Phi'(p)-\Phi(p))
\end{aligned}
$$
**Zig, Zag-Zig, Zag-Zag** 的情况与上述情况分别对称。

综合以上各种情况可知，无论具体过程如何，伸展操作的每一步至多需要 $3(\Phi'(p)-\Phi(p))$。所以，若在对 Splay 树的某次操作后，节点 $p$ 被伸展至根节点，则总体所需的分摊时间为
$$
t \le 1 + 3(\Phi(\text{root})-\Phi(p)) \le 1 + 3\Phi(\text{root}) = O(\log n)
$$

### AVL 树

#### 旋转操作

**右旋（Zig）**

![AVL-zig](https://img.picgo.net/2023/12/04/AVL-zige9278e447578b4af.png)

```cpp
// 旋转的是 p 和 p 的左孩子间的那条边
void zig(int &p) {
    int l = ch[p][0];
    ch[p][0] = ch[l][1];
    ch[l][1] = p;
    p = l;
    pushup(ch[p][1]), pushup(p);
}
```

**左旋（Zag）**

![AVL-zag](https://img.picgo.net/2023/12/04/AVL-zaga5d924e1178a1971.png)

```cpp
// 旋转的是 p 和 p 的右孩子间的那条边
void zag(int &p) {
    int r = ch[p][1];
    ch[p][1] = ch[r][0];
    ch[r][0] = p;
    p = r;
    pushup(ch[p][0]), pushup(p);
}
```

#### 检查并处理失衡情况的操作

一共有四种可能的失衡情况，对应有四种旋转处理方式，用四幅图来表示。

1. 左孩子更高，且是因为左孩子的左子树导致的

   ![AVL-check-zig](https://img.picgo.net/2023/12/04/AVL-check-zig0694bc12937211e0.png)

2. 左孩子更高，且是因为左孩子的右子树导致的

   ![AVL-check-zag-zig](https://img.picgo.net/2023/12/04/AVL-check-zag-zig3187f4963530c622.png)

3. 右孩子更高，且是因为右孩子的右子树导致的

   ![AVL-check-zag](https://img.picgo.net/2023/12/04/AVL-check-zag21776bc50e28768c.png)

4. 右孩子更高，且是因为右孩子的左子树导致的

   ![AVL-check-zig-zag](https://img.picgo.net/2023/12/04/AVL-check-zig-zagd7a22ad8feccd1e9.png)

```cpp
void check(int &p) {
    if (balance(p) > 1) {
        if (balance(ch[p][0]) > 0)
            zig(p); // 情况 1
        else
            zag(ch[p][0]), zig(p); // 情况 2
    }
    else if (balance(p) < -1) {
        if (balance(ch[p][1]) < 0)
            zag(p); // 情况 3
        else
            zig(ch[p][1]), zag(p); // 情况 4
    } else if (p)
        pushup(p);
}
```

#### 插入操作

以 $p$ 为根的子树中插入值为 $v$ 的节点，如果 $v > \text{dat}(p)$ ，则在右子树中插入；反之则在左子树中插入。递归处理上述两种情况即可。由于插入新的节点后平衡树可能会失衡，所以在回溯时需要检查并处理失衡的情况。

```cpp
void insert(int &p, int v) {
    // 如果当前节点不存在，说明需要新建节点
    if (!p) {
        p = make(v);
        return;
    }
    // 若 v > dat[p]，则在右子树中插入；反之则在左子树中
    insert(ch[p][v > dat[p]], v);
    // 回溯时检查失衡情况
    check(p);
}
```

#### 删除操作

以 $p$ 为根的子树中插入值为 $v$ 的节点，如果 $v > \text{dat}(p)$ ，则在右子树中删除；反之则在左子树中删除。递归处理上述两种情况即可。由于插入新的节点后平衡树可能会失衡，所以在回溯时需要检查并处理失衡的情况。

需要注意的是递归操作的中间情况，即 $p$ **既有左孩子又有右孩子**的情况。此时我们将 $p$ 旋转至高度较矮的孩子节点的位置，然后递归处理，直至将 $p$ 旋转到叶节点，这样我们就能方便地删除它。

```cpp
void remove(int &p, int v) {
    // 如果当前节点需要被删除
    if (v == dat[p]) {
        // 如果 p 有一子树为空，那么直接合并
        if (!ch[p][0] || !ch[p][1])
            p = ch[p][0] + ch[p][1];
        // 左边高度更高，右旋，递归处理使 p 变为叶节点
        else if (balance(p) > 0)
            zig(p), remove(ch[p][1], v);
        // 右边高度更高，左旋，递归处理使 p 变为叶节点
        else
            zag(p), remove(ch[p][0], v);
        return;
    }
    // 若 v > dat[p]，则在右子树中删除；反之则在左子树中
    remove(ch[p][v > dat[p]], v);
    // 回溯时检查失衡情况
    check(p);
}
```

#### 求不大于 $v$ 的最大值操作

具体操作与 Splay 树中的实现类似，只不过不需要维护最近访问的节点 $f$，也不需要将其伸展到根。

```cpp
int query(int v) {
    int p = rt, ret = -1;
    while (p) {
        // 如果 dat[p] <= v，满足题意，则可以更新答案
        if (dat[p] <= v)
            ret = std::max(ret, dat[p]);
        // 若 v > dat[p]，则在右子树中继续查找；反之则在左子树中
        p = ch[p][v > dat[p]];
    }
    return ret;
}
```

#### 时间复杂度分析

由于 AVL 树强制平衡，因此树高恒为 $\left\lceil\log n\right\rceil$。由于从根开始向下寻找目标最深只会到达叶节点，因此单次插入、删除、求不大于 $v$ 的最大值操作的时间复杂度均为 $O(\log n)$。

因此只需要证明单次操作引起的失衡能够在 $O(\log n)$ 的时间复杂度内解决即可。

1. 插入导致的失衡

   由 Zig-Zag 和 Zag-Zig 的示意图可知，无论单旋或双旋，经局部调整之后，不仅 $g$ 能够重获平衡，而且局部子树的高度也必将复原。 这就意味着，$g$ 以上所有祖先的平衡因子亦将统一地复原。换而言之， 在 AVL 树中插入新节点后，仅需不超过两次旋转， 即可使整树恢复平衡。

   既然原树是平衡的，故至多检查 $O(\log n)$ 个节点即可确定 $g$；如有必要，至多旋转两次，即可使局部乃至全树恢复平衡。由此可见，AVL树的节点插入操作可以在 $O(\log n)$ 时间内完成。

2. 删除导致的失衡

   节点的失衡与否仅仅取决于其左、右子树高度之差。因此反过来，只要子树的高度不变，则节点不可能失衡。

   在删除节点之后自底而上逐层核对平衡因子的过程中，一旦遇到一个失衡节点 $p$，则被删除节点必然来自 $p$ 原本更低的一棵子树，而 $p$ 的高度必然由其另一更高的子树确定，故 $p$ 的高度必然保持不变。由以上分析结论，除了 $p$ 本身，其祖先节点必然不可能失衡。

   删除最多只会导致一个节点失衡，但该节点会导致失衡传播。失衡传播的方向必然自底而上，而不致于影响到后代节点。在此过程中的任一时刻，至多只有一个失衡的节点；高层的某一节点由平衡转为失衡，只可能发生在下层失衡节点恢复平衡之后。 因此， 可沿`fa` 数组遍历所有祖先， 每找到一个失衡的祖先节点， 即可套用以上方法使之恢复平衡。

   而在删除前 AVL 树的树高为 $O(\log n)$ 级别，因此失衡的祖先节点个数为 $O(\log n)$ 级别，因此AVL 树的节点删除操作总体的时间复杂度依然是 $O(\log n)$。

### 测试数据

我利用 `check.cpp`  编译得出的程序对 Splay 树和 AVL 树进行了实验，在不同数据分布下统计了运行时间。

#### 测试数据 1

由于 Splay 会在查找后将最近访问的节点伸展至根，所以如果在某个数据分布中高频访问上一次访问过的节点（已被伸展至根），会导致 Splay 的查询效率极高。但是对于 AVL 树而言，如果高频访问同一个节点，该节点恰为叶子节点，则每次均为 $O(\log n)$ 的时间复杂度。

我设计了 $n = 10^6$ 值域为 $[1, n]$ 的测试数据。其中前 $5 \times 10^5$ 次操作均为插入操作，后 $5 \times 10^5$ 操作均为查询操作，且查询的节点为同一节点。数据生成器代码见 `gen1.cpp`。

实际结果与预期结果相同：

| 平衡树类型 | 测试用时 |
| :--------: | :------: |
|   Splay    |  1.03 s  |
|    AVL     |  1.30 s  |

#### 测试数据 2

由于 Splay 树单次操作的时间复杂度最坏可达到 $O(n)$，所以对于一个大量随机的数据集，这样的操作可能会出现很多次，所以 Splay 树的整体表现应当不如 AVL 树优秀。~~同时，我觉得我实现的 AVL 树常数比我实现的 Splay 树更小，所以肯定会跑得更快。~~

我随机生成了 $n = 10^6$，值域为 $[1, n]$ 的测试数据。我觉得这一题中生成随机数据的方法还是有些 tricky 的。在数据生成器中，我维护了一个 `std::set` 以保存此时平衡树内的值；然后，对于 `B x` 操作而言，我只会在当前 `set` 中随机寻找一个在平衡树内的值进行删除。数据生成器代码见 `gen2.cpp`。

实际结果与预期结果相同：

| 平衡树类型 | 测试用时 |
| :--------: | :------: |
|   Splay    |  2.02 s  |
|    AVL     |  1.64 s  |

#### 分析与总结

Splay 树是一种自适应平衡树，通过对最近访问的节点进行伸展，将其移动到根节点处，从而提高了对于动态数据集合的搜索效率（测试数据 1）。Splay 树的优点在于其简单易实现，但是 Splay 树的缺点在于其操作的时间复杂度不稳定，**最坏情况下** 会达到 $O(n)$，这使得它在随机状态下性能不如 AVL 树（测试数据 2）。

但是 Splay 树能够方便地维护区间，尤其是支持 **区间翻转** 操作。它也有更加广泛的应用（例如 Link-Cut Tree 和 Euler-Tour Tree）。

AVL 树则是一种强制平衡的平衡树，它通过对每个节点的左右子树高度差保持在 $1$ 以内来保证树的平衡，因此其操作的时间复杂度保持在 $O(\log n)$。AVL 树的优点在于其 **时间复杂度稳定**，具有较好的性能保证（测试数据 2）。但是由于 AVL 树需要频繁的进行旋转操作，因此其代码实现较为复杂（我觉得比 Splay 树难写多了），并且对于某些数据分布情况表现可能不如 Splay 树，例如大量查找同一个数（测试数据 1）。

在做这次实验之前，我一直以为我写的 Splay 树在随机数据下会比 AVL 树快很多。这次实验更正了我以前的不正确的想法，让我收获颇丰。

