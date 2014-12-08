#ifndef __NORMAL_DISTRIBUTION_H__
#define __NORMAL_DISTRIBUTION_H__

struct NormalDistribution
{
  NormalDistribution(double stdDev, double average);
  double computeCdfVal(double x) const;
  const double standardDeviation;
  const double average;
};

#endif