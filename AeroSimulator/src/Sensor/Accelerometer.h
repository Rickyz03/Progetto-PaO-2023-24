#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "SpeedSensor.h"

namespace Sensor {

class Accelerometer: public AbstractSensor{
private:
    Chronometer chronometer;
    SpeedSensor speedSensor;
    std::vector<double> data;

public:
    Accelerometer(const unsigned int& identifier, const std::string& name, const Chronometer& chronometer, const SpeedSensor& speedSensor, 
    const std::vector<double>& new_data = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0});
    Accelerometer(const Accelerometer& other);

    Chronometer getChronometer() const;
    SpeedSensor getSpeedSensor() const;
    std::vector<double> getData() const;
    void setData();

    // Ho fatto due metodi getter non const, così posso modificare il sensore annidato partendo dal sensore principale
    Chronometer& getChronometer_NON_Const();
    SpeedSensor& getSpeedSensor_NON_Const();

    Accelerometer* clone() const override;

    void accept(SensorVisitor& visitor) const final;
};

}

#endif