#ifndef SPEED_H
#define SPEED_H

#include "DistanceCoveredSensor.h"
#include "Chronometer.h"

namespace Sensor {

class SpeedSensor: public AbstractSensor{
private:
    DistanceCoveredSensor distanceCoveredSensor;
    Chronometer chronometer;
    std::vector<double> data;

public:
    SpeedSensor(const unsigned int& identifier, const std::string& name, const DistanceCoveredSensor& distanceCoveredSensor, const Chronometer& chronometer,
    const std::vector<double>& new_data = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0});
    SpeedSensor(const SpeedSensor& other);

    DistanceCoveredSensor getDistanceCoveredSensor() const;
    Chronometer getChronometer() const;
    std::vector<double> getData() const;
    void setData();

    // Ho fatto due metodi getter non const, così posso modificare il sensore annidato partendo dal sensore principale
    DistanceCoveredSensor& getDistanceCoveredSensor_NON_Const();
    Chronometer& getChronometer_NON_Const();

    SpeedSensor* clone() const override;

    void accept(SensorVisitor& visitor) const override;
};

}

#endif