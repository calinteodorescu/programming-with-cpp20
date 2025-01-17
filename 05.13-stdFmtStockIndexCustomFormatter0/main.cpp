// Copyright (c) Andreas Fertig.
// SPDX-License-Identifier: MIT

#if __has_include(<format>) and not defined(__clang__)
#  include <format>
#  include <iomanip>
#  include <iostream>
#  include <locale>
#  include <string>
#  include <vector>

class StockIndex {
  std::string mName{};
  double      mLastPoints{};
  double      mPoints{};

public:
  StockIndex(std::string name)
  : mName{name}
  {}

  const std::string& name() const { return mName; }

  void setPoints(double points)
  {
    mLastPoints = mPoints;
    mPoints     = points;
  }

  double points() const { return mPoints; }

  double pointsDiff() const { return mPoints - mLastPoints; }

  double pointsPercent() const
  {
    if(0.0 == mLastPoints) { return 0.0; }
    return (mPoints - mLastPoints) / mLastPoints * 100.0;
  }
};

std::vector<StockIndex> GetIndices()
{
  StockIndex dax{"DAX"};
  dax.setPoints(13'052.95);
  dax.setPoints(13'108.50);

  StockIndex dow{"Dow"};
  dow.setPoints(29'080.17);
  dow.setPoints(29'290.00);

  StockIndex sp{"S&P 500"};
  sp.setPoints(3'537.01);
  sp.setPoints(3'561.50);

  return {dax, dow, sp};
}

template<>
struct std::formatter<StockIndex> {
  constexpr auto parse(std::format_parse_context& ctx)
  {
    return ctx.begin();
  }

  auto format(const StockIndex& index, std::format_context& ctx)
  {
    return std::format_to(ctx.out(),
                          "{:10}  {:>8.2f}  {:>6.2f} {:.2f}%",
                          index.name(),
                          index.points(),
                          index.pointsDiff(),
                          index.pointsPercent());
  }
};

int main()
{
  for(const auto& index : GetIndices()) {
    std::cout << std::format("{}\n", index);
  }
}

#else
int main()
{
#  pragma message("not supported")
}
#endif