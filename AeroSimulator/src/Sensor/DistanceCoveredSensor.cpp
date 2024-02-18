#include <random>
#include <iostream>
#include <typeinfo>
#include <stdexcept>

#include "DistanceCoveredSensor.h"

namespace Sensor {

DistanceCoveredSensor::DistanceCoveredSensor(const unsigned int& identifier, const std::string& name,
    const double& min_value, const double& max_value, const double& mean, const double& variance, const double& lambda,
    const std::vector<double>& new_data)
    : AbstractSensor(identifier, name), min_value(min_value), max_value(max_value), mean(mean), variance(variance), lambda(lambda) {
    for (int i = 0; i < 7; ++i) {
        data.push_back(new_data[i]);
    }
}

DistanceCoveredSensor::DistanceCoveredSensor(const DistanceCoveredSensor& other)
    : AbstractSensor(other), min_value(other.min_value), max_value(other.max_value), mean(other.mean), variance(other.variance), lambda(other.lambda) {
    for (int i = 0; i < 7; ++i) {
        data.push_back(other.data[i]);
    }
}

std::vector<double> DistanceCoveredSensor::getData() const {
    return data;
}

double DistanceCoveredSensor::getMinValue() const {
    return min_value;
}

void DistanceCoveredSensor::setMinValue(const double& value) {
    min_value = value;
}

double DistanceCoveredSensor::getMaxValue() const {
    return max_value;
}

void DistanceCoveredSensor::setMaxValue(const double& value) {
    max_value = value;
}

double DistanceCoveredSensor::getMean() const {
    return mean;
}

void DistanceCoveredSensor::setMean(const double& value) {
    mean = value;
}

double DistanceCoveredSensor::getVariance() const {
    return variance;
}

void DistanceCoveredSensor::setVariance(const double& value) {
    variance = value;
}

double DistanceCoveredSensor::getLambda() const {
    return lambda;
}

void DistanceCoveredSensor::setLambda(const double& value) {
    lambda = value;
}

void DistanceCoveredSensor::setRandomData() {
    std::random_device rd;
    std::mt19937 generator(rd());

    unsigned int min_value_int = (unsigned int) min_value;
    unsigned int max_value_int = (unsigned int) max_value;

    data.clear();
    for (int i = 0; i < 7; ++i) {
        data.push_back(generator() % (max_value_int - min_value_int + 1) + min_value_int);
    }

    getObserver()->notify(*this);
}

void DistanceCoveredSensor::setNormalDistributionData() {
    srand(time(NULL));
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<double> distribution(mean, std::sqrt(variance));

    data.clear();
    for (int i = 0; i < 7; ++i) {
        double randomValue = distribution(generator) + (rand() % ((unsigned int)max_value - (unsigned int)min_value + 1) + (unsigned int)min_value);
        double scaledValue = 0.5 * (max_value - min_value) * randomValue + 0.5 * (max_value + min_value);
        data.push_back(scaledValue/10);
    }

    getObserver()->notify(*this);
}

void DistanceCoveredSensor::setUniformDistributionData() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(min_value, max_value);

    data.clear();
    for (int i = 0; i < 7; ++i) {
        data.push_back(distribution(generator));
    }

    getObserver()->notify(*this);
}

void DistanceCoveredSensor::setExponentialDistributionData() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::exponential_distribution<double> distribution(lambda);

    data.clear();
    for (int i = 0; i < 7; ++i) {
        data.push_back(distribution(generator));
    }

    getObserver()->notify(*this);
}

DistanceCoveredSensor* DistanceCoveredSensor::clone() const {
    return new DistanceCoveredSensor(*this);
}

void DistanceCoveredSensor::accept(SensorVisitor& visitor) const {
    visitor.visit(*this);
}

}
