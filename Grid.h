#include <vector>
namespace lst {
namespace gol {
static constexpr int Live = 1;
static constexpr int Dead = 0;
class Grid {

public:
  Grid(int width, int height);
  int get_digest();
  bool empty();
  int sum() const;
  Grid evolve();
  bool set_cell(int x, int y, int value);

private:
  int width_;
  int height_;
  using DataType = std::vector<std::vector<char>>;
  DataType data_;
  int get_disget_v1();
  bool is_valid_xy(int x, int y) const;
  int get_neighbour_sum(int x, int y) const;
};
};
};