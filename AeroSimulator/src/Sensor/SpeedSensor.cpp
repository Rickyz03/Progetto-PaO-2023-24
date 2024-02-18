#include <iostream>
#include <typeinfo>
#include <stdexcept>

#include "SpeedSensor.h"

namespace Sensor {

SpeedSensor::SpeedSensor(const unsigned int& identifier, const std::string& name, const DistanceCoveredSensor& distanceCoveredSensor, const Chronometer& chronometer, const std::vector<double>& new_data)
    : AbstractSensor(identifier, name), distanceCoveredSensor(distanceCoveredSensor), chronometer(chronometer) {
    for (int i = 0; i < 7; ++i) {
        data.push_back(new_data[i]);
    }
}

SpeedSensor::SpeedSensor(const SpeedSensor& other) : AbstractSensor(other), distanceCoveredSensor(other.distanceCoveredSensor), chronometer(other.chronometer) {
    for (int i = 0; i < 7; ++i) {
        data.push_back(other.data[i]);
    }
}

DistanceCoveredSensor SpeedSensor::getDistanceCoveredSensor() const {
    return distanceCoveredSensor;
}

Chronometer SpeedSensor::getChronometer() const {
    return chronometer;
}

std::vector<double> SpeedSensor::getData() const {
    return data;
}

void SpeedSensor::setData() {
    data.clear();
    std::vector<double> distanceData = distanceCoveredSensor.getData();
    std::vector<double> chronometerData = chronometer.getData();
    for (int i = 0; i < 7; ++i) {
        data.push_back(distanceData[i] / chronometerData[i]);
    }

    getObserver()->notify(*this);
}

DistanceCoveredSensor& SpeedSensor::getDistanceCoveredSensor_NON_Const(){
    return distanceCoveredSensor;
}

Chronometer& SpeedSensor::getChronometer_NON_Const(){
    return chronometer;
}

SpeedSensor* SpeedSensor::clone() const {
    return new SpeedSensor(*this);
}

void SpeedSensor::accept(SensorVisitor& visitor) const {
    visitor.visit(*this);
}

}