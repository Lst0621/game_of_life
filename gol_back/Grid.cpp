#include "Grid.h"
#include <algorithm>
#include "iostream"

namespace lst::gol {

Grid::Grid(int width, int height)
    : width_(width),
      height_(height),
      data_(DataType(width, DataType::value_type(height))) {
}

int Grid::get_digest() {
    return get_digest_v1();
}

bool Grid::empty() {
    return std::all_of(data_.begin(), data_.end(), [](const auto &line) {
        return std::all_of(line.begin(), line.end(),
                           [](auto n) { return n == 0; });

    });
}

Grid Grid::evolve() {
    // todo refac
    constexpr int LiveLiveLower = 2;
    constexpr int LiveLiveHigher = 3;
    constexpr int DeadLiveLower = 3;
    constexpr int DeadLiveHigher = 3;
    Grid ret = *this;
    for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++) {
            int neighbour_sum = get_neighbour_sum(x, y);
            bool current_live = data_[x][y] == Live;
            const int lower = current_live ? LiveLiveLower : DeadLiveLower;
            const int higher = current_live ? LiveLiveHigher : DeadLiveHigher;
            ret.data_[x][y] =
                (neighbour_sum >= lower && neighbour_sum <= higher) ? Live
                                                                    : Dead;
        }
    }

    return ret;
}

int Grid::get_digest_v1() {
    constexpr int weight = 3;
    constexpr int RES = 10000007;
    int sum = 0;
    for (const auto &line : data_) {
        for (const auto &num : line) {
            sum = sum * weight + num;
            sum = sum % RES;
        }
    }
    return sum;
}

bool Grid::is_valid_xy(int x, int y) const {
    return x >= 0 && x < width_ && y >= 0 && y < height_;
}

int Grid::get_neighbour_sum(int x, int y) const {
    int sum = 0;
    for (const int dx : {-1, 0, 1}) {
        const int neighbour_x = x + dx;
        for (const int dy : {-1, 0, 1}) {
            const int neighbour_y = y + dy;
            if (dx == 0 && dy == 0) {
                continue;
            }
            if (is_valid_xy(neighbour_x, neighbour_y)) {
                sum += data_[neighbour_x][neighbour_y];
            }
        }
    }
    return sum;
}

bool Grid::set_cell(int x, int y, int value) {
    if (is_valid_xy(x, y)) {
        data_[x][y] = value;

        return true;
    } else {
        return false;
    }
}

int Grid::sum() const {
    int sum = 0;
    for (const auto &line : data_) {
        for (const auto &num : line) {
            sum += num;
        }
    }
    return sum;
}

void Grid::to_console(char ch) const {
    constexpr char Space = ' ';
    for (const auto &line : data_) {
        for (const auto &num : line) {
            std::cout << (num == Live ? ch : Space);
        }
        std::cout << '\n';
    }
    std::cout << std::flush;
    // ofs.close();
}

std::vector<Grid::CoorType> Grid::get_live_cells() const {
    std::vector<CoorType> ret;
    for (int i = 0; i < width_; i++) {
        for (int j = 0; j < height_; j++) {
            if (data_[i][j] == Live) {
                ret.push_back({i, j});
            }
        }
    }
    return ret;
}
}
