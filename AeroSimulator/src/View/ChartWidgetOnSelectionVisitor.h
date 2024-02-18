#ifndef CHARTWIDGETONSELECTIONVISITOR_H
#define CHARTWIDGETONSELECTIONVISITOR_H

#include "ChartWidget.h"
#include "../Sensor/Accelerometer.h"

namespace View {

class ChartWidgetOnSelectionVisitor : public Sensor::SensorVisitor {
private:
    ChartWidget* chartWidget;

public:
    ChartWidgetOnSelectionVisitor(ChartWidget* chartWidget);

    void visit(const Sensor::DistanceCoveredSensor& distanceCoveredSensor) override;
    void visit(const Sensor::Chronometer& chronometer) override;
    void visit(const Sensor::SpeedSensor& speedSensor) override;
    void visit(const Sensor::Accelerometer& accelerometer) override;
};

}

#endif
