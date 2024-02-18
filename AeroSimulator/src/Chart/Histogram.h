#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "AbstractChart.h"
#include "../Sensor/DistanceCoveredSensor.h"
#include "../Sensor/Chronometer.h"
#include "../Sensor/SpeedSensor.h"

namespace Chart {

class Histogram : public AbstractChart {
    Q_OBJECT

private:
    QBarSet* distanceSet;
    QBarSet* chronometerSet;
    QBarSet* speedSet;
    QBarSeries* barSeries;
    QBarCategoryAxis* axisX;
    QValueAxis* axisY;
    QChart* chart;
    QChartView* chartView;
    QVBoxLayout* layout;

public:
    explicit Histogram(Sensor::DistanceCoveredSensor* distanceCoveredSensor = nullptr, const unsigned int& index = 0, AbstractChart* parent = nullptr);
    explicit Histogram(Sensor::Chronometer* chronometer = nullptr, const unsigned int& index = 0, AbstractChart* parent = nullptr);
    explicit Histogram(Sensor::SpeedSensor* speedSensor = nullptr, AbstractChart* parent = nullptr);

    void updateDataDistanceChart(const Sensor::DistanceCoveredSensor& distanceCoveredSensor);
    void updateDataChronoChart(const Sensor::Chronometer& chronometer);
    void updateDataSpeedChart(const Sensor::SpeedSensor& speedSensor);

    void notify(const Sensor::AbstractSensor& sensor) override;

    virtual ~Histogram();
};

}

#endif
