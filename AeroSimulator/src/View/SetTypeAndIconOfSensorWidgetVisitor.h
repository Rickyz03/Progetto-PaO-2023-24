#ifndef SETTYPEANDICONOFSENSORWIDGETVISITOR_H
#define SETTYPEANDICONOFSENSORWIDGETVISITOR_H

#include "SensorPanel.h"
#include "../Sensor/Accelerometer.h"

namespace View {

class SetTypeAndIconOfSensorWidgetVisitor : public Sensor::SensorVisitor {
private:
    SensorPanel* sensorPanel;

public:
    SetTypeAndIconOfSensorWidgetVisitor(SensorPanel* sensorPanel);

    void visit(const Sensor::DistanceCoveredSensor& distanceCoveredSensor) override;
    void visit(const Sensor::Chronometer& chronometer) override;
    void visit(const Sensor::SpeedSensor& speedSensor) override;
    void visit(const Sensor::Accelerometer& accelerometer) override;
};

}

#endif
