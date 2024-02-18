#ifndef SENSOR_OBSERVER
#define SENSOR_OBSERVER

namespace Sensor {

class AbstractSensor;

class SensorObserver{
public:
    virtual void notify(const AbstractSensor& sensor) = 0;

    virtual ~SensorObserver() = default;
};

}

#endif