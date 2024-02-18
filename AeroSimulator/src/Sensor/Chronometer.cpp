#include <iostream>
#include <typeinfo>
#include <stdexcept>
#include <random>

#include "Chronometer.h"

namespace Sensor {

Chronometer::Chronometer(const unsigned int& identifier, const std::string& name,
    const double& min_value, const double& max_value, const double& mean, const double& variance, const double& lambda,
    const std::vector<double>& new_data)
    : AbstractSensor(identifier, name), min_value(min_value), max_value(max_value), mean(mean), variance(variance), lambda(lambda) {
    for (int i = 0; i < 7; ++i) {
        data.push_back(new_data[i]);
    }
}

Chronometer::Chronometer(const Chronometer& other) 
    : AbstractSensor(other), min_value(other.min_value), max_value(other.max_value), mean(other.mean), variance(other.variance), lambda(other.lambda) {
    for (int i = 0; i < 7; ++i) {
        data.push_back(other.data[i]);
    }
}

std::vector<double> Chronometer::getData() const {
    return data;
}

void Chronometer::setData(const std::vector<double>& new_data) {
    data.clear();
    for(double elem : new_data){
        data.push_back(elem);
    }
}

double Chronometer::getMinValue() const {
    return min_value;
}

void Chronometer::setMinValue(const double& value) {
    min_value = value;
}

double Chronometer::getMaxValue() const {
    return max_value;
}

void Chronometer::setMaxValue(const double& value) {
    max_value = value;
}

double Chronometer::getMean() const {
    return mean;
}

void Chronometer::setMean(const double& value) {
    mean = value;
}

double Chronometer::getVariance() const {
    return variance;
}

void Chronometer::setVariance(const double& value) {
    variance = value;
}

double Chronometer::getLambda() const {
    return lambda;
}

void Chronometer::setLambda(const double& value) {
    lambda = value;
}

void Chronometer::setRandomData() {
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

void Chronometer::setNormalDistributionData() {
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

void Chronometer::setUniformDistributionData() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(min_value, max_value);

    data.clear();
    for (int i = 0; i < 7; ++i) {
        data.push_back(distribution(generator));
    }

    getObserver()->notify(*this);
}

void Chronometer::setExponentialDistributionData() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::exponential_distribution<double> distribution(lambda);

    data.clear();
    for (int i = 0; i < 7; ++i) {
        data.push_back(distribution(generator));
    }

    getObserver()->notify(*this);
}

Chronometer* Chronometer::clone() const {
    return new Chronometer(*this);
}

void Chronometer::accept(SensorVisitor& visitor) const {
    visitor.visit(*this);
}

}
