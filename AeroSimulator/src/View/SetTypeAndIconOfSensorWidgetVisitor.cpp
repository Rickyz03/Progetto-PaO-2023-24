#include "SetTypeAndIconOfSensorWidgetVisitor.h"

namespace View {

SetTypeAndIconOfSensorWidgetVisitor::SetTypeAndIconOfSensorWidgetVisitor(SensorPanel* sensorPanel) : sensorPanel(sensorPanel) {}

void SetTypeAndIconOfSensorWidgetVisitor::visit(const Sensor::DistanceCoveredSensor& distanceCoveredSensor){
    // Espediente per evitare il warning "unused parameter"
    std::string name = distanceCoveredSensor.getName();

    sensorPanel->setTypeAndIconOfSensorWidget("DistanceCoveredSensor", QIcon("Assets/Sensori/DistanceCoveredSensor.svg"));
}

void SetTypeAndIconOfSensorWidgetVisitor::visit(const Sensor::Chronometer& chronometer){
    // Espediente per evitare il warning "unused parameter"
    std::string name = chronometer.getName();

    sensorPanel->setTypeAndIconOfSensorWidget("Chronometer", QIcon("Assets/Sensori/Chronometer.svg"));
}

void SetTypeAndIconOfSensorWidgetVisitor::visit(const Sensor::SpeedSensor& speedSensor){
    // Espediente per evitare il warning "unused parameter"
    std::string name = speedSensor.getName();

    sensorPanel->setTypeAndIconOfSensorWidget("SpeedSensor", QIcon("Assets/Sensori/SpeedSensor.svg"));
}

void SetTypeAndIconOfSensorWidgetVisitor::visit(const Sensor::Accelerometer& accelerometer){
    // Espediente per evitare il warning "unused parameter"
    std::string name = accelerometer.getName();

    sensorPanel->setTypeAndIconOfSensorWidget("Accelerometer", QIcon("Assets/Sensori/Accelerometer.svg"));
}

}