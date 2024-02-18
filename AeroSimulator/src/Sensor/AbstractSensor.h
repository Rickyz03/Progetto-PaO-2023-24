#ifndef SENSORE_H
#define SENSORE_H

#include <string>
#include <vector>

#include "SensorVisitor.h"
#include "SensorObserver.h"

namespace Sensor {

class AbstractSensor{
private:
    const unsigned int identifier;
    std::string name;
    SensorObserver* observer;

protected:
    AbstractSensor(const unsigned int& identifier, const std::string& name);
    AbstractSensor(const AbstractSensor& other);

public:
    const unsigned int& getIdentifier() const;
    std::string getName() const;
    void setName(const std::string& name);
    SensorObserver* getObserver() const;
    void setObserver(SensorObserver* newObserver);

    virtual AbstractSensor* clone() const = 0;
    virtual void accept(SensorVisitor& visitor) const = 0;

    virtual ~AbstractSensor() = default;
};

}

#endif
