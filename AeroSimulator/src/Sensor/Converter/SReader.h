#ifndef SENSOR_CONVERTER_S_READER_H
#define SENSOR_CONVERTER_S_READER_H

#include <QJsonObject>

#include "../AbstractSensor.h"

namespace Sensor {
namespace Converter {

class SReader {
  public:
    virtual ~SReader() = default;
    virtual AbstractSensor* read(const QJsonObject& object) = 0;
};

}
}
#endif