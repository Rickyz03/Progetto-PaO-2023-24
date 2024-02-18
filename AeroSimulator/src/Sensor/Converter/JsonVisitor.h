#ifndef SENSOR_JSON_VISITOR_H
#define SENSOR_JSON_VISITOR_H

#include <QJsonObject>

#include "../AbstractSensor.h"
#include "Json.h"

namespace Sensor {
namespace Converter {

class JsonVisitor: public SensorVisitor {
private:
    QJsonObject object;

public:
    QJsonObject getObject() const;

    void visit(const Accelerometer& accelerometer);
    void visit(const Chronometer& chronometer);
    void visit(const DistanceCoveredSensor& distanceCoveredSensor);
    void visit(const SpeedSensor& speedSensor);
};

}
}

#endif
