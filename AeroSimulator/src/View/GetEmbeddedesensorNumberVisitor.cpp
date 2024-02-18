#include "GetEmbeddedesensorNumberVisitor.h"

namespace View {

GetEmbeddedesensorNumberVisitor::GetEmbeddedesensorNumberVisitor(AboveChartWidget* aboveChartWidget) : aboveChartWidget(aboveChartWidget) {}

void GetEmbeddedesensorNumberVisitor::visit(const Sensor::DistanceCoveredSensor& distanceCoveredSensor){
    // Espediente per evitare il warning "unused parameter"
    std::string name = distanceCoveredSensor.getName();

    aboveChartWidget->createEmbeddedSensorsLabel(0);
}

void GetEmbeddedesensorNumberVisitor::visit(const Sensor::Chronometer& chronometer){
    // Espediente per evitare il warning "unused parameter"
    std::string name = chronometer.getName();

    aboveChartWidget->createEmbeddedSensorsLabel(0);
}

void GetEmbeddedesensorNumberVisitor::visit(const Sensor::SpeedSensor& speedSensor){
    // Espediente per evitare il warning "unused parameter"
    std::string name = speedSensor.getName();

    aboveChartWidget->createEmbeddedSensorsLabel(2);
}

void GetEmbeddedesensorNumberVisitor::visit(const Sensor::Accelerometer& accelerometer){
    // Espediente per evitare il warning "unused parameter"
    std::string name = accelerometer.getName();

    aboveChartWidget->createEmbeddedSensorsLabel(3);
}

}