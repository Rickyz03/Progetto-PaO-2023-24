#ifndef LINECHART_H
#define LINECHART_H

#include "AbstractChart.h"
#include "../Sensor/Accelerometer.h"

namespace Chart {

class LineChart : public AbstractChart {
    Q_OBJECT

private:
    QLineSeries* accelerationSeries;
    QLineSeries* lowerThresholdSeries;
    QLineSeries* upperThresholdSeries;
    QValueAxis* axisX;
    QValueAxis* axisY;
    QChart* chart;
    QChartView* chartView;
    QVBoxLayout* layout;

    bool isLineRed;

public:
    explicit LineChart(Sensor::Accelerometer* accelerometer = nullptr, AbstractChart* parent = nullptr);

    bool getIsLineRed() const;
    void updateDataAccelerationChart(const Sensor::Accelerometer& accelerometer);
    void notify(const Sensor::AbstractSensor& sensor) override;

    virtual ~LineChart();
};

}

#endif
