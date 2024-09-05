#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include <QApplication>
#include <QWidget> 
#include <QMainWindow>
#include <QtCharts>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <vector>

#include "../Sensor/Repository/JsonRepository.h"
#include "../Sensor/Accelerometer.h"
#include "../Chart/Histogram.h"
#include "../Chart/LineChart.h"
#include "AboveChartWidget.h"
#include "ChartWidget.h"
#include "SensorPanel.h"
#include "StatusBar.h"
#include "ToolBar.h"

QT_USE_NAMESPACE 

namespace View {

class MainWindow: public QMainWindow{
    Q_OBJECT

private:
    std::vector<Sensor::AbstractSensor*> sensors;
    Sensor::Repository::JsonRepository* repository;

    bool isSaved;

    QWidget* centralWidget;
    QVBoxLayout* mainLayout;
    QHBoxLayout* centralLayout;
    QVBoxLayout* chartLayout;

    ToolBar* toolBar;
    SensorPanel* sensorPanel;
    AboveChartWidget* aboveChartWidget;
    ChartWidget* chartWidget;
    StatusBar* statusBar;

signals:
    void nowIGiveYouTheSensorsSoYouCanCheckIfNameAndIDAreUnique(const std::vector<Sensor::AbstractSensor*>& sensors);
    void nowIGiveYouTheSensorsSoYouCanCheckIfNameIsUnique(const std::vector<Sensor::AbstractSensor*>& sensors);

public slots:
    void closeEvent(QCloseEvent* event);
    void openHandler();
    void saveHandler();
    void saveAsHandler();
    void fileOpenedHandler();
    void setIsSaved(const bool& value);
    void checkIfAreThereAnySensors();
    void searchHandler();
    //void oneCharacterSearchHandler();
    void searchResultsHandler(const std::vector<SensorWidget*>& sensorWidgets);
    void returnBackHandler();
    void sensorSelectedHandler(const unsigned int& id); 
    void sensorAddedHandler(Sensor::AbstractSensor* sensor); 
    void createAndAddSensorHandler();
    void modifyHandler();
    void applyChangesHandler();
    void saveModifyHandler(const std::string& name, const double& min_value, const double& max_value, const double& mean, const double& variance, 
                           const double& lambda);
    void nameModifiedHandler(const std::string& previousName, const std::string& newName);
    void sensorDeletedHandler();
    void simulationHandler();
    void afterAccelerationSimulationHandler(const Sensor::Accelerometer& accelerometer, const bool& isLineRed);

public:
    explicit MainWindow(QWidget* parent = 0); 

    bool maybeSave();
    Sensor::AbstractSensor* getCurrentlySelectedSensor();
    void setSensors();

    ~MainWindow();
};

}

#endif