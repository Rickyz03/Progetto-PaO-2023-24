#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <vector>

#include "../Chart/Histogram.h"
#include "../Chart/LineChart.h"
#include "../Sensor/AbstractSensor.h"

namespace View {

class ChartWidget : public QWidget {
    Q_OBJECT

private:
    QVBoxLayout* verticalLayout;
    QGridLayout* gridLayout;

    QFrame* greyPanel1;
    QFrame* greyPanel2;
    QFrame* greyPanel3;
    QFrame* greyPanel4;

    Chart::Histogram* distanceHistogram;
    Chart::Histogram* timeHistogram;
    QComboBox* leftComboBox;
    QComboBox* rightComboBox;
    Chart::Histogram* speedHistogram;
    Chart::LineChart* accelerationLineChart;

signals:
    void accelerationLineColor(const Sensor::Accelerometer& accelerometer, const bool& isLineRed);

public:
    explicit ChartWidget(QWidget *parent = nullptr);

    void initialChartWidget();
    void chartWidgetOnSelection(Sensor::AbstractSensor* sensor);

    void chartWidgetOnDistanceSelected(const Sensor::DistanceCoveredSensor& distanceCoveredSensor);
    void chartWidgetOnChronoSelected(const Sensor::Chronometer& chronometer);
    void chartWidgetOnSpeedSelected(const Sensor::SpeedSensor& speedSensor);
    void chartWidgetOnAccelerometerSelected(const Sensor::Accelerometer& accelerometer);

    void insertDistanceChart(Sensor::DistanceCoveredSensor* distanceCoveredSensor);
    void insertChronoChart(Sensor::Chronometer* chronometer);
    void insertSpeedChart(Sensor::SpeedSensor* speedSensor);
    void insertAccelerationChart(Sensor::Accelerometer* accelerometer);

    void theAccelerationLineIs(const Sensor::Accelerometer& accelerometer, const bool& isLineRed);

    ~ChartWidget();
};

}

#endif 
