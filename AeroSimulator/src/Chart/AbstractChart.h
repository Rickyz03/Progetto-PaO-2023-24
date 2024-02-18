#ifndef ABSTRACT_CHART_H
#define ABSTRACT_CHART_H

#include <QtCharts>
#include <QWidget>
#include <vector>

#include "../Sensor/SensorObserver.h"

namespace Chart {

class AbstractChart : public QWidget, public Sensor::SensorObserver {
    Q_OBJECT

public:
    AbstractChart(QWidget* parent = nullptr);

    // Interfaccia per eventuali futuri metodi virtuali puri in comune tra i due grafici

    virtual ~AbstractChart() = 0;
};

}

#endif 
