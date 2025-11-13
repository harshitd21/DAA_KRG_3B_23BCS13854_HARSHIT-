const canvas = document.getElementById("mazeCanvas");
const ctx = canvas.getContext("2d");

let rows = 20, cols = 20;
let grid = [];
let weights = [];
let start = [0, 0];
let end;
let running = false;
let locked = false;
let speed = 40;
let explored = 0;

const directions = [[1,0],[-1,0],[0,1],[0,-1]];

function updateSizeLabel(val) {
  document.getElementById("sizeValue").innerText = `${val}x${val}`;
}

function generateGrid() {
  rows = parseInt(document.getElementById("sizeSlider").value);
  cols = rows;
  grid = Array.from({ length: rows }, () => Array(cols).fill(0));
  weights = Array.from({ length: rows }, () => Array(cols).fill(1));
  for (let i = 0; i < rows; i++)
    for (let j = 0; j < cols; j++)
      weights[i][j] = Math.floor(Math.random() * 9) + 1;
  end = [rows - 1, cols - 1];
  explored = 0;
  updateStats();
  drawGrid();
}

function randomWalls() {
  if (locked) return;
  for (let i = 0; i < rows; i++)
    for (let j = 0; j < cols; j++)
      grid[i][j] = Math.random() < 0.25 ? 1 : 0;
  grid[start[0]][start[1]] = 0;
  grid[end[0]][end[1]] = 0;
  drawGrid();
}

function drawGrid() {
  const cellSize = canvas.width / cols;
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < cols; j++) {
      if (i === start[0] && j === start[1]) ctx.fillStyle = "#0099ff";
      else if (i === end[0] && j === end[1]) ctx.fillStyle = "#ff0066";
      else if (grid[i][j] === 1) ctx.fillStyle = "#555";
      else ctx.fillStyle = "#222";
      ctx.fillRect(j * cellSize, i * cellSize, cellSize - 1, cellSize - 1);

      if (document.getElementById("algo").value === "dijkstra" && grid[i][j] === 0) {
        ctx.fillStyle = "#00ffcc";
        ctx.font = `${cellSize / 2.5}px Poppins`;
        ctx.textAlign = "center";
        ctx.textBaseline = "middle";
        ctx.fillText(weights[i][j], j * cellSize + cellSize / 2, i * cellSize + cellSize / 2);
      }
    }
  }
}

canvas.addEventListener("click", (e) => {
  if (running || locked) return;
  const cellSize = canvas.width / cols;
  const x = Math.floor(e.offsetY / cellSize);
  const y = Math.floor(e.offsetX / cellSize);
  if ((x === start[0] && y === start[1]) || (x === end[0] && y === end[1])) return;
  grid[x][y] = grid[x][y] ? 0 : 1;
  drawGrid();
});

document.getElementById("lockWalls").addEventListener("change", e => {
  locked = e.target.checked;
});

function sleep(ms) {
  return new Promise(res => setTimeout(res, ms));
}

function updateStats() {
  document.getElementById("explored").innerText = explored;
}

async function runAlgorithm() {
  if (running) return;
  running = true;
  speed = parseInt(document.getElementById("speed").value);
  const algo = document.getElementById("algo").value;

  const t0 = performance.now();

  if (algo === "bfs") await BFS();
  else if (algo === "dijkstra") await Dijkstra();
  else await AStar();

  const t1 = performance.now();
  const timeTaken = (t1 - t0).toFixed(2);
  document.getElementById("time").innerText = `${timeTaken} ms`;

  addToHistory(algo, timeTaken, explored);
  running = false;
}

async function BFS() {
  let q = [start];
  let visited = Array.from({ length: rows }, () => Array(cols).fill(false));
  let parent = Array.from({ length: rows }, () => Array(cols).fill(null));
  visited[start[0]][start[1]] = true;

  while (q.length) {
    let [x, y] = q.shift();
    if (x === end[0] && y === end[1]) return drawPath(parent);
    for (const [dx, dy] of directions) {
      const nx = x + dx, ny = y + dy;
      if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && !visited[nx][ny] && grid[nx][ny] === 0) {
        visited[nx][ny] = true;
        parent[nx][ny] = [x, y];
        q.push([nx, ny]);
        explored++;
        drawVisited(nx, ny);
        await sleep(speed);
      }
    }
  }
}

async function Dijkstra() {
  let dist = Array.from({ length: rows }, () => Array(cols).fill(Infinity));
  let parent = Array.from({ length: rows }, () => Array(cols).fill(null));
  dist[start[0]][start[1]] = 0;
  const pq = [[0, start]];

  while (pq.length) {
    pq.sort((a,b) => a[0] - b[0]);
    const [d, [x, y]] = pq.shift();
    if (x === end[0] && y === end[1]) return drawPath(parent);
    for (const [dx, dy] of directions) {
      const nx = x + dx, ny = y + dy;
      if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && grid[nx][ny] === 0) {
        const newDist = d + weights[nx][ny];
        if (newDist < dist[nx][ny]) {
          dist[nx][ny] = newDist;
          parent[nx][ny] = [x, y];
          pq.push([newDist, [nx, ny]]);
          explored++;
          drawVisited(nx, ny);
          await sleep(speed);
        }
      }
    }
  }
}

async function AStar() {
  const h = (x, y) => Math.abs(x - end[0]) + Math.abs(y - end[1]);
  let g = Array.from({ length: rows }, () => Array(cols).fill(Infinity));
  let parent = Array.from({ length: rows }, () => Array(cols).fill(null));
  g[start[0]][start[1]] = 0;
  const pq = [[h(start[0], start[1]), start]];

  while (pq.length) {
    pq.sort((a,b) => a[0] - b[0]);
    const [f, [x, y]] = pq.shift();
    if (x === end[0] && y === end[1]) return drawPath(parent);
    for (const [dx, dy] of directions) {
      const nx = x + dx, ny = y + dy;
      if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && grid[nx][ny] === 0) {
        const newG = g[x][y] + 1;
        if (newG < g[nx][ny]) {
          g[nx][ny] = newG;
          parent[nx][ny] = [x, y];
          pq.push([newG + h(nx, ny), [nx, ny]]);
          explored++;
          drawVisited(nx, ny);
          await sleep(speed);
        }
      }
    }
  }
}

function drawVisited(x, y) {
  const cellSize = canvas.width / cols;
  ctx.fillStyle = "#ffff33";
  ctx.fillRect(y * cellSize, x * cellSize, cellSize - 1, cellSize - 1);
  updateStats();
}

function drawPath(parent) {
  const cellSize = canvas.width / cols;
  let [x, y] = end;
  while (parent[x][y]) {
    const [px, py] = parent[x][y];
    ctx.fillStyle = "#00ff99";
    ctx.fillRect(y * cellSize, x * cellSize, cellSize - 1, cellSize - 1);
    [x, y] = [px, py];
  }
}

function resetGrid() {
  if (!locked) generateGrid();
  explored = 0;
  updateStats();
  drawGrid();
}

const historyList = document.getElementById("historyList");
const runHistory = [];

function addToHistory(algo, time, explored) {
  const entry = `${algo.toUpperCase()} - ${time} ms | Explored: ${explored}`;
  runHistory.unshift(entry);
  if (runHistory.length > 4) runHistory.pop();
  renderHistory();
}

function renderHistory() {
  historyList.innerHTML = runHistory.map(item => `<li>${item}</li>`).join('');
}

generateGrid();
