(function () {
  const canvas = document.getElementById("stage");
  const data = window.LESSON_ANIM;
  if (!canvas || !data || !data.frames || !data.frames.length) return;
  const ctx = canvas.getContext("2d");
  const note = document.getElementById("note");
  const stepEl = document.getElementById("step");
  const playBtn = document.getElementById("play");
  let i = 0;
  let timer = null;
  const dpr = Math.min(window.devicePixelRatio || 1, 2);
  const font = '15px system-ui, "Segoe UI", "Microsoft YaHei", sans-serif';

  function resize() {
    const w = canvas.clientWidth || 640;
    const h = canvas.clientHeight || 360;
    canvas.width = Math.round(w * dpr);
    canvas.height = Math.round(h * dpr);
    ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
    draw();
  }

  function frame() { return data.frames[i]; }

  function draw() {
    const w = canvas.clientWidth || 640;
    const h = canvas.clientHeight || 360;
    ctx.clearRect(0, 0, w, h);
    ctx.fillStyle = "#0f172a";
    ctx.fillRect(0, 0, w, h);
    ctx.font = font;
    ctx.textBaseline = "middle";
    const f = frame();
    if (note) note.textContent = f.note || "";
    if (stepEl) stepEl.textContent = (i + 1) + " / " + data.frames.length;
    const kind = f.kind || data.kind;
    if (kind === "array") drawArray(f, w, h);
    else if (kind === "bars") drawBars(f, w, h);
    else if (kind === "list") drawList(f, w, h);
    else if (kind === "graph") drawGraph(f, w, h);
    else if (kind === "matrix") drawMatrix(f, w, h);
    else if (kind === "hash") drawHash(f, w, h);
    else if (kind === "stack") drawStack(f, w, h);
    else drawText(f, w, h);
  }

  function roundRect(x, y, w, h, r) {
    ctx.beginPath();
    ctx.moveTo(x + r, y);
    ctx.arcTo(x + w, y, x + w, y + h, r);
    ctx.arcTo(x + w, y + h, x, y + h, r);
    ctx.arcTo(x, y + h, x, y, r);
    ctx.arcTo(x, y, x + w, y, r);
    ctx.closePath();
  }

  function fillText(text, x, y, color) {
    ctx.fillStyle = color || "#e2e8f0";
    ctx.textAlign = "center";
    ctx.fillText(String(text), x, y);
  }

  function has(arr, v) { return Array.isArray(arr) && arr.indexOf(v) >= 0; }

  function drawArray(f, w, h) {
    const cells = f.cells || [];
    const n = Math.max(cells.length, 1);
    const gap = 8;
    const bw = Math.min(72, (w - 40 - gap * (n - 1)) / n);
    const total = n * bw + (n - 1) * gap;
    let x = (w - total) / 2;
    const y = h / 2 - 28;
    cells.forEach(function (c, idx) {
      const on = has(f.hl, idx);
      const done = has(f.done, idx);
      ctx.fillStyle = on ? "#f59e0b" : done ? "#166534" : "#1e293b";
      ctx.strokeStyle = on ? "#fde68a" : "#334155";
      roundRect(x, y, bw, 52, 8);
      ctx.fill();
      ctx.stroke();
      fillText(c, x + bw / 2, y + 26, on ? "#111827" : "#e2e8f0");
      fillText(idx, x + bw / 2, y + 70, "#94a3b8");
      x += bw + gap;
    });
  }

  function drawBars(f, w, h) {
    const vals = f.vals || [];
    const n = Math.max(vals.length, 1);
    const max = Math.max.apply(null, vals.concat([1]));
    const gap = 8;
    const bw = Math.min(56, (w - 40 - gap * (n - 1)) / n);
    const total = n * bw + (n - 1) * gap;
    let x = (w - total) / 2;
    vals.forEach(function (v, idx) {
      const bh = Math.max(8, (h - 90) * (v / max));
      const y = h - 36 - bh;
      const on = has(f.hl, idx) || f.pivot === idx;
      const done = has(f.done, idx);
      ctx.fillStyle = f.pivot === idx ? "#38bdf8" : on ? "#f59e0b" : done ? "#22c55e" : "#334155";
      roundRect(x, y, bw, bh, 6);
      ctx.fill();
      fillText(v, x + bw / 2, y - 14, "#e2e8f0");
      x += bw + gap;
    });
  }

  function drawList(f, w, h) {
    const nodes = f.nodes || [];
    const n = Math.max(nodes.length, 1);
    const bw = 64;
    const gap = 36;
    const total = n * bw + (n - 1) * gap;
    let x = Math.max(24, (w - total) / 2);
    const y = h / 2 - 24;
    nodes.forEach(function (node, idx) {
      const on = has(f.hl, idx);
      ctx.fillStyle = node.tag === "new" ? "#4c1d95" : on ? "#f59e0b" : "#1e293b";
      ctx.strokeStyle = node.tag === "cut" ? "#fb7185" : on ? "#fde68a" : "#334155";
      ctx.setLineDash(node.tag === "cut" ? [4, 3] : []);
      roundRect(x, y, bw, 48, 8);
      ctx.fill();
      ctx.stroke();
      ctx.setLineDash([]);
      fillText(node.v, x + bw / 2, y + 24, on ? "#111827" : "#e2e8f0");
      if (idx < nodes.length - 1) {
        arrow(x + bw, y + 24, x + bw + gap, y + 24, "#94a3b8");
      } else {
        fillText("∅", x + bw + 22, y + 24, "#94a3b8");
      }
      x += bw + gap;
    });
  }

  function arrow(x1, y1, x2, y2, color) {
    const ang = Math.atan2(y2 - y1, x2 - x1);
    const len = Math.hypot(x2 - x1, y2 - y1);
    if (len < 8) return;
    ctx.strokeStyle = color;
    ctx.fillStyle = color;
    ctx.lineWidth = 1.6;
    ctx.beginPath();
    ctx.moveTo(x1, y1);
    ctx.lineTo(x2, y2);
    ctx.stroke();
    ctx.beginPath();
    ctx.moveTo(x2, y2);
    ctx.lineTo(x2 - 8 * Math.cos(ang - 0.4), y2 - 8 * Math.sin(ang - 0.4));
    ctx.lineTo(x2 - 8 * Math.cos(ang + 0.4), y2 - 8 * Math.sin(ang + 0.4));
    ctx.closePath();
    ctx.fill();
  }

  function drawGraph(f, w, h) {
    const nodes = f.nodes || [];
    const byId = {};
    nodes.forEach(function (n) { byId[n.id] = n; });
    (f.edges || []).forEach(function (e) {
      const a = byId[e.u];
      const b = byId[e.v];
      if (!a || !b) return;
      const x1 = a.x * w, y1 = a.y * h, x2 = b.x * w, y2 = b.y * h;
      const color = e.hl ? "#f59e0b" : "#64748b";
      if (e.dir === false) {
        ctx.strokeStyle = color;
        ctx.beginPath();
        ctx.moveTo(x1, y1);
        ctx.lineTo(x2, y2);
        ctx.stroke();
      } else {
        arrow(x1, y1, x2, y2, color);
      }
      if (e.w !== undefined && e.w !== "") {
        fillText(e.w, (x1 + x2) / 2, (y1 + y2) / 2 - 12, "#fde68a");
      }
    });
    nodes.forEach(function (n) {
      const x = n.x * w, y = n.y * h;
      const on = has(f.hl, n.id);
      ctx.beginPath();
      ctx.arc(x, y, 18, 0, Math.PI * 2);
      ctx.fillStyle = on ? "#f59e0b" : "#1e293b";
      ctx.fill();
      ctx.strokeStyle = on ? "#fde68a" : "#94a3b8";
      ctx.stroke();
      fillText(n.v, x, y, on ? "#111827" : "#e2e8f0");
    });
  }

  function drawMatrix(f, w, h) {
    const rows = f.rows || [];
    const R = rows.length || 1;
    const C = (rows[0] || []).length || 1;
    const headC = f.colHead ? 1 : 0;
    const headR = f.rowHead ? 1 : 0;
    const cw = Math.min(48, (w - 30) / (C + headC));
    const ch = Math.min(36, (h - 30) / (R + headR));
    const ox = (w - cw * (C + headC)) / 2;
    const oy = (h - ch * (R + headR)) / 2;
    if (f.colHead) {
      f.colHead.forEach(function (name, c) {
        fillText(name, ox + (c + headR) * cw + cw / 2, oy + ch / 2, "#94a3b8");
      });
    }
    rows.forEach(function (row, r) {
      if (f.rowHead) fillText(f.rowHead[r], ox + cw / 2, oy + (r + headC) * ch + ch / 2, "#94a3b8");
      row.forEach(function (cell, c) {
        const x = ox + (c + headR) * cw;
        const y = oy + (r + headC) * ch;
        const on = (f.hl || []).some(function (p) { return p[0] === r && p[1] === c; });
        ctx.fillStyle = on ? "#f59e0b" : "#1e293b";
        ctx.fillRect(x + 2, y + 2, cw - 4, ch - 4);
        fillText(cell, x + cw / 2, y + ch / 2, on ? "#111827" : "#e2e8f0");
      });
    });
  }

  function drawHash(f, w, h) {
    const buckets = f.buckets || [];
    const n = Math.max(buckets.length, 1);
    const col = Math.min(110, (w - 20) / n);
    buckets.forEach(function (chain, b) {
      const x = 16 + b * col;
      fillText("[" + b + "]", x + 36, 28, "#94a3b8");
      (chain || []).forEach(function (val, k) {
        const y = 48 + k * 40;
        const on = f.hl && f.hl.b === b && f.hl.i === k;
        ctx.fillStyle = on ? "#f59e0b" : "#1e293b";
        roundRect(x, y, 72, 32, 6);
        ctx.fill();
        fillText(val, x + 36, y + 16, on ? "#111827" : "#e2e8f0");
      });
    });
  }

  function drawStack(f, w, h) {
    const cells = f.cells || [];
    const bw = 88;
    const bh = 36;
    const x = w * 0.32;
    let y = h - 48;
    cells.forEach(function (c, idx) {
      const on = idx === f.top;
      ctx.fillStyle = on ? "#f59e0b" : "#1e293b";
      roundRect(x, y, bw, bh, 6);
      ctx.fill();
      ctx.strokeStyle = "#334155";
      ctx.stroke();
      fillText(c, x + bw / 2, y + bh / 2, on ? "#111827" : "#e2e8f0");
      y -= bh + 6;
    });
    fillText("栈", x + bw / 2, h - 18, "#94a3b8");
    fillText("输出  " + (f.out || ""), w * 0.72, h / 2, "#e2e8f0");
  }

  function drawText(f, w, h) {
    const lines = f.lines || [];
    ctx.textAlign = "left";
    lines.forEach(function (line, idx) {
      ctx.fillStyle = idx === f.cur ? "#fde68a" : "#e2e8f0";
      ctx.fillText(line, 28, 40 + idx * 28);
    });
  }

  function stop() {
    if (timer) clearInterval(timer);
    timer = null;
    if (playBtn) playBtn.textContent = "播放";
  }

  function go(n) {
    i = Math.max(0, Math.min(data.frames.length - 1, n));
    draw();
  }

  document.getElementById("prev").addEventListener("click", function () { stop(); go(i - 1); });
  document.getElementById("next").addEventListener("click", function () { stop(); go(i + 1); });
  playBtn.addEventListener("click", function () {
    if (timer) { stop(); return; }
    if (i >= data.frames.length - 1) i = 0;
    playBtn.textContent = "暂停";
    timer = setInterval(function () {
      if (i >= data.frames.length - 1) { stop(); return; }
      go(i + 1);
    }, 850);
  });
  document.addEventListener("keydown", function (e) {
    if (e.key === "ArrowLeft") go(i - 1);
    if (e.key === "ArrowRight") go(i + 1);
  });
  document.addEventListener("visibilitychange", function () {
    if (document.hidden) stop();
  });

  const code = document.getElementById("code");
  const copy = document.getElementById("copy");
  if (copy && code) {
    copy.addEventListener("click", function () {
      const text = code.textContent || "";
      if (navigator.clipboard) navigator.clipboard.writeText(text);
      copy.textContent = "已复制";
      setTimeout(function () { copy.textContent = "复制"; }, 1200);
    });
  }
  if (code) colorize(code);

  function colorize(el) {
    const src = el.textContent;
    const keys = {
      int: 1, void: 1, if: 1, else: 1, for: 1, while: 1, return: 1, class: 1,
      struct: 1, const: 1, bool: 1, true: 1, false: 1, nullptr: 1, new: 1,
      delete: 1, public: 1, private: 1, template: 1, typename: 1, using: 1,
      namespace: 1, include: 1, define: 1, break: 1, continue: 1, switch: 1,
      case: 1, default: 1, sizeof: 1, auto: 1, static: 1
    };
    let html = "";
    let i0 = 0;
    while (i0 < src.length) {
      if (src[i0] === "/" && src[i0 + 1] === "/") {
        const j = src.indexOf("\n", i0);
        const end = j < 0 ? src.length : j;
        html += '<span class="cm">' + escape(src.slice(i0, end)) + "</span>";
        i0 = end;
        continue;
      }
      if (src[i0] === '"') {
        let j = i0 + 1;
        while (j < src.length && src[j] !== '"') {
          if (src[j] === "\\") j++;
          j++;
        }
        html += '<span class="st">' + escape(src.slice(i0, Math.min(src.length, j + 1))) + "</span>";
        i0 = j + 1;
        continue;
      }
      if (/[A-Za-z_]/.test(src[i0])) {
        let j = i0 + 1;
        while (j < src.length && /[A-Za-z0-9_]/.test(src[j])) j++;
        const word = src.slice(i0, j);
        html += keys[word] ? '<span class="kw">' + word + "</span>" : escape(word);
        i0 = j;
        continue;
      }
      html += escape(src[i0]);
      i0++;
    }
    el.innerHTML = html;
  }

  function escape(s) {
    return s.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;");
  }

  window.addEventListener("resize", resize);
  resize();
})();
