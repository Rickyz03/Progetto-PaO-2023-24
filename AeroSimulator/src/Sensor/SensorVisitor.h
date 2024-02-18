#ifndef SENSOR_VISITOR_H
#define SENSOR_VISITOR_H

namespace Sensor {

class DistanceCoveredSensor;
class Chronometer;
class SpeedSensor;
class Accelerometer;

class SensorVisitor{
public:
    virtual void visit(const DistanceCoveredSensor& distanceCoveredSensor) = 0;
    virtual void visit(const Chronometer& chronometer) = 0;
    virtual void visit(const SpeedSensor& speedSensor) = 0;
    virtual void visit(const Accelerometer& accelerometer) = 0;

    virtual ~SensorVisitor() = default;
};

}

#endif