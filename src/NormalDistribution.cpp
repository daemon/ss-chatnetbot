#include <cmath>
#include "NormalDistribution.hpp"

static const double Z_SCORE_TABLE[36] =
 {0.5000, 0.5398, 0.5793, 0.6179,
  0.6554, 0.6915, 0.7257, 0.7580,
  0.7881, 0.8159, 0.8413, 0.8643,
  0.8849, 0.9032, 0.9192, 0.9332,
  0.9452, 0.9554, 0.9641, 0.9713,
  0.9772, 0.9821, 0.9861, 0.9893,
  0.9918, 0.9938, 0.9953, 0.9965,
  0.9974, 0.9981, 0.9981, 0.9987,
  0.9990, 0.9993, 0.9995, 0.9997};

NormalDistribution::NormalDistribution(double stdDev, double _average) : standardDeviation(stdDev), average(_average)
{
}

double NormalDistribution::computeCdfVal(double value) const
{
  int z = static_cast<int>(abs((value - this->average) / this->standardDeviation) * 10);
  if (z >= 36)
    return value - this->average < 0 ? 0 : 1;
  return value - this->average < 0 ? 1 - z : z;
}