#ifndef SENSOR_REPOSITORY_H
#define SENSOR_REPOSITORY_H

#include <vector>

#include "../AbstractSensor.h"

namespace Sensor {
namespace Repository {

class SRepository { 
public:
    virtual void create(AbstractSensor* sensor) = 0;
    virtual AbstractSensor* read(const unsigned int identifier) const = 0;
    virtual void update(AbstractSensor* sensor) = 0;
    virtual void remove(const unsigned int identifier) = 0;
    virtual std::vector<AbstractSensor*> readAll() const = 0;
    virtual void overwrite(const std::vector<Sensor::AbstractSensor*> newSensors) = 0;

    virtual ~SRepository() = default;
};

}
}

#endif
