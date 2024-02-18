#include <stdexcept>
#include <QJsonArray>
#include <iostream>

#include "Reader.h"
#include "../Accelerometer.h"

namespace Sensor {
namespace Converter {

const std::map<unsigned int, AbstractSensor*>& Reader::getCache() const {
    return cache;
}

Reader& Reader::clear() {
    cache.clear();
    return *this;
}

AbstractSensor* Reader::read(const QJsonObject& object) {
    QJsonValue type = object.value("type");
    if (type.isUndefined()) {
        throw std::invalid_argument("Missing sensor type.");
    }

    const unsigned int identifier = object.value("id").toInt();

    if (cache.count(identifier) > 0) {
        return cache[identifier];
    } 
    else if (type.toString().compare("accelerometer") == 0) {
        cache[identifier] = readAccelerometer(object);
    } 
    else if (type.toString().compare("chronometer") == 0) {
        cache[identifier] = readChronometer(object);
    } 
    else if (type.toString().compare("distanceCoveredSensor") == 0) {
        cache[identifier] = readDistanceCoveredSensor(object);
    } 
    else if (type.toString().compare("speedSensor") == 0) {
        cache[identifier] = readSpeedSensor(object);
    } 
    else {
        throw std::invalid_argument("Unknown sensor type.");
    }

    return cache[identifier];
}

Accelerometer* Reader::readAccelerometer(const QJsonObject& object) const {
    try {
        return new Accelerometer(
            object.value("id").toInt(),
            object.value("name").toString().toStdString(),
            static_cast<Chronometer&>(Json::toObject(object.value("chronometer").toObject())),
            static_cast<SpeedSensor&>(Json::toObject(object.value("speedSensor").toObject()))//,
            //Json::QJsonArrayToStdVector(object.value("data").toArray())
        );
    } catch (const std::bad_cast& e) {
        std::cerr << "Static_cast fallito! " << e.what() << std::endl;
        return nullptr;
    }
}

Chronometer* Reader::readChronometer(const QJsonObject& object) const {
    return new Chronometer(
        object.value("id").toInt(),
        object.value("name").toString().toStdString(),
        //Json::QJsonArrayToStdVector(object.value("data").toArray())
        object.value("min_value").toDouble(),
        object.value("max_value").toDouble(),
        object.value("mean").toDouble(),
        object.value("variance").toDouble(),
        object.value("lambda").toDouble()
    );
}

DistanceCoveredSensor* Reader::readDistanceCoveredSensor(const QJsonObject& object) const {
    return new DistanceCoveredSensor(
        object.value("id").toInt(),
        object.value("name").toString().toStdString(),
        //Json::QJsonArrayToStdVector(object.value("data").toArray())
        object.value("min_value").toDouble(),
        object.value("max_value").toDouble(),
        object.value("mean").toDouble(),
        object.value("variance").toDouble(),
        object.value("lambda").toDouble()
    );
}

SpeedSensor* Reader::readSpeedSensor(const QJsonObject& object) const {
    try {
        return new SpeedSensor(
            object.value("id").toInt(),
            object.value("name").toString().toStdString(),
            static_cast<DistanceCoveredSensor&>(Json::toObject(object.value("distanceCoveredSensor").toObject())),
            static_cast<Chronometer&>(Json::toObject(object.value("chronometer").toObject()))//,
            //Json::QJsonArrayToStdVector(object.value("data").toArray())
        );
    } catch (const std::bad_cast& e) {
        std::cerr << "Static_cast fallito! " << e.what() << std::endl;
        return nullptr;
    }
}

}
}
