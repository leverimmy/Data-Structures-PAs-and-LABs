此文件夹包括：

- `gen.cpp` 和 `check.cpp`

  其中 `gen.cpp` 为数据生成器的源代码，`check.cpp` 为测试脚本的源代码。

- `framework/`

  修改后的实验框架。

- `result.txt` 与 `result.md`

  `result.txt` 为未经整理过的测试结果。其中 `Case Number` 为数据点编号，`Time used` 为所用时间，`Combination` 为该次测试使用了怎样的哈希函数以及冲突解决策略的组合。具体而言：

  |              名字               |       意义       |
  | :-----------------------------: | :--------------: |
  |          `bad_hashing`          |  “坏”的哈希函数  |
  |         `good_hashing`          |  “好”的哈希函数  |
  |         `linear_probe`          |   线性试探策略   |
  | `bidirectional_quadratic_probe` | 双向平方试探策略 |
  |         `overflow_area`         |  公共溢出区策略  |

  `result.md` 为更直观的数据表格。

- `LAB2.md`

  实验报告。

- `feelings.md`

  对这道题目的感受和建议，以及估计完成题目实际使用的时间。