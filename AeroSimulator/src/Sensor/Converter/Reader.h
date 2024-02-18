#ifndef SENSOR_READER_H
#define SENSOR_READER_H

#include <map>
#include <QJsonObject>

#include "SReader.h"
#include "Json.h"

namespace Sensor {
namespace Converter {

class Reader: public SReader {
private:
    std::map<unsigned int, AbstractSensor*> cache;

    Accelerometer* readAccelerometer(const QJsonObject& object) const;
    Chronometer* readChronometer(const QJsonObject& object) const;
    DistanceCoveredSensor* readDistanceCoveredSensor(const QJsonObject& object) const;
    SpeedSensor* readSpeedSensor(const QJsonObject& object) const;
public:
    const std::map<unsigned int, AbstractSensor*>& getCache() const;
    Reader& clear();

    AbstractSensor* read(const QJsonObject& object) override;
};

}
}

#endif
