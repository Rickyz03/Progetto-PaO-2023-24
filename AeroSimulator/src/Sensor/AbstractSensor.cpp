#include "AbstractSensor.h"

namespace Sensor{

AbstractSensor::AbstractSensor(const unsigned int& identifier, const std::string& name) : identifier(identifier), name(name) {}

AbstractSensor::AbstractSensor(const AbstractSensor& other) : identifier(other.identifier), name(other.name) {}

const unsigned int& AbstractSensor::getIdentifier() const {
    return identifier;
}

std::string AbstractSensor::getName() const {
    return name;
}

void AbstractSensor::setName(const std::string& name) {
    this->name = name;
}

SensorObserver* AbstractSensor::getObserver() const {
    return observer;
}

void AbstractSensor::setObserver(SensorObserver* newObserver){
    observer = newObserver;
}

}
