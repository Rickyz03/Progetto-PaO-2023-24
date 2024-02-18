#include "ChartWidgetOnSelectionVisitor.h"

namespace View {

ChartWidgetOnSelectionVisitor::ChartWidgetOnSelectionVisitor(ChartWidget* chartWidget) : chartWidget(chartWidget) {}

void ChartWidgetOnSelectionVisitor::visit(const Sensor::DistanceCoveredSensor& distanceCoveredSensor){
    chartWidget->chartWidgetOnDistanceSelected(distanceCoveredSensor);
}

void ChartWidgetOnSelectionVisitor::visit(const Sensor::Chronometer& chronometer){
    chartWidget->chartWidgetOnChronoSelected(chronometer);
}

void ChartWidgetOnSelectionVisitor::visit(const Sensor::SpeedSensor& speedSensor){
    chartWidget->chartWidgetOnSpeedSelected(speedSensor);
}

void ChartWidgetOnSelectionVisitor::visit(const Sensor::Accelerometer& accelerometer){
    chartWidget->chartWidgetOnAccelerometerSelected(accelerometer);
}

}