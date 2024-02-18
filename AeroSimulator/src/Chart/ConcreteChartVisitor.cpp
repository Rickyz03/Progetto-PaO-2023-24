#include "ConcreteChartVisitor.h"

namespace Chart {

ConcreteChartVisitor::ConcreteChartVisitor(Histogram* histogram): histogram(histogram) {};

ConcreteChartVisitor::ConcreteChartVisitor(LineChart* lineChart): lineChart(lineChart) {};

void ConcreteChartVisitor::visit(const Sensor::DistanceCoveredSensor& distanceCoveredSensor){
    histogram->updateDataDistanceChart(distanceCoveredSensor);
}

void ConcreteChartVisitor::visit(const Sensor::Chronometer& chronometer){
    histogram->updateDataChronoChart(chronometer);
}

void ConcreteChartVisitor::visit(const Sensor::SpeedSensor& speedSensor){
    histogram->updateDataSpeedChart(speedSensor);
}

void ConcreteChartVisitor::visit(const Sensor::Accelerometer& accelerometer){
    lineChart->updateDataAccelerationChart(accelerometer);
}

}