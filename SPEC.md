# 内容规格

每一节三个文件，都放在 `content/`，UTF-8 无 BOM：

- `content/<id>.cpp` 完整、可单独用 `g++ -std=c++17` 编译的程序
- `content/<id>.meta.json`
- `content/<id>.anim.json`

不要改 `catalog.json` 里的 id 和标题。不要引用教材原文，要点用自己的话写，每条不超过 40 字。

## meta.json

```json
{
  "blurb": "一句话，不超过 28 字",
  "points": ["要点1", "要点2", "要点3", "要点4"],
  "complexity": "时间与空间，写清楚最好、最坏、平均"
}
```

## C++

- 标准库头文件，禁止 `bits/stdc++.h`、`system`、`conio.h`
- 必须有 `main`，返回 0
- 动画用的那组数据，必须和 `main` 里演示的数据相同
- 中文只出现在注释里。`cout` 用 ASCII，避免编码问题
- 算法要处理空表、越界、找不到。错误用返回值或打印 `error`，不要抛给用户看的异常
- 标题里写了「代码」的节，把过程打印出来，方便对动画

## anim.json

`kind` 只能是：`array` `bars` `list` `graph` `matrix` `hash` `stack` `text`

帧数 8 到 16。每帧都有 `note`（一句中文，说明这一步眼睛该看哪）。

- array：`cells` 字符串数组，`hl` 下标数组，`done` 可选
- bars：`vals` 数字数组，`hl` 下标，`done` 已归位下标，`pivot` 一个下标或省略
- list：`nodes` 为 `{v, tag}`，`tag` 可省略或为 `new` / `cut`，`hl` 为下标。结点顺序就是链接顺序
- graph：`nodes` 为 `{id, v, x, y}`，x/y 取 0 到 1。`edges` 为 `{u, v, w, hl, dir}`，`dir:false` 表示无向。`hl` 是要点亮的结点 id
- matrix：`rows` 二维字符串，`hl` 为 `[[r,c]]`，可选 `colHead` `rowHead`
- hash：`buckets` 二维字符串，`hl` 为 `{b, i}` 或省略
- stack：`cells` 从栈底到栈顶，`top` 是栈顶下标，`out` 是已经输出的串
- text：`lines` 字符串数组，`cur` 当前行下标

动画数据要短。数组长度不超过 8，图结点不超过 7，这样手机上也不挤。
