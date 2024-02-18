#include <iostream>
#include <typeinfo>
#include <stdexcept>
#include <vector>

#include "Accelerometer.h"

namespace Sensor {

Accelerometer::Accelerometer(const unsigned int& identifier, const std::string& name, const Chronometer& chronometer, const SpeedSensor& speedSensor, const std::vector<double>& new_data)
    : AbstractSensor(identifier, name), chronometer(chronometer), speedSensor(speedSensor) {
    for (int i = 0; i < 7; ++i) {
        data.push_back(new_data[i]);
    }
}

Accelerometer::Accelerometer(const Accelerometer& other) : AbstractSensor(other), chronometer(other.chronometer), speedSensor(other.speedSensor) {
    for (int i = 0; i < 7; ++i) {
        data.push_back(other.data[i]);
    }
}

Chronometer Accelerometer::getChronometer() const {
    return chronometer;
}

SpeedSensor Accelerometer::getSpeedSensor() const {
    return speedSensor;
}

std::vector<double> Accelerometer::getData() const {
    return data;
}

void Accelerometer::setData() {
    data.clear();
    std::vector<double> chronometerData = chronometer.getData();
    std::vector<double> speedData = speedSensor.getData();
    for (int i = 0; i < 7; ++i) {
        data.push_back(speedData[i] / chronometerData[i]);
    }

    getObserver()->notify(*this);
}

Chronometer& Accelerometer::getChronometer_NON_Const(){
    return chronometer;
}

SpeedSensor& Accelerometer::getSpeedSensor_NON_Const(){
    return speedSensor;
}

Accelerometer* Accelerometer::clone() const {
    return new Accelerometer(*this);
}

void Accelerometer::accept(SensorVisitor& visitor) const {
    visitor.visit(*this);
}

}