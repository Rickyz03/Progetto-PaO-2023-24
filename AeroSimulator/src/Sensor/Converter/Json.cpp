#include "Json.h"
#include <QJsonArray>

namespace Sensor {
namespace Converter {

QJsonObject Json::fromObject(const AbstractSensor& sensor) {
    JsonVisitor json_visitor;
    sensor.accept(json_visitor);
    return json_visitor.getObject();
}

AbstractSensor& Json::toObject(const QJsonObject& json) {
    Reader reader;
    return *(reader.read(json));
}

std::vector<double> Json::QJsonArrayToStdVector(const QJsonArray& jsonArray) { // Alla fine risulta inutilizzato, lo tengo per eventuali futuri ampliamenti
    std::vector<double> result;
    for (const QJsonValue& value : jsonArray) {
        result.push_back(value.toDouble());
    }
    return result;
}

QJsonArray Json::StdVectorToQJsonArray(const std::vector<double>& vectorOfDouble) { // Alla fine risulta inutilizzato, lo tengo per eventuali futuri ampliamenti
    QJsonArray jsonArray;
    for (const double& value : vectorOfDouble) {
        jsonArray.append(QJsonValue::fromVariant(value));
    }
    return jsonArray;
}

}
}