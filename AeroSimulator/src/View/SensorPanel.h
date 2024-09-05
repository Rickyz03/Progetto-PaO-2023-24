#ifndef SENSORPANEL_H
#define SENSORPANEL_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QScrollArea>
#include <QLabel>
#include <algorithm>
#include <QMultiMap>

#include "../Sensor/Accelerometer.h"
#include "AddSensorDialogueWindow.h"
#include "SensorWidget.h"

namespace View {

class SensorPanel : public QWidget {
    Q_OBJECT

private:
    QVBoxLayout* mainLayout;

    QHBoxLayout* searchLayout;
    QLineEdit* searchBar;
    //QPushButton* goButton;
    QPushButton* returnBackButton;

    QVBoxLayout* sensorLayout;
    QScrollArea* scrollArea;
    std::vector<SensorWidget*> sensorWidgets;
    QWidget* sensorWidgetContainer;

    QPushButton* addSensorButton;

    AddSensorDialogueWindow* addWindow;

    SensorWidget* sensorWidget; // Puntatore temporaneo, crea oggetti perchè siano inseriti nel vector sensorWidgets, e poi si autoannulla
                                // Per questo basta solo costruirlo a nullptr nel costruttore, non occorre distruggerlo all'inizio di funzioni o nel distruttore,
                                // appunto perchè delega la sua memoria sullo Heap al vector tramite copia shallow, e poi "stacca la sua freccia".
                                // Quella memoria sulla Heap verra pulita al momento della pulizia del vector stesso
protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void areThereAnySensors();
    void searchSignal();
    void oneCharacterSearch();
    void searchResults(const std::vector<SensorWidget*>& sensorWidgets);
    void returnBackSignal();
    void sensorSelected(const unsigned int& id);
    void createAndAddSensorSignal();
    void finallyYouCanCreateAndAddSensor(const std::vector<Sensor::AbstractSensor*>& sensors);
    void sensorAdded(Sensor::AbstractSensor* sensor);

public slots:
    void afterTextChangedSlot();
    void search();
    void returnBackFromSearch();
    void addSensorSlot();
    void createAndAddSensorSlot();
    void nowIGiveYouTheSensorsSoYouCanCheckIfNameAndIDAreUnique(const std::vector<Sensor::AbstractSensor*>& sensors);
    void handleSensorWidgetSelected(SensorWidget* sender);
    void handleSensorAdded(Sensor::AbstractSensor* sensor);

public:
    explicit SensorPanel(const std::vector<Sensor::AbstractSensor*>& sensors, QWidget *parent);
    void createPanel(const std::vector<Sensor::AbstractSensor*>& sensors);
    void updateSearchResults(const std::vector<Sensor::AbstractSensor*>& sensors);
    int findLengthOfLongestCommonSubstring(const QString& str1, const QString& str2);
    std::vector<Sensor::AbstractSensor*> getSensorsForKey(const QMultiMap<int, Sensor::AbstractSensor*>& sensorMap, int key);

    void setTypeAndIconOfSensorWidget(const QString& type, const QIcon& icon);

    void afterTextChanged(const bool& thereAreSensors);
    void modifyOneName(const std::string& previousName, const std::string& newName);
    void setColors(Sensor::AbstractSensor* previousCurrentSensor, Sensor::AbstractSensor* newCurrentSensor);

    ~SensorPanel();
};

}

#endif
