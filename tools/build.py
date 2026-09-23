# -*- coding: utf-8 -*-
"""把 catalog.json 和 content/ 编成多页静态站。只依赖 Python 标准库。"""
import html
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
CATALOG = json.loads((ROOT / "catalog.json").read_text(encoding="utf-8"))
CONTENT = ROOT / "content"
OUT_L = ROOT / "l"
OUT_C = ROOT / "c"


def load_json(path, default):
    if not path.exists():
        return default
    return json.loads(path.read_text(encoding="utf-8"))


def lessons():
    items = []
    n = 0
    total = sum(len(s["lessons"]) for s in CATALOG["sections"])
    for sec in CATALOG["sections"]:
        for les in sec["lessons"]:
            n += 1
            meta = load_json(CONTENT / f"{les['id']}.meta.json", {})
            anim = load_json(CONTENT / f"{les['id']}.anim.json", {"kind": "text", "frames": [{"note": "这一节的动画还没写进 content。", "lines": [les["title"]], "cur": 0}]})
            cpp_path = CONTENT / f"{les['id']}.cpp"
            cpp = cpp_path.read_text(encoding="utf-8") if cpp_path.exists() else "// 这一节的 C++ 还没写进 content。\n"
            items.append({
                "n": n,
                "total": total,
                "section": sec,
                "id": les["id"],
                "title": les["title"],
                "blurb": meta.get("blurb") or "",
                "points": meta.get("points") or [],
                "complexity": meta.get("complexity") or "",
                "anim": anim,
                "cpp": cpp,
            })
    return items


def script_json(obj):
    raw = json.dumps(obj, ensure_ascii=False, separators=(",", ":"))
    return raw.replace("<", "\\u003c")


def page(item, prev_item, next_item):
    points = "".join(f"<li>{html.escape(p)}</li>" for p in item["points"])
    prev_html = f'<a href="{prev_item["id"]}.html">上一节<br>{html.escape(prev_item["title"])}</a>' if prev_item else "<span></span>"
    next_html = f'<a href="{next_item["id"]}.html">下一节<br>{html.escape(next_item["title"])}</a>' if next_item else "<span></span>"
    return f"""<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>{html.escape(item["title"])}</title>
<link rel="stylesheet" href="../assets/css/site.css">
<link rel="icon" href="data:,">
</head>
<body>
<header class="top">
  <a class="brand" href="../index.html">408 数据结构</a>
  <span class="muted">{item["n"]} / {item["total"]}</span>
</header>
<main class="wrap lesson">
  <p class="crumb">{html.escape(item["section"]["name"])}</p>
  <h1>{html.escape(item["title"])}</h1>
  <p>{html.escape(item["blurb"])}</p>
  <div class="stage-wrap"><canvas id="stage" width="960" height="360"></canvas></div>
  <p id="note"></p>
  <div class="controls">
    <button id="prev" type="button">上一步</button>
    <button id="play" type="button">播放</button>
    <button id="next" type="button">下一步</button>
    <span id="step" class="muted"></span>
    <span class="muted">方向键也可切换</span>
  </div>
  <section class="panel">
    <h2>要点</h2>
    <ul>{points}</ul>
    <p class="muted">{html.escape(item["complexity"])}</p>
  </section>
  <section class="panel">
    <h2>完整 C++ 代码</h2>
    <p><a href="../c/{item["id"]}.cpp" download>下载 .cpp</a>
    <button id="copy" type="button">复制</button></p>
    <pre><code id="code">{html.escape(item["cpp"])}</code></pre>
  </section>
  <nav class="pager">{prev_html}{next_html}</nav>
</main>
<script>window.LESSON_ANIM={script_json(item["anim"])};</script>
<script src="../assets/js/anim.js"></script>
</body>
</html>
"""


def index(items):
    by_sec = {s["id"]: [] for s in CATALOG["sections"]}
    for it in items:
        by_sec[it["section"]["id"]].append(it)
    tabs = "".join(
        f'<a href="#{s["id"]}">{html.escape(s["name"])}</a>' for s in CATALOG["sections"]
    )
    blocks = []
    for sec in CATALOG["sections"]:
        cards = []
        for it in by_sec[sec["id"]]:
            cards.append(
                f'<a class="card" href="l/{it["id"]}.html"><div class="badge">{html.escape(sec["name"])}</div>'
                f'<div><b>{html.escape(it["title"])}</b><span>{html.escape(it["blurb"])}</span></div></a>'
            )
        blocks.append(
            f'<section class="block" id="{sec["id"]}"><h2>{html.escape(sec["name"])}</h2>'
            f'<div class="list">{"".join(cards)}</div></section>'
        )
    return f"""<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>408 数据结构</title>
<link rel="stylesheet" href="assets/css/site.css">
<link rel="icon" href="data:,">
</head>
<body>
<header class="top">
  <a class="brand" href="index.html">408 数据结构</a>
  <span class="muted">{len(items)} 节 · 多页静态站</span>
</header>
<main class="wrap">
  <p>按 408 考纲整理的数据结构教程。每节单独一页，含分步动画和可编译的 C++。代码是教学向的原创实现。</p>
  <nav class="tabs">{tabs}</nav>
  <input class="find" id="q" type="search" placeholder="筛选标题" autocomplete="off">
  {"".join(blocks)}
</main>
<script>
document.getElementById("q").addEventListener("input", function (e) {{
  var q = e.target.value.trim().toLowerCase();
  document.querySelectorAll(".card").forEach(function (el) {{
    el.classList.toggle("hidden", q && el.textContent.toLowerCase().indexOf(q) < 0);
  }});
}});
</script>
</body>
</html>
"""


def main():
    OUT_L.mkdir(exist_ok=True)
    OUT_C.mkdir(exist_ok=True)
    items = lessons()
    for i, it in enumerate(items):
        prev_item = items[i - 1] if i else None
        next_item = items[i + 1] if i + 1 < len(items) else None
        (OUT_L / f"{it['id']}.html").write_text(page(it, prev_item, next_item), encoding="utf-8")
        (OUT_C / f"{it['id']}.cpp").write_text(it["cpp"], encoding="utf-8")
    (ROOT / "index.html").write_text(index(items), encoding="utf-8")
    missing = []
    for it in items:
        cpp = CONTENT / f"{it['id']}.cpp"
        meta = CONTENT / f"{it['id']}.meta.json"
        anim = CONTENT / f"{it['id']}.anim.json"
        if not (cpp.exists() and meta.exists() and anim.exists()):
            missing.append(it["id"])
    print(f"pages={len(items)} missing={len(missing)}")
    if missing:
        print(" ".join(missing))


if __name__ == "__main__":
    main()
