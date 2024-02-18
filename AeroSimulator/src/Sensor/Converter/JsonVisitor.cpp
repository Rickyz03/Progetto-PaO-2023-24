#include "JsonVisitor.h"
#include "../Accelerometer.h"
#include <QJsonArray>

namespace Sensor {
namespace Converter {

QJsonObject JsonVisitor::getObject() const {
    return object;
}

void JsonVisitor::visit(const Accelerometer& accelerometer) {
    QJsonObject accelerometerObject;

    accelerometerObject.insert("type", QJsonValue::fromVariant("accelerometer"));
    accelerometerObject.insert("id", QJsonValue::fromVariant(accelerometer.getIdentifier()));
    accelerometerObject.insert("name", QJsonValue::fromVariant(accelerometer.getName().c_str()));
    //accelerometerObject.insert("data", QJsonValue::fromVariant(Json::StdVectorToQJsonArray(accelerometer.getData())));
    accelerometerObject.insert("chronometer", Json::fromObject(accelerometer.getChronometer()));
    accelerometerObject.insert("speedSensor", Json::fromObject(accelerometer.getSpeedSensor()));

    object = accelerometerObject;
}

void JsonVisitor::visit(const Chronometer& chronometer) {
    QJsonObject chronometerObject;

    chronometerObject.insert("type", QJsonValue::fromVariant("chronometer"));
    chronometerObject.insert("id", QJsonValue::fromVariant(chronometer.getIdentifier()));
    chronometerObject.insert("name", QJsonValue::fromVariant(chronometer.getName().c_str()));
    //chronometerObject.insert("data", QJsonValue::fromVariant(Json::StdVectorToQJsonArray(chronometer.getData())));
    chronometerObject.insert("min_value", QJsonValue::fromVariant(chronometer.getMinValue()));
    chronometerObject.insert("max_value", QJsonValue::fromVariant(chronometer.getMaxValue()));
    chronometerObject.insert("mean", QJsonValue::fromVariant(chronometer.getMean()));
    chronometerObject.insert("variance", QJsonValue::fromVariant(chronometer.getVariance()));
    chronometerObject.insert("lambda", QJsonValue::fromVariant(chronometer.getLambda()));

    object = chronometerObject;
}

void JsonVisitor::visit(const DistanceCoveredSensor& distanceCoveredSensor) {
    QJsonObject distanceCoveredSensorObject;

    distanceCoveredSensorObject.insert("type", QJsonValue::fromVariant("distanceCoveredSensor"));
    distanceCoveredSensorObject.insert("id", QJsonValue::fromVariant(distanceCoveredSensor.getIdentifier()));
    distanceCoveredSensorObject.insert("name", QJsonValue::fromVariant(distanceCoveredSensor.getName().c_str()));
    //distanceCoveredSensorObject.insert("data", QJsonValue::fromVariant(Json::StdVectorToQJsonArray(distanceCoveredSensor.getData())));
    distanceCoveredSensorObject.insert("min_value", QJsonValue::fromVariant(distanceCoveredSensor.getMinValue()));
    distanceCoveredSensorObject.insert("max_value", QJsonValue::fromVariant(distanceCoveredSensor.getMaxValue()));
    distanceCoveredSensorObject.insert("mean", QJsonValue::fromVariant(distanceCoveredSensor.getMean()));
    distanceCoveredSensorObject.insert("variance", QJsonValue::fromVariant(distanceCoveredSensor.getVariance()));
    distanceCoveredSensorObject.insert("lambda", QJsonValue::fromVariant(distanceCoveredSensor.getLambda()));

    object = distanceCoveredSensorObject;
}

void JsonVisitor::visit(const SpeedSensor& speedSensor) {
    QJsonObject speedSensorObject;

    speedSensorObject.insert("type", QJsonValue::fromVariant("speedSensor"));
    speedSensorObject.insert("id", QJsonValue::fromVariant(speedSensor.getIdentifier()));
    speedSensorObject.insert("name", QJsonValue::fromVariant(speedSensor.getName().c_str()));
    //speedSensorObject.insert("data", QJsonValue::fromVariant(Json::StdVectorToQJsonArray(speedSensor.getData())));
    speedSensorObject.insert("distanceCoveredSensor", Json::fromObject(speedSensor.getDistanceCoveredSensor()));
    speedSensorObject.insert("chronometer", Json::fromObject(speedSensor.getChronometer()));

    object = speedSensorObject;
}

}
}
