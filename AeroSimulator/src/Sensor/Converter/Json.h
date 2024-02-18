#ifndef SENSOR_CONVERTER_JSON_H
#define SENSOR_CONVERTER_JSON_H

#include "Reader.h"
#include "JsonVisitor.h"

namespace Sensor {
namespace Converter {

class Json {
  public:
    static QJsonObject fromObject(const AbstractSensor& sensor);
    static AbstractSensor& toObject(const QJsonObject& json);
    static std::vector<double> QJsonArrayToStdVector(const QJsonArray& jsonArray); // Alla fine risulta inutilizzato, lo tengo per eventuali futuri ampliamenti
    static QJsonArray StdVectorToQJsonArray(const std::vector<double>& vectorOfDouble); // Alla fine risulta inutilizzato, lo tengo per eventuali futuri ampliamenti
};

}
}
#endif