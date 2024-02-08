#include "aoc/solutions/day24.hpp"

#include <Eigen/Dense>

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <utility>

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

namespace
{
  using Matrix3 = Eigen::Matrix<long double, 3, 3>;
  using Vector3 = Eigen::Vector<long double, 3>;
  using Matrix6 = Eigen::Matrix<long double, 6, 6>;
  using Vector6 = Eigen::Vector<long double, 6>;

  struct Hailstone : public std::vector<long double>
  {
    explicit Hailstone(const std::string &line)
    {
      aoc::vstring temp = aoc::parse::split_by_delimiters(line, ", @");
      this->reserve(temp.size());
      for (const auto &str : temp)
        this->emplace_back(std::stold(str));
    }
    long double x() const { return this->at(0); }
    long double y() const { return this->at(1); }
    long double z() const { return this->at(2); }
    long double vx() const { return this->at(3); }
    long double vy() const { return this->at(4); }
    long double vz() const { return this->at(5); }
  };

  std::pair<double, double> intersection(const Hailstone &p, const Hailstone &q)
  {
    double det = p[3] * q[4] - q[3] * p[4];
    if (det == 0.f) return {std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()};
    double det_inv = 1.f / det;
    double t       = det_inv * (-q[4] * (p[0] - q[0]) + q[3] * (p[1] - q[1]));
    double u       = det_inv * (-p[4] * (p[0] - q[0]) + p[3] * (p[1] - q[1]));
    if (t >= 0.f && u >= 0.f)
      return {p[0] + t * p[3], p[1] + t * p[4]};
    return {std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()};
  }

  struct Simulation
  {
    std::vector<Hailstone>    hailstones;
    std::pair<double, double> test_area;

    Simulation(const aoc::vstring &input, const std::pair<double, double> &test_area = {0, 0}) : test_area(test_area)
    {
      this->hailstones.reserve(input.size());
      for (const auto &line : input)
        this->hailstones.emplace_back(Hailstone(line));
    }

    std::size_t solve() const
    {
      std::size_t result = 0;
      for (std::size_t i = 0; i < hailstones.size() - 1; ++i)
        for (std::size_t j = i + 1; j < hailstones.size(); ++j)
        {
          std::pair<double, double> collision = intersection(this->hailstones[i], this->hailstones[j]);
          if (test_area.first <= collision.first && collision.first <= test_area.second &&
              test_area.first <= collision.second && collision.second <= test_area.second)
            result++;
        }
      return result;
    }

    Vector6 operator[](const std::size_t &index) const
    {
      Vector6 res;
      // clang-format off
      res << this->hailstones[index].x(),
             this->hailstones[index].y(),
             this->hailstones[index].z(),
             this->hailstones[index].vx(),
             this->hailstones[index].vy(),
             this->hailstones[index].vz();
      // clang-format on
      return res;
    }
  };

  Matrix3 crossMatrix(const Vector3 &v)
  {
    Matrix3 result;
    // clang-format off
    result <<    0, -v[2], v[1],
              v[2],     0, -v[0],
             -v[1],  v[0], 0;
    // clang-format on
    return result;
  }

} // namespace

std::size_t aoc::day24::part1(const std::string &filename, const double &min, const double &max)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Simulation   sim(input, {min, max});
  return sim.solve();
}

std::size_t aoc::day24::part2(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);
  Simulation   sim(input);

  Vector6 sim0 = sim[0];
  Vector6 sim1 = sim[1];
  Vector6 sim2 = sim[2];

  Matrix6 A;
  Vector6 b;

  b.segment<3>(0)     = -sim0.segment<3>(0).cross(sim0.segment<3>(3)) + sim1.segment<3>(0).cross(sim1.segment<3>(3));
  b.segment<3>(3)     = -sim0.segment<3>(0).cross(sim0.segment<3>(3)) + sim2.segment<3>(0).cross(sim2.segment<3>(3));
  A.block<3, 3>(0, 0) = crossMatrix(sim0.segment<3>(3)) - crossMatrix(sim1.segment<3>(3));
  A.block<3, 3>(3, 0) = crossMatrix(sim0.segment<3>(3)) - crossMatrix(sim2.segment<3>(3));
  A.block<3, 3>(0, 3) = -crossMatrix(sim0.segment<3>(0)) + crossMatrix(sim1.segment<3>(0));
  A.block<3, 3>(3, 3) = -crossMatrix(sim0.segment<3>(0)) + crossMatrix(sim2.segment<3>(0));

  Vector6 x = A.inverse() * b;

  long double sum = 0;
  for (std::size_t i = 0; i < 3; ++i)
    sum += x[i];
  return round(sum);
}