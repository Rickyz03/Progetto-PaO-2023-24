#include "LineChart.h"
#include "ConcreteChartVisitor.h"
#include <iostream>

#define LOWER_THRESHOLD 0.025
#define UPPER_THRESHOLD 9.0

namespace Chart{

LineChart::LineChart(Sensor::Accelerometer* accelerometer, AbstractChart* parent) : AbstractChart(parent), accelerationSeries(nullptr), 
                     lowerThresholdSeries(nullptr), upperThresholdSeries(nullptr), axisX(nullptr), axisY(nullptr), chart(nullptr), chartView(nullptr), 
                     layout(nullptr), isLineRed(false){
    setFixedSize(345, 183);
    
    if(accelerometer!=nullptr){
        accelerometer->setObserver(this);
        accelerometer->setData();
    }
}

bool LineChart::getIsLineRed() const {
    return isLineRed;
}

void LineChart::updateDataAccelerationChart(const Sensor::Accelerometer& accelerometer) {
    // Dealloca la memoria nel caso il grafico già esista
    delete accelerationSeries, delete lowerThresholdSeries, delete upperThresholdSeries, delete axisX, delete axisY, delete chart, delete chartView; 
    delete layout;
    accelerationSeries = nullptr, lowerThresholdSeries = nullptr, upperThresholdSeries = nullptr, axisX = nullptr, axisY = nullptr, chart = nullptr, 
    chartView = nullptr; layout = nullptr;


    std::vector<double> data = accelerometer.getData();

    accelerationSeries = new QLineSeries();
    for (size_t i = 0; i < data.size(); ++i) {
        accelerationSeries->append(i, data[i]);
    }

    chart = new QChart();
    chart->setTitle("Accelerazione");
    chart->legend()->hide(); // Nasconde la legenda predefinita, sennò mi sarebbero apparsi tre quadratoni a occupar spazio
    chart->addSeries(accelerationSeries);

    // Creazione dell'asse x
    axisX = new QValueAxis();
    //axisX->setTitleText("This week's tests");

    // Creazione dell'asse y
    axisY = new QValueAxis();
    axisY->setRange(0, 10);
    //axisY->setTitleText("Acceleration");

    // Un esperimento non riuscito
    /*chart->axes(Qt::Horizontal, accelerationSeries).append(axisX);
    chart->axes(Qt::Vertical, accelerationSeries).append(axisY);*/

    // Aggiunta dell'asse y al grafico
    chart->addAxis(axisY, Qt::AlignLeft);
    accelerationSeries->attachAxis(axisY);

    // Aggiunta dell'asse x al grafico
    chart->addAxis(axisX, Qt::AlignBottom);
    accelerationSeries->attachAxis(axisX);

    // Nascondere i valori numerici degli assi
    chart->axes(Qt::Horizontal).at(0)->setVisible(false); // Asse X
    chart->axes(Qt::Vertical).at(0)->setVisible(false);   // Asse Y

    // Aggiunta delle linee tratteggiate per i threshold
    QPen dashedPen(Qt::red);
    dashedPen.setStyle(Qt::DashLine);

    lowerThresholdSeries = new QLineSeries();
    chart->addSeries(lowerThresholdSeries);
    lowerThresholdSeries->append(axisX->max(), LOWER_THRESHOLD);
    lowerThresholdSeries->append(axisX->min(), LOWER_THRESHOLD);
    lowerThresholdSeries->setColor(Qt::red);
    lowerThresholdSeries->setPen(dashedPen);
    lowerThresholdSeries->attachAxis(axisY);

    upperThresholdSeries = new QLineSeries();
    chart->addSeries(upperThresholdSeries);
    upperThresholdSeries->append(axisX->min(), UPPER_THRESHOLD);
    upperThresholdSeries->append(axisX->max(), UPPER_THRESHOLD);
    lowerThresholdSeries->setColor(Qt::red);
    upperThresholdSeries->setPen(dashedPen);
    upperThresholdSeries->attachAxis(axisY);

    accelerationSeries->setPen(QPen(Qt::blue, 1));

    // Se la linea va oltre i thresholds, essa diventa rossa
    for (const auto& value : data) {
        if (value < LOWER_THRESHOLD || value > UPPER_THRESHOLD) {
            // Rendi la linea rossa
            QPen redPen(Qt::red, 3); // Imposta la penna a rosso
            redPen.setStyle(Qt::SolidLine); // Imposta lo stile della linea a solida
            accelerationSeries->setPen(redPen); // Applica la penna rossa alla serie
            isLineRed = true;
            break;  // Al primo valore che esce dai thresholds, la linea diventa rossa, non occorre controllare gli altri valori
        }
    }

    // Tentativo fallito perchè non mi rilevava il segnale
    /*
    // Se la linea è rossa, emette il segnale con true, altrimenti con false
    if (isLineRed){
        emit accelerationSimulationResume(accelerometer, true);
        qDebug()<<"Ho emesso un segnale di linea rossa";
    }
    else{
        emit accelerationSimulationResume(accelerometer, false);
        qDebug()<<"Ho emesso un segnale di linea blu";
    }
    */

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout = new QVBoxLayout();
    layout->addWidget(chartView);
    setLayout(layout);
}

void LineChart::notify(const Sensor::AbstractSensor& sensor){
    ConcreteChartVisitor concreteChartVisitor(this);
    sensor.accept(concreteChartVisitor);
}

LineChart::~LineChart(){
    delete accelerationSeries;
    delete lowerThresholdSeries;
    delete upperThresholdSeries;
    delete axisX;
    delete axisY;
    delete chart;
    delete chartView;
    delete layout;
}

}