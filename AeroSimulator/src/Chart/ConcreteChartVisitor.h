#ifndef CONCRETE_CHART_VISITOR
#define CONCRETE_CHART_VISITOR

#include "../Sensor/SensorVisitor.h"
#include "Histogram.h"
#include "LineChart.h"

namespace Chart {

class ConcreteChartVisitor: public Sensor::SensorVisitor {
private:
    Histogram* histogram;
    LineChart* lineChart;

public:
    ConcreteChartVisitor(Histogram* histogram);
    ConcreteChartVisitor(LineChart* lineChart);

    void visit(const Sensor::DistanceCoveredSensor& distanceCoveredSensor) override;
    void visit(const Sensor::Chronometer& chronometer) override;
    void visit(const Sensor::SpeedSensor& speedSensor) override;
    void visit(const Sensor::Accelerometer& accelerometer) override;
};

}

#endif