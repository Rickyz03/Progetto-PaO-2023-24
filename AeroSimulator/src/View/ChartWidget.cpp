#include "ChartWidget.h"
#include "ChartWidgetOnSelectionVisitor.h"

namespace View {

ChartWidget::ChartWidget(QWidget *parent)
    : QWidget(parent), verticalLayout(nullptr), gridLayout(nullptr), greyPanel1(nullptr), greyPanel2(nullptr), greyPanel3(nullptr), greyPanel4(nullptr), 
    distanceHistogram(nullptr), timeHistogram(nullptr), leftComboBox(nullptr), rightComboBox(nullptr), speedHistogram(nullptr), accelerationLineChart(nullptr)
{
    initialChartWidget();
}

void ChartWidget::initialChartWidget(){
    // Rimozione degli oggetti allocati dinamicamente in precedenza
    delete greyPanel1; delete greyPanel2; delete greyPanel3; delete greyPanel4; delete distanceHistogram; delete timeHistogram; 
    delete leftComboBox; delete rightComboBox; delete speedHistogram; delete accelerationLineChart; delete gridLayout; delete verticalLayout;

    // Piazzo a nullptr i puntatori i cui oggetti puntati sono stati appena disallocati
    greyPanel1 = nullptr; greyPanel2 = nullptr; greyPanel3 = nullptr; greyPanel4 = nullptr; distanceHistogram = nullptr; timeHistogram = nullptr; 
    leftComboBox = nullptr; rightComboBox = nullptr; speedHistogram = nullptr; accelerationLineChart = nullptr; gridLayout = nullptr; verticalLayout = nullptr;


    greyPanel1 = new QFrame(this);
    greyPanel1->setStyleSheet("background-color: grey;");
    greyPanel1->setGeometry(0, 0, 714, 421);
    greyPanel1->show();
}

void ChartWidget::chartWidgetOnSelection(Sensor::AbstractSensor* sensor){
    // Rimozione degli oggetti allocati dinamicamente in precedenza
    delete greyPanel1; delete greyPanel2; delete greyPanel3; delete greyPanel4; delete distanceHistogram; delete timeHistogram; 
    delete leftComboBox; delete rightComboBox; delete speedHistogram; delete accelerationLineChart; delete gridLayout; delete verticalLayout;

    // Piazzo a nullptr i puntatori i cui oggetti puntati sono stati appena disallocati
    greyPanel1 = nullptr; greyPanel2 = nullptr; greyPanel3 = nullptr; greyPanel4 = nullptr; distanceHistogram = nullptr; timeHistogram = nullptr; 
    leftComboBox = nullptr; rightComboBox = nullptr; speedHistogram = nullptr; accelerationLineChart = nullptr; gridLayout = nullptr; verticalLayout = nullptr;


    ChartWidgetOnSelectionVisitor chartWidgetOnSelectionVisitor(this);
    sensor->accept(chartWidgetOnSelectionVisitor);
}

void ChartWidget::chartWidgetOnDistanceSelected(const Sensor::DistanceCoveredSensor& distanceCoveredSensor){
    // Strategia perchè non appaia il warning "unused parameter", perchè non c'è proprio modo di dedurre dal tipo del sensore il modo in cui intendo utilizzarlo
    std::string name = distanceCoveredSensor.getName();

    verticalLayout = new QVBoxLayout(this);

    greyPanel1 = new QFrame(this);
    greyPanel1->setStyleSheet("background-color: grey;");
    greyPanel1->setGeometry(0, 0, 714, 300);

    leftComboBox = new QComboBox(this);

    leftComboBox->setEnabled(true);
    leftComboBox->addItem("Dati casuali");
    leftComboBox->addItem("Distribuzione normale");
    leftComboBox->addItem("Distribuzione uniforme");
    leftComboBox->addItem("Distribuzione esponenziale");
    leftComboBox->setCurrentIndex(0);

    verticalLayout->addWidget(greyPanel1);
    verticalLayout->addWidget(leftComboBox);
}

void ChartWidget::chartWidgetOnChronoSelected(const Sensor::Chronometer& chronometer){
    // Strategia perchè non appaia il warning "unused parameter", perchè non c'è proprio modo di dedurre dal tipo del sensore il modo in cui intendo utilizzarlo
    std::string name = chronometer.getName();

    verticalLayout = new QVBoxLayout(this);

    greyPanel2 = new QFrame(this);
    greyPanel2->setStyleSheet("background-color: grey;");
    greyPanel2->setGeometry(0, 0, 714, 400);

    rightComboBox = new QComboBox(this);

    rightComboBox->setEnabled(true);
    rightComboBox->addItem("Dati casuali");
    rightComboBox->addItem("Distribuzione normale");
    rightComboBox->addItem("Distribuzione uniforme");
    rightComboBox->addItem("Distribuzione esponenziale");
    rightComboBox->setCurrentIndex(0);

    verticalLayout->addWidget(greyPanel2);
    verticalLayout->addWidget(rightComboBox);
}

void ChartWidget::chartWidgetOnSpeedSelected(const Sensor::SpeedSensor& speedSensor){
    // Strategia perchè non appaia il warning "unused parameter", perchè non c'è proprio modo di dedurre dal tipo del sensore il modo in cui intendo utilizzarlo
    std::string name = speedSensor.getName();

    verticalLayout = new QVBoxLayout(this);
    gridLayout = new QGridLayout();

    greyPanel1 = new QFrame(this);
    greyPanel1->setStyleSheet("background-color: grey;");
    greyPanel1->setGeometry(0, 0, width(), height());

    greyPanel2 = new QFrame(this);
    greyPanel2->setStyleSheet("background-color: grey;");
    greyPanel2->setGeometry(0, 0, width(), height());

    leftComboBox = new QComboBox(this);
    rightComboBox = new QComboBox(this);

    leftComboBox->setEnabled(true);
    leftComboBox->addItem("Dati casuali");
    leftComboBox->addItem("Distribuzione normale");
    leftComboBox->addItem("Distribuzione uniforme");
    leftComboBox->addItem("Distribuzione esponenziale");
    leftComboBox->setCurrentIndex(0);

    rightComboBox->setEnabled(true);
    rightComboBox->addItem("Dati casuali");
    rightComboBox->addItem("Distribuzione normale");
    rightComboBox->addItem("Distribuzione uniforme");
    rightComboBox->addItem("Distribuzione esponenziale");
    rightComboBox->setCurrentIndex(0);

    gridLayout->addWidget(greyPanel1, 0, 0);
    gridLayout->addWidget(greyPanel2, 0, 1);
    gridLayout->addWidget(leftComboBox, 1, 0);
    gridLayout->addWidget(rightComboBox, 1, 1);

    greyPanel3 = new QFrame(this);
    greyPanel3->setStyleSheet("background-color: grey;");
    greyPanel3->setGeometry(0, 0, width(), height());

    verticalLayout->addLayout(gridLayout);
    verticalLayout->addWidget(greyPanel3);
}

void ChartWidget::chartWidgetOnAccelerometerSelected(const Sensor::Accelerometer& accelerometer){
    // Strategia perchè non appaia il warning "unused parameter", perchè non c'è proprio modo di dedurre dal tipo del sensore il modo in cui intendo utilizzarlo
    std::string name = accelerometer.getName();

    gridLayout = new QGridLayout(this);

    greyPanel1 = new QFrame(this);
    greyPanel1->setStyleSheet("background-color: grey;");
    greyPanel1->setGeometry(0, 0, width(), height());

    greyPanel2 = new QFrame(this);
    greyPanel2->setStyleSheet("background-color: grey;");
    greyPanel2->setGeometry(0, 0, width(), height());

    leftComboBox = new QComboBox(this);
    rightComboBox = new QComboBox(this);

    leftComboBox->setEnabled(true);
    leftComboBox->addItem("Dati casuali");
    leftComboBox->addItem("Distribuzione normale");
    leftComboBox->addItem("Distribuzione uniforme");
    leftComboBox->addItem("Distribuzione esponenziale");
    leftComboBox->setCurrentIndex(0);

    rightComboBox->setEnabled(true);
    rightComboBox->addItem("Dati casuali");
    rightComboBox->addItem("Distribuzione normale");
    rightComboBox->addItem("Distribuzione uniforme");
    rightComboBox->addItem("Distribuzione esponenziale");
    rightComboBox->setCurrentIndex(0);

    greyPanel3 = new QFrame(this);
    greyPanel3->setStyleSheet("background-color: grey;");
    greyPanel3->setGeometry(0, 0, width(), height());

    greyPanel4 = new QFrame(this);
    greyPanel4->setStyleSheet("background-color: grey;");
    greyPanel4->setGeometry(0, 0, width(), height());

    gridLayout->addWidget(greyPanel1, 0, 0);
    gridLayout->addWidget(greyPanel2, 0, 1);
    gridLayout->addWidget(leftComboBox, 1, 0);
    gridLayout->addWidget(rightComboBox, 1, 1);
    gridLayout->addWidget(greyPanel3, 2, 0);
    gridLayout->addWidget(greyPanel4, 2, 1);
}

void ChartWidget::insertDistanceChart(Sensor::DistanceCoveredSensor* distanceCoveredSensor){
    int index = leftComboBox->currentIndex();


    // Rimozione degli oggetti allocati dinamicamente in precedenza
    delete greyPanel1; delete greyPanel2; delete greyPanel3; delete greyPanel4; delete distanceHistogram; delete timeHistogram; 
    delete leftComboBox; delete rightComboBox; delete speedHistogram; delete accelerationLineChart; delete gridLayout; delete verticalLayout;

    // Piazzo a nullptr i puntatori i cui oggetti puntati sono stati appena disallocati
    greyPanel1 = nullptr; greyPanel2 = nullptr; greyPanel3 = nullptr; greyPanel4 = nullptr; distanceHistogram = nullptr; timeHistogram = nullptr; 
    leftComboBox = nullptr; rightComboBox = nullptr; speedHistogram = nullptr; accelerationLineChart = nullptr; gridLayout = nullptr; verticalLayout = nullptr;

   
    verticalLayout = new QVBoxLayout(this);

    distanceHistogram = new Chart::Histogram(distanceCoveredSensor, index);
    distanceHistogram->setFixedSize(714, 300);

    leftComboBox = new QComboBox(this);

    leftComboBox->setEnabled(true);
    leftComboBox->addItem("Dati casuali");
    leftComboBox->addItem("Distribuzione normale");
    leftComboBox->addItem("Distribuzione uniforme");
    leftComboBox->addItem("Distribuzione esponenziale");
    leftComboBox->setCurrentIndex(index);

    verticalLayout->addWidget(distanceHistogram);
    verticalLayout->addWidget(leftComboBox);
}

void ChartWidget::insertChronoChart(Sensor::Chronometer* chronometer){
    int index = rightComboBox->currentIndex();


    // Rimozione degli oggetti allocati dinamicamente in precedenza
    delete greyPanel1; delete greyPanel2; delete greyPanel3; delete greyPanel4; delete distanceHistogram; delete timeHistogram; 
    delete leftComboBox; delete rightComboBox; delete speedHistogram; delete accelerationLineChart; delete gridLayout; delete verticalLayout;

    // Piazzo a nullptr i puntatori i cui oggetti puntati sono stati appena disallocati
    greyPanel1 = nullptr; greyPanel2 = nullptr; greyPanel3 = nullptr; greyPanel4 = nullptr; distanceHistogram = nullptr; timeHistogram = nullptr; 
    leftComboBox = nullptr; rightComboBox = nullptr; speedHistogram = nullptr; accelerationLineChart = nullptr; gridLayout = nullptr; verticalLayout = nullptr;


    verticalLayout = new QVBoxLayout(this);

    timeHistogram = new Chart::Histogram(chronometer, index);
    timeHistogram->setFixedSize(714, 300);

    rightComboBox = new QComboBox(this);

    rightComboBox->setEnabled(true);
    rightComboBox->addItem("Dati casuali");
    rightComboBox->addItem("Distribuzione normale");
    rightComboBox->addItem("Distribuzione uniforme");
    rightComboBox->addItem("Distribuzione esponenziale");
    rightComboBox->setCurrentIndex(index);

    verticalLayout->addWidget(timeHistogram);
    verticalLayout->addWidget(rightComboBox);
}

void ChartWidget::insertSpeedChart(Sensor::SpeedSensor* speedSensor){
    int index1 = leftComboBox->currentIndex();
    int index2 = rightComboBox->currentIndex();


    // Rimozione degli oggetti allocati dinamicamente in precedenza
    delete greyPanel1; delete greyPanel2; delete greyPanel3; delete greyPanel4; delete distanceHistogram; delete timeHistogram; 
    delete leftComboBox; delete rightComboBox; delete speedHistogram; delete accelerationLineChart; delete gridLayout; delete verticalLayout;

    // Piazzo a nullptr i puntatori i cui oggetti puntati sono stati appena disallocati
    greyPanel1 = nullptr; greyPanel2 = nullptr; greyPanel3 = nullptr; greyPanel4 = nullptr; distanceHistogram = nullptr; timeHistogram = nullptr; 
    leftComboBox = nullptr; rightComboBox = nullptr; speedHistogram = nullptr; accelerationLineChart = nullptr; gridLayout = nullptr; verticalLayout = nullptr;




    verticalLayout = new QVBoxLayout(this);
    gridLayout = new QGridLayout();

    distanceHistogram = new Chart::Histogram(&(speedSensor->getDistanceCoveredSensor_NON_Const()), index1);

    timeHistogram = new Chart::Histogram(&(speedSensor->getChronometer_NON_Const()), index2);

    leftComboBox = new QComboBox(this);
    rightComboBox = new QComboBox(this);

    leftComboBox->setEnabled(true);
    leftComboBox->addItem("Dati casuali");
    leftComboBox->addItem("Distribuzione normale");
    leftComboBox->addItem("Distribuzione uniforme");
    leftComboBox->addItem("Distribuzione esponenziale");
    leftComboBox->setCurrentIndex(index1);

    rightComboBox->setEnabled(true);
    rightComboBox->addItem("Dati casuali");
    rightComboBox->addItem("Distribuzione normale");
    rightComboBox->addItem("Distribuzione uniforme");
    rightComboBox->addItem("Distribuzione esponenziale");
    rightComboBox->setCurrentIndex(index2);

    gridLayout->addWidget(distanceHistogram, 0, 0);
    gridLayout->addWidget(timeHistogram, 0, 1);
    gridLayout->addWidget(leftComboBox, 1, 0);
    gridLayout->addWidget(rightComboBox, 1, 1);

    speedHistogram = new Chart::Histogram(speedSensor);
    speedHistogram->setFixedSize(714, 215);

    verticalLayout->addLayout(gridLayout);
    verticalLayout->addWidget(speedHistogram);
}

void ChartWidget::insertAccelerationChart(Sensor::Accelerometer* accelerometer){
    int index1 = leftComboBox->currentIndex();
    int index2 = rightComboBox->currentIndex();


    // Rimozione degli oggetti allocati dinamicamente in precedenza
    delete greyPanel1; delete greyPanel2; delete greyPanel3; delete greyPanel4; delete distanceHistogram; delete timeHistogram; 
    delete leftComboBox; delete rightComboBox; delete speedHistogram; delete accelerationLineChart; delete gridLayout; delete verticalLayout;

    // Piazzo a nullptr i puntatori i cui oggetti puntati sono stati appena disallocati
    greyPanel1 = nullptr; greyPanel2 = nullptr; greyPanel3 = nullptr; greyPanel4 = nullptr; distanceHistogram = nullptr; timeHistogram = nullptr; 
    leftComboBox = nullptr; rightComboBox = nullptr; speedHistogram = nullptr; accelerationLineChart = nullptr; gridLayout = nullptr; verticalLayout = nullptr;


    gridLayout = new QGridLayout(this);

    distanceHistogram = new Chart::Histogram(&((accelerometer->getSpeedSensor_NON_Const()).getDistanceCoveredSensor_NON_Const()), index1);


    // Dichiaro qui, perchè andrò a creare i dati identici per entrambi i cronometri annidati
    Sensor::Chronometer* nestedSpeedChronometer = &((accelerometer->getSpeedSensor_NON_Const()).getChronometer_NON_Const());
    Sensor::Chronometer* nestedAccelerationChronometer = &(accelerometer->getChronometer_NON_Const());

    // Il cronometro scelto per la rappresentazione con il grafico è quello annidato in Accelerometer. L'altro gli copia i dati
    timeHistogram = new Chart::Histogram(nestedAccelerationChronometer, index2);
    nestedSpeedChronometer->setData(nestedAccelerationChronometer->getData());


    leftComboBox = new QComboBox(this);
    leftComboBox->setEnabled(true);
    leftComboBox->addItem("Dati casuali");
    leftComboBox->addItem("Distribuzione normale");
    leftComboBox->addItem("Distribuzione uniforme");
    leftComboBox->addItem("Distribuzione esponenziale");
    leftComboBox->setCurrentIndex(index1);

    rightComboBox = new QComboBox(this);
    rightComboBox->setEnabled(true);
    rightComboBox->addItem("Dati casuali");
    rightComboBox->addItem("Distribuzione normale");
    rightComboBox->addItem("Distribuzione uniforme");
    rightComboBox->addItem("Distribuzione esponenziale");
    rightComboBox->setCurrentIndex(index2);

    speedHistogram = new Chart::Histogram(&(accelerometer->getSpeedSensor_NON_Const()));

    accelerationLineChart = new Chart::LineChart(accelerometer);

    // Tentativo fallito perchè non mi rilevava il segnale
    //connect(accelerationLineChart, &Chart::LineChart::accelerationSimulationResume, this, &ChartWidget::theAccelerationLineIs);

    theAccelerationLineIs(*accelerometer, accelerationLineChart->getIsLineRed());

    gridLayout->addWidget(distanceHistogram, 0, 0);
    gridLayout->addWidget(timeHistogram, 0, 1);
    gridLayout->addWidget(leftComboBox, 1, 0);
    gridLayout->addWidget(rightComboBox, 1, 1);
    gridLayout->addWidget(speedHistogram, 2, 0);
    gridLayout->addWidget(accelerationLineChart, 2, 1);
}

void ChartWidget::theAccelerationLineIs(const Sensor::Accelerometer& accelerometer, const bool& isLineRed){
    emit accelerationLineColor(accelerometer, isLineRed);
}

ChartWidget::~ChartWidget(){
    delete greyPanel1;
    delete greyPanel2;
    delete greyPanel3;
    delete greyPanel4;

    delete distanceHistogram;
    delete timeHistogram;
    delete leftComboBox;
    delete rightComboBox;
    delete speedHistogram;
    delete accelerationLineChart;

    delete gridLayout;
    delete verticalLayout;
}

}
