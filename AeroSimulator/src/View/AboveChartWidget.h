#ifndef ABOVECHARTWIDGET_H
#define ABOVECHARTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

#include "../Sensor/Accelerometer.h"
#include "ModifySensorDialogueWindow.h"

namespace View {

class AboveChartWidget : public QWidget {
    Q_OBJECT

private:
    QFrame* greyPanel;

    QGridLayout* layout;

    QLabel* sensorNameLabel;
    QLabel* sensorIDLabel;
    QLabel* embeddedSensorsLabel;
    QLabel* minValueLabel;
    QLabel* maxValueLabel;
    QLabel* meanLabel;
    QLabel* varianceLabel;
    QLabel* lambdaLabel;
    QLabel* airplaneEnabledLabel;

    QPushButton* simulateButton;
    QPushButton* modifyButton;
    QPushButton* deleteButton;

    ModifySensorDialogueWindow* modifyWindow;

signals:
    void setIsSaved(const bool& value);
    void modifySignal();
    void applyChangesSignal();
    void finallyYouCanApplyChanges(const std::vector<Sensor::AbstractSensor*>& sensors);
    void saveModifySignal(const std::string& name, const double& min_value, const double& max_value, const double& mean, const double& variance, 
                          const double& lambda);
    void nameHasBeenModified(const std::string& previousName, const std::string& newName); 
    void sensorDeleted();
    void simulate();

public slots:
    void modifySlot();
    void applyChangesSlot();
    void nowIGiveYouTheSensorsSoYouCanCheckIfNameIsUnique(const std::vector<Sensor::AbstractSensor*>& sensors);
    void saveModifySlot(const std::string& name, const double& min_value, const double& max_value, const double& mean, const double& variance, 
                        const double& lambda);
    void nameModifiedSlot(const std::string& previousName, const std::string& newName);
    void deleteSlot();
    void simulateSlot();

public:
    AboveChartWidget(QWidget *parent = nullptr);
    void createGreyPanel();
    void createAboveChartForSensor(Sensor::AbstractSensor* sensor);
    void recreateAfterAccelerometerSimulation(Sensor::Accelerometer* accelerometer, const bool& LineisRed);
    
    void createTheRestOfLabels(const double& minValue, const double& maxValue, const double& mean, const double& variance, const double& lambda);
    void createEmbeddedSensorsLabel(const unsigned int& number);

    unsigned int getId() const;
    void modify(Sensor::AbstractSensor* sensor);
    void saveModify(Sensor::AbstractSensor* sensor, const std::string& name, const double& min_value, const double& max_value, 
                    const double& mean, const double& variance, const double& lambda);

    void setSensorNameLabel(const std::string& name);
    void setMinValueLabel(const double& min_value);
    void setMaxValueLabel(const double& max_value);
    void setMeanLabel(const double& mean);
    void setVarianceLabel(const double& variance);
    void setLambdaLabel(const double& lambda);

    ~AboveChartWidget();
};

}

#endif
