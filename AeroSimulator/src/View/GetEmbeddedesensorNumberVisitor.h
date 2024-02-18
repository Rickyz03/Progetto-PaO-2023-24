#ifndef GETEMBEDDEDESENSORNUMBERVISITOR_H
#define GETEMBEDDEDESENSORNUMBERVISITOR_H

#include "AboveChartWidget.h"
#include "../Sensor/Accelerometer.h"

namespace View {

class GetEmbeddedesensorNumberVisitor : public Sensor::SensorVisitor {
private:
    AboveChartWidget* aboveChartWidget;

public:
    GetEmbeddedesensorNumberVisitor(AboveChartWidget* aboveChartWidget);

    void visit(const Sensor::DistanceCoveredSensor& distanceCoveredSensor) override;
    void visit(const Sensor::Chronometer& chronometer) override;
    void visit(const Sensor::SpeedSensor& speedSensor) override;
    void visit(const Sensor::Accelerometer& accelerometer) override;
};

}

#endif
