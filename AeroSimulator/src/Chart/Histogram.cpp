#include "Histogram.h"

#include "ConcreteChartVisitor.h"

namespace Chart{

Histogram::Histogram(Sensor::DistanceCoveredSensor* distanceCoveredSensor, const unsigned int& index, AbstractChart* parent) : AbstractChart(parent), 
                    distanceSet(nullptr), chronometerSet(nullptr), speedSet(nullptr), barSeries(nullptr), axisX(nullptr), axisY(nullptr), chart(nullptr), 
                    chartView(nullptr), layout(nullptr){
    setFixedSize(345, 183);
    
    if(distanceCoveredSensor){
        distanceCoveredSensor->setObserver(this);

        // A seconda di quale index arriva dal segnale della QComboBox, chiama il corretto metodo di set dei dati di distanceCoveredSensor
        if(index == 0)
            distanceCoveredSensor->setRandomData();
        else if(index == 1)
            distanceCoveredSensor->setNormalDistributionData();
        else if(index == 2)
            distanceCoveredSensor->setUniformDistributionData();
        else
            distanceCoveredSensor->setExponentialDistributionData();
    }
}

Histogram::Histogram(Sensor::Chronometer* chronometer, const unsigned int& index, AbstractChart* parent) : AbstractChart(parent), distanceSet(nullptr), 
                    chronometerSet(nullptr), speedSet(nullptr), barSeries(nullptr), axisX(nullptr), axisY(nullptr), chart(nullptr), chartView(nullptr), 
                    layout(nullptr){
    setFixedSize(345, 183);
    
    if(chronometer!=nullptr){
        chronometer->setObserver(this);

        // A seconda di quale index arriva dal segnale della QComboBox, chiama il corretto metodo di set dei dati di chronometer
        if(index == 0)
            chronometer->setRandomData();
        else if(index == 1)
            chronometer->setNormalDistributionData();
        else if(index == 2)
            chronometer->setUniformDistributionData();
        else
            chronometer->setExponentialDistributionData();
    }
}

Histogram::Histogram(Sensor::SpeedSensor* speedSensor, AbstractChart* parent) : AbstractChart(parent), distanceSet(nullptr), chronometerSet(nullptr), 
                    speedSet(nullptr), barSeries(nullptr), axisX(nullptr), axisY(nullptr), chart(nullptr), chartView(nullptr), layout(nullptr){
    setFixedSize(345, 183);
    
    if(speedSensor!=nullptr){
        speedSensor->setObserver(this);
        speedSensor->setData();
    }
}

void Histogram::updateDataDistanceChart(const Sensor::DistanceCoveredSensor& distanceCoveredSensor) {
    // Dealloca la memoria nel caso il grafico già esista
    delete distanceSet; delete barSeries; delete axisX; delete axisY; delete chart; delete chartView; delete layout;
    distanceSet = nullptr; barSeries = nullptr; axisX = nullptr; axisY = nullptr; chart = nullptr; chartView = nullptr; layout = nullptr;


    std::vector<double> data = distanceCoveredSensor.getData();

    // Crea un set di barre
    distanceSet = new QBarSet("Distance");
    for (long unsigned int i = 0; i < data.size(); ++i) {
        *distanceSet << data[i];
    }

    // Crea una serie di barre
    barSeries = new QBarSeries();
    barSeries->append(distanceSet);

    // Crea l'asse X
    axisX = new QBarCategoryAxis();
    axisX->setTitleText("This week's tests");

    // Crea l'asse Y
    axisY = new QValueAxis();
    axisY->setTitleText("Distance covered");

    // Crea il grafico
    chart = new QChart();
    chart->setTitle("Distanza percorsa");
    chart->legend()->hide();
    chart->addSeries(barSeries);
    chart->axes(Qt::Horizontal, barSeries).append(axisX);
    chart->axes(Qt::Vertical, barSeries).append(axisY);

    // Crea la vista del grafico e imposta il grafico
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Crea il layout e vi aggiunge la vista del grafico
    layout = new QVBoxLayout();
    layout->addWidget(chartView);
    setLayout(layout);
}

void Histogram::updateDataChronoChart(const Sensor::Chronometer& chronometer) {
    // Dealloca la memoria nel caso il grafico già esista
    delete chronometerSet; delete barSeries; delete axisX; delete axisY; delete chart; delete chartView; delete layout;
    chronometerSet = nullptr; barSeries = nullptr; axisX = nullptr; axisY = nullptr; chart = nullptr; chartView = nullptr; layout = nullptr;


    std::vector<double> data = chronometer.getData();

    chronometerSet = new QBarSet("Chronometer");
    for (long unsigned int i = 0; i < data.size(); ++i) {
        *chronometerSet << data[i];
    }

    barSeries = new QBarSeries();
    barSeries->append(chronometerSet);

    axisX = new QBarCategoryAxis();
    axisX->setTitleText("This week's tests");

    axisY = new QValueAxis();
    axisY->setTitleText("Flight time");

    chart = new QChart();
    chart->setTitle("Tempo di volo");
    chart->legend()->hide();
    chart->addSeries(barSeries);
    chart->axes(Qt::Horizontal, barSeries).append(axisX);
    chart->axes(Qt::Vertical, barSeries).append(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout = new QVBoxLayout();
    layout->addWidget(chartView);
    setLayout(layout);
}

void Histogram::updateDataSpeedChart(const Sensor::SpeedSensor& speedSensor) {
    // Dealloca la memoria nel caso il grafico già esista
    delete speedSet; delete barSeries; delete axisX; delete axisY; delete chart; delete chartView; delete layout;
    speedSet = nullptr; barSeries = nullptr; axisX = nullptr; axisY = nullptr; chart = nullptr; chartView = nullptr; layout = nullptr;


    std::vector<double> data = speedSensor.getData();

    speedSet = new QBarSet("Speed");
    for (long unsigned int i = 0; i < data.size(); ++i) {
        *speedSet << data[i];
    }

    barSeries = new QBarSeries();
    barSeries->append(speedSet);

    axisX = new QBarCategoryAxis();
    axisX->setTitleText("This week's tests");

    axisY = new QValueAxis();
    axisY->setTitleText("Speed");

    chart = new QChart();
    chart->setTitle("Velocità");
    chart->legend()->hide();
    chart->addSeries(barSeries);
    chart->axes(Qt::Horizontal, barSeries).append(axisX);
    chart->axes(Qt::Vertical, barSeries).append(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout = new QVBoxLayout();
    layout->addWidget(chartView);
    setLayout(layout);
}

void Histogram::notify(const Sensor::AbstractSensor& sensor){
    ConcreteChartVisitor concreteChartVisitor(this);
    sensor.accept(concreteChartVisitor);
}

Histogram::~Histogram(){
    delete distanceSet;
    delete chronometerSet;
    delete speedSet;
    delete barSeries;
    delete axisX;
    delete axisY;
    delete chart;
    delete chartView;
    delete layout;
}

}