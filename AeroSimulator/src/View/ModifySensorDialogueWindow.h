#ifndef MODIFYSENSORDIALOGUEWINDOW_H
#define MODIFYSENSORDIALOGUEWINDOW_H

#include "AbstractDialogueWindow.h"

namespace View{

class ModifySensorDialogueWindow : public AbstractDialogueWindow {
    Q_OBJECT

private:
    unsigned int id;
    std::string originalSensorName;
    double originalMinValue;
    double originalMaxValue;
    double originalMean;
    double originalVariance;
    double originalLambda;

    QLabel* nameLabel;
    QLabel* minLabel;
    QLabel* maxLabel;
    QLabel* meanLabel;
    QLabel* varianceLabel;
    QLabel* lambdaLabel;

    QLineEdit* nameLineEdit;
    QLineEdit* minLineEdit;
    QLineEdit* maxLineEdit;
    QLineEdit* meanLineEdit;
    QLineEdit* varianceLineEdit;
    QLineEdit* lambdaLineEdit;

    QPushButton* discardButton;
    QPushButton* applyButton;

    QVBoxLayout* mainLayout;
    QHBoxLayout* nameLayout;
    QHBoxLayout* minLayout;
    QHBoxLayout* maxLayout;
    QHBoxLayout* meanLayout;
    QHBoxLayout* varianceLayout;
    QHBoxLayout* lambdaLayout;
    QHBoxLayout* buttonsLayout;

signals:
    void applySignal();
    void sensorModified(const std::string& name, const double& min_value, const double& max_value, const double& mean, const double& variance, 
                        const double& lambda);
    void sensorNameModified(const std::string& previousName, const std::string& newName);

public slots:
    void afterTextChanged();
    void discardChanges();
    void applySlot();

public:
    explicit ModifySensorDialogueWindow(const unsigned int& Id, const std::string& OriginalSensorName, const double& OriginalMinValue, const double& OriginalMaxValue, 
               const double& OriginalMean, const double& OriginalVariance, const double& OriginalLambda, AbstractDialogueWindow* parent = nullptr);
    
    bool differentFromOriginal();
    void applyChanges(const std::vector<Sensor::AbstractSensor*> sensors);

    ~ModifySensorDialogueWindow();
};

}

#endif
