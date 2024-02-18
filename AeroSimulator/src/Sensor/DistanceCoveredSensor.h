#ifndef DISTANCE_COVERED_SENSOR_H
#define DISTANCE_COVERED_SENSOR_H

#include "AbstractSensor.h"

namespace Sensor {

class DistanceCoveredSensor : public AbstractSensor {
private:
    std::vector<double> data;

    double min_value;
    double max_value;
    double mean;
    double variance;
    double lambda;

public:
    DistanceCoveredSensor(const unsigned int& identifier, const std::string& name,
        const double& min_value = 1.0, const double& max_value = 10.0, const double& mean = 35.0, const double& variance = 5.0, const double& lambda = 2.0,
        const std::vector<double>& new_data = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0});
    DistanceCoveredSensor(const DistanceCoveredSensor& other);

    std::vector<double> getData() const;

    double getMinValue() const;
    void setMinValue(const double& value);

    double getMaxValue() const;
    void setMaxValue(const double& value);

    double getMean() const;
    void setMean(const double& value);

    double getVariance() const;
    void setVariance(const double& value);

    double getLambda() const;
    void setLambda(const double& value);

    void setRandomData();
    void setNormalDistributionData();
    void setUniformDistributionData();
    void setExponentialDistributionData();

    DistanceCoveredSensor* clone() const override;

    void accept(SensorVisitor& visitor) const override;
};

}

#endif
