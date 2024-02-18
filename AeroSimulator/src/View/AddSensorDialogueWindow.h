#ifndef ADD_SENSOR_DIALOGUE_WIDGET_H
#define ADD_SENSOR_DIALOGUE_WIDGET_H

#include "AbstractDialogueWindow.h"

namespace View {

class AddSensorDialogueWindow : public AbstractDialogueWindow {
    Q_OBJECT

private:
    QLabel* typeLabel;
    QLabel* idLabel;
    QLabel* nameLabel;
    QLabel* minLabel;
    QLabel* maxLabel;
    QLabel* meanLabel;
    QLabel* varianceLabel;
    QLabel* lambdaLabel;

    QComboBox* typeComboBox;
    QLineEdit* idLineEdit;
    QLineEdit* nameLineEdit;
    QLineEdit* minLineEdit;
    QLineEdit* maxLineEdit;
    QLineEdit* meanLineEdit;
    QLineEdit* varianceLineEdit;
    QLineEdit* lambdaLineEdit;

    QPushButton* discardButton;
    QPushButton* createButton;

    QVBoxLayout* mainLayout;
    QHBoxLayout* typeLayout;
    QHBoxLayout* idLayout;
    QHBoxLayout* nameLayout;
    QHBoxLayout* minLayout;
    QHBoxLayout* maxLayout;
    QHBoxLayout* meanLayout;
    QHBoxLayout* varianceLayout;
    QHBoxLayout* lambdaLayout;
    QHBoxLayout* buttonsLayout;

signals:
    void createAndAddSignal();
    void sensorAdded(Sensor::AbstractSensor* sensor);

public slots:
    void afterSomethingChanged();
    void createAndAddSlot();
    void discardChanges();

public:
    explicit AddSensorDialogueWindow(AbstractDialogueWindow* parent = nullptr);

    bool differentFromOriginal();
    void createAndAddSensor(const std::vector<Sensor::AbstractSensor*>& sensors);

    ~AddSensorDialogueWindow();
};

}

#endif
