# 408 数据结构

多页静态站。目录与「数据结构（精美动画演示讲解）」67 节一致：线性表、树、图、查找、排序、常见题型。每节一页，含分步动画和可单独编译的 C++17 程序。

讲解按 408 考纲组织，代码是教学用的原创实现，不是教材摘录。

本地预览：

```text
python tools/build.py
python -m http.server 8765
```

浏览器打开 `http://127.0.0.1:8765/`。改 `content/` 之后要重新运行 `tools/build.py`，生成的 `index.html`、`l/`、`c/` 才会更新。

内容格式见 `SPEC.md`。继续开工见 `summary/CONTINUE.md`。
