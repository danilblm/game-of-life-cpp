// Conway's Game of Life — portable C++ console implementation.
//
// A cellular automaton on a finite grid. Each cell is alive or dead and
// evolves according to Conway's classic B3/S23 rules:
//   - a dead cell with exactly 3 living neighbours becomes alive (birth);
//   - a living cell with 2 or 3 neighbours survives;
//   - in every other case the cell dies.
//
// Unlike a Windows-only version, this build relies only on the C++ standard
// library (no <windows.h> / <conio.h>) and renders with ANSI escape codes,
// so it runs on Linux, macOS and any modern Windows terminal.
//
// Build:
//   g++ -std=c++17 -O2 main.cpp -o life
//
// Usage:
//   life [width] [height] [generations] [delay_ms] [pattern]
//     pattern: "random" (default) or "glider"
//
// Examples:
//   life                       # 40x20 random, 300 generations
//   life 60 30 500 80          # 60x30 grid, 500 generations, 80 ms/frame
//   life 40 20 400 120 glider  # animate a single glider

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>

using Grid = std::vector<std::vector<bool>>;

// Count the 8 neighbours of cell (r, c). Cells outside the grid count as dead.
int countNeighbours(const Grid& g, int r, int c) {
    const int rows = static_cast<int>(g.size());
    const int cols = static_cast<int>(g[0].size());
    int alive = 0;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;
            const int nr = r + dr;
            const int nc = c + dc;
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && g[nr][nc]) {
                ++alive;
            }
        }
    }
    return alive;
}

// Compute the next generation by applying the B3/S23 rules to every cell.
Grid step(const Grid& g) {
    const int rows = static_cast<int>(g.size());
    const int cols = static_cast<int>(g[0].size());
    Grid next(rows, std::vector<bool>(cols, false));
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            const int n = countNeighbours(g, r, c);
            next[r][c] = (n == 3) || (n == 2 && g[r][c]);
        }
    }
    return next;
}

// Render the grid in place using ANSI escape codes (cursor home + redraw).
void draw(const Grid& g, int generation) {
    std::string frame = "\033[H"; // move cursor to top-left
    frame += "Conway's Game of Life  -  generation " +
             std::to_string(generation) + "\n\n";
    for (const auto& row : g) {
        for (const bool cell : row) frame += cell ? "# " : ". ";
        frame += '\n';
    }
    std::cout << frame << std::flush;
}

// Fill the grid randomly; `density` is the probability a cell starts alive.
void seedRandom(Grid& g, double density) {
    std::mt19937 rng(std::random_device{}());
    std::bernoulli_distribution alive(density);
    for (std::size_t r = 0; r < g.size(); ++r) {
        for (std::size_t c = 0; c < g[0].size(); ++c) {
            g[r][c] = alive(rng);
        }
    }
}

// Place a single glider in the top-left corner.
void seedGlider(Grid& g) {
    const int cells[5][2] = {{0, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}};
    for (const auto& cell : cells) {
        if (cell[0] < static_cast<int>(g.size()) &&
            cell[1] < static_cast<int>(g[0].size())) {
            g[cell[0]][cell[1]] = true;
        }
    }
}

int main(int argc, char** argv) {
    int width = 40;
    int height = 20;
    int generations = 300;
    int delayMs = 120;
    std::string pattern = "random";

    if (argc > 1) width = std::max(3, std::atoi(argv[1]));
    if (argc > 2) height = std::max(3, std::atoi(argv[2]));
    if (argc > 3) generations = std::max(1, std::atoi(argv[3]));
    if (argc > 4) delayMs = std::max(0, std::atoi(argv[4]));
    if (argc > 5) pattern = argv[5];

    Grid grid(height, std::vector<bool>(width, false));
    if (pattern == "glider") {
        seedGlider(grid);
    } else {
        seedRandom(grid, 0.25);
    }

    std::cout << "\033[2J"; // clear the screen once at startup
    for (int gen = 0; gen < generations; ++gen) {
        draw(grid, gen);
        grid = step(grid);
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }

    std::cout << "\nDone after " << generations << " generations.\n";
    return 0;
}
