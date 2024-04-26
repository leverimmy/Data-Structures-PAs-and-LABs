## LAB0 报告

### 2.0 节的思考题

> 若将评测系统上这道题目的时间限制设置为 1 秒，应当准备 $n$ 最大为多少的黑盒测试数据？

应准备 $n$ 最大为 $\sqrt{\dfrac{10^8}{2 \times 10}} \approx 2 \times 10^3$ 的测试数据。

> 时间限制 1 秒不变，如果标程的程序执行 $20n\log_2n$ 条指令，又应当准备 $n$ 最大为多少的黑盒测试数据？

解方程 $20 n\log_2 n\times 10^{-8} \times 2 = 1$ 得 $n \approx 1.46 \times 10^5$。应准备 $n$ 最大为 $1 \times 10^5$ 的测试数据。

### 3.2 节要求包含在报告中的内容

> 1. 描述所有找出的 bug，及找到它们的方式。

`solution_1.cpp` 中：

```cpp
// int matrix[2000][2000];
int matrix[2005][2005];
```

通过 **静态检查** 发现，程序后面访问了 `matrix[n][m]` 等元素，所以这里应该将空间扩大。

```cpp
    // int sum = 0;
    for (int i = 1; i <= q; ++i) {
        int x, y, a, b;
        long long sum = 0; // 添加这一行
        scanf("%d %d %d %d", &x, &y, &a, &b);
        for (int j = 0; j < a; ++j) {
            for (int k = 0; k < b; ++k) {
                sum += matrix[x + j][y + k];
            }
        }
        // printf("%d\n", sum);
        printf("%lld\n", sum);
    }
```

通过 **输出调试** 发现，`sum` 的和单调递增且两次差即为正确答案。所以 `sum` 应该在每次询问时清零。

通过 **测试边界情况数据** 并使用 **调试器** 单步调试发现，`sum` 的值可能超过 `int` 的表示范围，因此改为 `long long` 存储，并修改了相应输出语句。

`solution_2.cpp` 中：

```cpp
// int matrix[2000][2000];
// int rowsum[2000][2000];

int matrix[2005][2005];
long long rowsum[2005][2005];
```

通过 **静态检查** 发现，程序后面访问了 `matrix[n][m]` 等元素，所以这里应该将空间扩大。同时，`rowsum` 中的元素大小可能会超过 `int` 的表示范围，所以将其改为 `long long`。

```cpp
    // int sum = 0;
    for (int i = 1; i <= q; ++i) {
        int x, y, a, b;
        long long sum = 0; // 添加这一行
        scanf("%d %d %d %d", &x, &y, &a, &b);
        for (int j = 0; j < a; ++j) {
            // sum += rowsum[x + j][y + b] - rowsum[x + j][y];
            sum += rowsum[x + j][y + b - 1] - rowsum[x + j][y - 1];
        }
        // printf("%d\n", sum);
        printf("%lld\n", sum);
    }
```

通过 **输出调试** 发现，`sum` 的和单调递增且两次差即为正确答案。所以 `sum` 应该在每次询问时清零。

通过 **静态检查** 发现，`sum` 每次的增加量应该为 `rowsum[x + j][y + b - 1] - rowsum[x + j][y - 1]`，这是一个范围边界取值的问题。

通过 **测试边界情况数据** 并使用 **调试器** 单步调试发现，`sum` 的值可能超过 `int` 的表示范围，因此改为 `long long` 存储，并修改了相应输出语句。

> 2. 展示如何用调试器单步执行程序（例如对于在命令行使用 gdb 给出相关命令的使用方式，对于图形化调试工具可通过截图等方式展示），并回答为了使用调试器在编译程序时需要使用什么编译选项。

设置断点：

![设置断点](https://img.picgo.net/2023/09/14/breakpoint94dad442b73f444a.png)

开始调试：

![开始调试](https://img.picgo.net/2023/09/14/starteac727a3746a4d26.png)

点击单步调试按钮：

![点击单步调试按钮前](https://img.picgo.net/2023/09/14/debugging4a7f2b76c55b17f4.png)

![点击单步调试按钮后](https://img.picgo.net/2023/09/14/next2d43bd1a9b120666.png)

如果使用命令行使用 `gdb`，则需要加上 `-g` 这个编译选项：

`g++ -g test.cpp -o test`

> 3. 回答 `rand_input.cpp` 中调用 `srand(time(0))` 的作用。

`time(0)` 返回当前的时间戳，将其作为此次程序生成随机数所用的随机数种子。

> 4. 查询相关资料，描述 `battle.cpp` 中每次调用 `system` 执行的命令的功能。

`system("g++ A.cpp -o B");` 表示使用 g++ 编译 `A.cpp` 并将可执行文件输出到 `B`。

`system("./rand_input > rand.in");` 是将 `rand_input` 这个程序产生的输出放到 `rand.in` 中。

`system("./check_input < rand.in")` 将 `rand.in` 输入到 `check_input` 程序中，由于 `check_input.cpp` 中含有 `assert()` 语句，所以当断言不成立时会返回非零值。这是用来检查 `rand.in` 的合法性。

`system("./A < B.in > C.out");` 是将 `B.in` 作为 `A` 程序的输入，并将输出放到 `C.out` 中。

`system("diff 1.out 2.out")` 是判断 `1.out` 和 `2.out` 是否相等，若不相等则返回非零值。它可以检测 `solution_1.cpp` 和 `solution_2.cpp` 对于相同的输入是否能产生相同的输出。

> 5. 回答 `main` 函数的 `argv` 的参数的首项（即 `argv[0]`） 的含义。

为命令行参数中的第一个参数，即为该程序名称。

### 4.0 节要求描述的算法思路

考虑记录矩阵前缀和 $s(a, b) = \sum_{i = 1}^{a}\sum_{j = 1}^{b}v(i, j)$。

可以使用 `solution2.cpp` 中类似的递推的思路。通过容斥原理，我们可以得到

$$
s(i, j) = 
    \begin{cases}
    s(i, j - 1) + s(i - 1, j) - s(i - 1, j - 1) + v(i, j), & i \ge 2 \land j \ge 2, \\
    s(i, j - 1) + v(i, j), & i = 1 \land j \ge 2, \\
    s(i - 1, j) + v(i, j), & i \ge 2 \land j = 1, \\
    v(i, j), & i = 1 \land j = 1.
    \end{cases}
$$

这样，对于每次询问 $(x, y, a, b)$，通过容斥原理，我们能做到 $O(1)$ 的时间进行回答

$$
\sum_{i = x}^{x + a - 1}\sum_{j = y}^{y + b - 1} = s(x + a - 1, y + b - 1) - s(x + a - 1, b - 1) - s(a - 1, y + b - 1) + s(a - 1, b - 1).
$$

### 4.1 节要求回答的问题

> 一类测试数据使得 `solution_3.cpp` 相比另外两个程序展现出明显优势。

取 $n = 1900, m = 1000, q = 10^4$。三个程序分别用时

| 程序 | 用时 |
| ------ | ------ |
| `solution_1.cpp` | 7167ms |
| `solution_2.cpp` | 2010ms |
| `solution_3.cpp` | 1193ms |

> 一类测试数据使 `solution_3.cpp` 没有明显优势。

取 $n = m = 1000, q = 100$。三个程序分别用时

| 程序 | 用时 |
| ------ | ------ |
| `solution_1.cpp` | 1045ms |
| `solution_2.cpp` | 980ms |
| `solution_3.cpp` | 978ms |

> 当测试数据满足何种条件时，`solution_3.cpp` 相比另外两个程序会展现出明显优势？

`solution_1.cpp` 的时间复杂度为 $O(nmq)$，`solution_2.cpp` 的时间复杂度最坏可达到 $O(n(m + q))$，`solution_3.cpp` 的时间复杂度为 $O(nm + q)$。当 $n, m, q$ 均较大时 `solution_3.cpp` 会展现出明显优势。