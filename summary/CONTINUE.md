# 继续开工说明

这个文件夹给下一次接手用。站点已经按 67 节做完，并准备推到 GitHub Pages。

## 站点是什么

- 本地目录：`C:\Users\王奕博\.zcode\workspace\default\ds408`
- 仓库：`https://github.com/jlshdsdk/kaoyan-408-ds`
- 已上线：`https://jlshdsdk.github.io/kaoyan-408-ds/`（首页和 `l/seq-def.html` 已返回 200）
- 形式：多页静态 HTML。首页只放目录，点进 `l/<id>.html` 才加载那一节的动画和代码。单页最大约 14KB，首页约 14KB，整站 HTML 约 440KB。
- 目录来源：B 站合集「数据结构(精美动画演示讲解)」6 个分栏、67 节。标题写在 `catalog.json`，不要改 id。

## 目录怎么对应文件

| 分栏 | 节数 | id 例子 |
|---|---|---|
| 线性表 | 4 | seq-def, seq-edit, slist-create, slist-edit |
| 树 | 11 | tree-def … dsu |
| 图 | 16 | graph-def … aoe |
| 查找 | 14 | seq-search … hash |
| 排序 | 19 | insert-idea … radix-code |
| 常见题型 | 3 | expr-eval, expr-convert, order-infer |

每一节三份源文件，都在 `content/`：

- `<id>.cpp` 完整 C++17 程序
- `<id>.meta.json` 一句话、要点、复杂度
- `<id>.anim.json` 动画种类和 8 到 16 帧

`tools/build.py` 读这三份，写出 `l/<id>.html` 和 `c/<id>.cpp`。改内容后必须重新构建。

## 动画引擎

`assets/js/anim.js` 只在换步时重画，播放用一个 `setInterval`，页面隐藏就停。没有前端框架。

`kind` 可以写在整节上，也可以写在某一帧的 `kind` 字段上（后一种会盖过整节）。合法值：`array` `bars` `list` `graph` `matrix` `hash` `stack` `text`。字段说明在 `SPEC.md`。

## 已经核对过的结果

这些用例手算过，和代码一致：

- 顺序表 / 单链表的插入删除样例
- 后缀 `2 3 + 4 *` = 20
- 前序 `ABDEGCFH`、中序 `DBGEAFHC`，后序 `DGEBHFCA`
- 哈夫曼 A5 B3 C2 D7 E9，WPL = 57，前缀码 A:00 B:011 C:010 D:10 E:11
- Prim / Kruskal 总权 8，选边含 AB、BC、CD、DE（Kruskal 为 CD、AB、DE、BC）
- Dijkstra 源点 A：0, 2, 3, 4, 5
- Floyd `d[0][3] = 6`
- 拓扑序 A B C D E F
- AOE 关键路径长度 12，关键边 AB、BD、DF
- 二叉搜索树插入 8 3 10 1 6 14 4，再删 1、14、3 后中序 `4 6 8 10`
- AVL 的 LL / LR 中序 `10 20 30`
- 红黑树插入 10 20 30 15 25 再删 20，红黑性质仍成立
- B 树阶 3，插入 6 个关键字后删除不丢键
- B+ 树叶链 `5 8 10 15 20`
- 散列拉链 ASL = 1.80
- 排序主数组 `5 2 8 1 9 3` 的结果都是 `1 2 3 5 8 9`
- 基数排序 `21 15 8 32 4 27` → `4 8 15 21 27 32`

本机没有 g++ / clang / cl，所以上面是读代码和手算，不是编译运行。有编译器后可以：

```text
g++ -std=c++17 -Wall -Wextra -o nul content\<id>.cpp
```

Windows 下把 `nul` 换成一个临时 exe 再删掉。

## 已知限制

- `order-infer` 有 8 个结点，比规格里「图不超过 7 个点」多 1 个，画布上会紧一些。
- 单链表动画只画数据结点，不画头结点。代码里如果带头结点，以代码为准。
- 中文只写在注释和网页要点里，`cout` 用 ASCII。
- 不要把王道或严蔚敏的原文抄进要点。算法按考纲自己实现。

## 加一节或改一节

1. 若是新节，先在 `catalog.json` 对应分栏加 `{id, title}`。现有 67 节的 id 不要改。
2. 按 `SPEC.md` 写 `content/<id>.cpp`、`.meta.json`、`.anim.json`。
3. `python tools/build.py`，确认输出是 `pages=67 missing=0`（节数变了就改这个预期）。
4. 用浏览器打开对应的 `l/<id>.html`，点播放，看动画和代码是不是同一组数据。

## 发布

仓库还没建时：

```text
git init -b main
git add .
git commit
gh repo create jlshdsdk/kaoyan-408-ds --public --source . --remote origin --push
gh api -X POST repos/jlshdsdk/kaoyan-408-ds/pages -f build_type=workflow
```

若账号只用 classic Pages，把最后一步换成把 `main` 根目录设为 Pages 源。推完等一两分钟，打开 `https://jlshdsdk.github.io/kaoyan-408-ds/`。

本机 git：`C:\Users\王奕博\.zcode\workspace\default\tools\git\cmd\git.exe`  
本机 gh：`C:\Users\王奕博\.zcode\workspace\default\tools\bin\gh.exe`

不要改 git config。

## 还没做的事

- 用真编译器把 67 个 cpp 都编过一遍
- 把这个站加进 `https://jlshdsdk.github.io/` 的学习导航（目录用「408专业课」）
