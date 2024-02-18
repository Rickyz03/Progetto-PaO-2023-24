#include "AboveChartWidget.h"
#include "AboveChartLabelsCreatorVisitor.h"
#include <stdexcept>

namespace View {

AboveChartWidget::AboveChartWidget(QWidget *parent) : QWidget(parent), greyPanel(nullptr), layout(nullptr), sensorNameLabel(nullptr), sensorIDLabel(nullptr),
        embeddedSensorsLabel(nullptr), minValueLabel(nullptr), maxValueLabel(nullptr), meanLabel(nullptr), varianceLabel(nullptr), lambdaLabel(nullptr),
        airplaneEnabledLabel(nullptr), simulateButton(nullptr), modifyButton(nullptr), deleteButton(nullptr), modifyWindow(nullptr) {
    createGreyPanel();
}

void AboveChartWidget::createGreyPanel(){
    // Rimozione degli oggetti allocati dinamicamente in precedenza
    delete greyPanel; delete sensorNameLabel; delete sensorIDLabel; delete embeddedSensorsLabel; delete minValueLabel; delete maxValueLabel; 
    delete meanLabel; delete varianceLabel; delete lambdaLabel; delete airplaneEnabledLabel; 
    delete simulateButton; delete modifyButton; delete deleteButton; delete modifyWindow; delete layout;

    // Piazzo a nullptr i puntatori i cui oggetti puntati sono stati appena disallocati
    greyPanel = nullptr; sensorNameLabel = nullptr; sensorIDLabel = nullptr; embeddedSensorsLabel = nullptr; minValueLabel = nullptr; maxValueLabel = nullptr;
    meanLabel = nullptr; varianceLabel = nullptr; lambdaLabel = nullptr; airplaneEnabledLabel = nullptr; simulateButton = nullptr; modifyButton = nullptr; 
    deleteButton = nullptr; modifyWindow = nullptr; layout = nullptr;


    greyPanel = new QFrame(this);
    greyPanel->setStyleSheet("background-color: grey;");
    greyPanel->setGeometry(0, 0, 714, 85);
    greyPanel->show();
}

void AboveChartWidget::createAboveChartForSensor(Sensor::AbstractSensor* sensor){
    // Rimozione degli oggetti allocati dinamicamente in precedenza
    delete greyPanel; delete sensorNameLabel; delete sensorIDLabel; delete embeddedSensorsLabel; delete minValueLabel; delete maxValueLabel; 
    delete meanLabel; delete varianceLabel; delete lambdaLabel; delete airplaneEnabledLabel;  
    delete simulateButton; delete modifyButton; delete deleteButton; delete modifyWindow; delete layout;

    // Piazzo a nullptr i puntatori i cui oggetti puntati sono stati appena disallocati
    greyPanel = nullptr; sensorNameLabel = nullptr; sensorIDLabel = nullptr; embeddedSensorsLabel = nullptr; minValueLabel = nullptr; maxValueLabel = nullptr;
    meanLabel = nullptr; varianceLabel = nullptr; lambdaLabel = nullptr; airplaneEnabledLabel = nullptr; simulateButton = nullptr; modifyButton = nullptr; 
    deleteButton = nullptr; modifyWindow = nullptr; layout = nullptr;


    // Crea i pulsanti visivi
    simulateButton = new QPushButton(QIcon("Assets/Pulsanti/Simula.svg"), tr("Simula"), this);
    modifyButton = new QPushButton(QIcon("Assets/Pulsanti/Modifica.svg"), tr("Modifica"), this);
    deleteButton = new QPushButton(QIcon("Assets/Pulsanti/Elimina.svg"), tr("Elimina"), this);

    // Collega le shortcut ai QPushButtons
    simulateButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_T));
    modifyButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_M));
    deleteButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_E));


    // Creazione delle etichette per i dati del sensore
    sensorNameLabel = new QLabel(QString::fromStdString(sensor->getName()), this);
    sensorIDLabel = new QLabel("ID: " + QString::number(sensor->getIdentifier()), this);

    AboveChartLabelsCreatorVisitor aboveChartLabelsCreatorVisitor(this);
    sensor->accept(aboveChartLabelsCreatorVisitor);

    // Imposta la dimensione del carattere per il nome del sensore
    QFont font = sensorNameLabel->font();
    font.setPointSize(14);
    sensorNameLabel->setFont(font);
    

    // Creazione dei layout per organizzare i widget
    layout = new QGridLayout(this);

    // Aggiunta dei widget al layout dei dati
    layout->addWidget(sensorNameLabel, 0, 0);
    layout->addWidget(modifyButton, 0, 1);
    layout->addWidget(deleteButton, 0, 2);
    layout->addWidget(simulateButton, 0, 3);
    layout->addWidget(sensorIDLabel, 1, 0);
    layout->addWidget(minValueLabel, 1, 1);
    layout->addWidget(meanLabel, 1, 2);
    layout->addWidget(lambdaLabel, 1, 3);
    layout->addWidget(embeddedSensorsLabel, 2, 0);
    layout->addWidget(maxValueLabel, 2, 1);
    layout->addWidget(varianceLabel, 2, 2);

    // Settaggio del layout principale per il widget
    setLayout(layout);
    

    connect(simulateButton, &QPushButton::clicked, this, &AboveChartWidget::simulateSlot);
    connect(modifyButton, &QPushButton::clicked, this, &AboveChartWidget::modifySlot);
    connect(deleteButton, &QPushButton::clicked, this, &AboveChartWidget::deleteSlot);
}

void AboveChartWidget::recreateAfterAccelerometerSimulation(Sensor::Accelerometer* accelerometer, const bool& LineisRed){
    // Rimozione degli oggetti allocati dinamicamente in precedenza
    delete greyPanel; delete sensorNameLabel; delete sensorIDLabel; delete embeddedSensorsLabel; delete minValueLabel; delete maxValueLabel; 
    delete meanLabel; delete varianceLabel; delete lambdaLabel; delete airplaneEnabledLabel;  
    delete simulateButton; delete modifyButton; delete deleteButton; delete modifyWindow; delete layout;

    // Piazzo a nullptr i puntatori i cui oggetti puntati sono stati appena disallocati
    greyPanel = nullptr; sensorNameLabel = nullptr; sensorIDLabel = nullptr; embeddedSensorsLabel = nullptr; minValueLabel = nullptr; maxValueLabel = nullptr;
    meanLabel = nullptr; varianceLabel = nullptr; lambdaLabel = nullptr; airplaneEnabledLabel = nullptr; simulateButton = nullptr; modifyButton = nullptr; 
    deleteButton = nullptr; modifyWindow = nullptr; layout = nullptr;


    // Crea i pulsanti visivi
    simulateButton = new QPushButton(QIcon("Assets/Pulsanti/Simula.svg"), tr("Simula"), this);
    modifyButton = new QPushButton(QIcon("Assets/Pulsanti/Modifica.svg"), tr("Modifica"), this);
    deleteButton = new QPushButton(QIcon("Assets/Pulsanti/Elimina.svg"), tr("Elimina"), this);

    // Collega le shortcut ai QPushButtons
    simulateButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_T));
    modifyButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_M));
    deleteButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_E));


    // Creazione delle etichette per i dati del sensore
    sensorNameLabel = new QLabel(QString::fromStdString(accelerometer->getName()), this);
    sensorIDLabel = new QLabel("ID: " + QString::number(accelerometer->getIdentifier()), this);
    
    AboveChartLabelsCreatorVisitor aboveChartLabelsCreatorVisitor(this);
    accelerometer->accept(aboveChartLabelsCreatorVisitor);

    if(LineisRed)
        airplaneEnabledLabel = new QLabel("Aereo abilitato: No", this);
    else
        airplaneEnabledLabel = new QLabel("Aereo abilitato: Sì", this);

    // Imposta la dimensione del carattere per il nome del sensore
    QFont font = sensorNameLabel->font();
    font.setPointSize(14);
    sensorNameLabel->setFont(font);


    // Creazione dei layout per organizzare i widget
    layout = new QGridLayout(this);

    // Aggiunta dei widget al layout dei dati
    layout->addWidget(sensorNameLabel, 0, 0);
    layout->addWidget(modifyButton, 0, 1);
    layout->addWidget(deleteButton, 0, 2);
    layout->addWidget(simulateButton, 0, 3);
    layout->addWidget(sensorIDLabel, 1, 0);
    layout->addWidget(minValueLabel, 1, 1);
    layout->addWidget(meanLabel, 1, 2);
    layout->addWidget(lambdaLabel, 1, 3);
    layout->addWidget(embeddedSensorsLabel, 2, 0);
    layout->addWidget(maxValueLabel, 2, 1);
    layout->addWidget(varianceLabel, 2, 2);
    layout->addWidget(airplaneEnabledLabel, 2, 3);

    // Settaggio del layout principale per il widget
    setLayout(layout);


    connect(simulateButton, &QPushButton::clicked, this, &AboveChartWidget::simulateSlot);
    connect(modifyButton, &QPushButton::clicked, this, &AboveChartWidget::modifySlot);
    connect(deleteButton, &QPushButton::clicked, this, &AboveChartWidget::deleteSlot);
}

void AboveChartWidget::createTheRestOfLabels(const double& minValue, const double& maxValue, const double& mean, 
                                            const double& variance, const double& lambda){
    minValueLabel = new QLabel("Minimo: " + QString::number(minValue), this);
    maxValueLabel = new QLabel("Massimo: " + QString::number(maxValue), this);
    meanLabel = new QLabel("Media: " + QString::number(mean), this);
    varianceLabel = new QLabel("Varianza: " + QString::number(variance), this);
    lambdaLabel = new QLabel("Lambda: " + QString::number(lambda), this);
}

void AboveChartWidget::createEmbeddedSensorsLabel(const unsigned int& number){
    embeddedSensorsLabel = new QLabel("Sensori incorporati: " + QString::number(number));
}

unsigned int AboveChartWidget::getId() const {
    if(sensorIDLabel != nullptr){
        bool ok = true;
        unsigned int id = sensorIDLabel->text().right(6).toUInt(&ok);
        if (ok) {
            return id;
        } 
        else {
            // Gestione dell'errore se il testo non è un numero intero positivo valido
            qWarning() << "ID non valido!";
            throw std::exception();
        }
    }
    else   // Se non c'è nessun sensore selezionato in AboveChartWidget
        throw std::exception();
}

void AboveChartWidget::modifySlot(){
    emit modifySignal();
}

void AboveChartWidget::modify(Sensor::AbstractSensor* sensor) {
    if(dynamic_cast<Sensor::DistanceCoveredSensor*>(sensor)){
        Sensor::DistanceCoveredSensor* distanceCoveredSensor = static_cast<Sensor::DistanceCoveredSensor*>(sensor);

        modifyWindow = new ModifySensorDialogueWindow(distanceCoveredSensor->getIdentifier(), distanceCoveredSensor->getName(), 
                                                      distanceCoveredSensor->getMinValue(), 
                                                      distanceCoveredSensor->getMaxValue(), distanceCoveredSensor->getMean(), 
                                                      distanceCoveredSensor->getVariance(), distanceCoveredSensor->getLambda());

        connect(modifyWindow, &ModifySensorDialogueWindow::applySignal, this, &AboveChartWidget::applyChangesSlot);
        connect(this, &AboveChartWidget::finallyYouCanApplyChanges, modifyWindow, &ModifySensorDialogueWindow::applyChanges);
        connect(modifyWindow, &ModifySensorDialogueWindow::sensorModified, this, &AboveChartWidget::saveModifySlot);
        connect(modifyWindow, &ModifySensorDialogueWindow::sensorNameModified, this, &AboveChartWidget::nameModifiedSlot);

        modifyWindow->exec();
    }
    else if(dynamic_cast<Sensor::Chronometer*>(sensor)){
        Sensor::Chronometer* chronometer = static_cast<Sensor::Chronometer*>(sensor);

        modifyWindow = new ModifySensorDialogueWindow(chronometer->getIdentifier(), chronometer->getName(), chronometer->getMinValue(), 
                                                      chronometer->getMaxValue(), chronometer->getMean(), 
                                                      chronometer->getVariance(), chronometer->getLambda());

        connect(modifyWindow, &ModifySensorDialogueWindow::applySignal, this, &AboveChartWidget::applyChangesSlot);
        connect(this, &AboveChartWidget::finallyYouCanApplyChanges, modifyWindow, &ModifySensorDialogueWindow::applyChanges);
        connect(modifyWindow, &ModifySensorDialogueWindow::sensorModified, this, &AboveChartWidget::saveModifySlot);
        connect(modifyWindow, &ModifySensorDialogueWindow::sensorNameModified, this, &AboveChartWidget::nameModifiedSlot);

        modifyWindow->exec();
    }
    else if(dynamic_cast<Sensor::SpeedSensor*>(sensor)){
        Sensor::SpeedSensor* speedSensor = static_cast<Sensor::SpeedSensor*>(sensor);

        modifyWindow = new ModifySensorDialogueWindow(speedSensor->getIdentifier(), speedSensor->getName(), speedSensor->getDistanceCoveredSensor().getMinValue(), 
                                                      speedSensor->getDistanceCoveredSensor().getMaxValue(), speedSensor->getDistanceCoveredSensor().getMean(), 
                                                 speedSensor->getDistanceCoveredSensor().getVariance(), speedSensor->getDistanceCoveredSensor().getLambda());

        connect(modifyWindow, &ModifySensorDialogueWindow::applySignal, this, &AboveChartWidget::applyChangesSlot);
        connect(this, &AboveChartWidget::finallyYouCanApplyChanges, modifyWindow, &ModifySensorDialogueWindow::applyChanges);
        connect(modifyWindow, &ModifySensorDialogueWindow::sensorModified, this, &AboveChartWidget::saveModifySlot);
        connect(modifyWindow, &ModifySensorDialogueWindow::sensorNameModified, this, &AboveChartWidget::nameModifiedSlot);

        modifyWindow->exec();
    }
    else if(dynamic_cast<Sensor::Accelerometer*>(sensor)){
        Sensor::Accelerometer* accelerometer = static_cast<Sensor::Accelerometer*>(sensor);

        modifyWindow = new ModifySensorDialogueWindow(accelerometer->getIdentifier(), accelerometer->getName(), accelerometer->getChronometer().getMinValue(), 
                                                      accelerometer->getChronometer().getMaxValue(), accelerometer->getChronometer().getMean(), 
                                                      accelerometer->getChronometer().getVariance(), accelerometer->getChronometer().getLambda());

        connect(modifyWindow, &ModifySensorDialogueWindow::applySignal, this, &AboveChartWidget::applyChangesSlot);
        connect(this, &AboveChartWidget::finallyYouCanApplyChanges, modifyWindow, &ModifySensorDialogueWindow::applyChanges);
        connect(modifyWindow, &ModifySensorDialogueWindow::sensorModified, this, &AboveChartWidget::saveModifySlot);
        connect(modifyWindow, &ModifySensorDialogueWindow::sensorNameModified, this, &AboveChartWidget::nameModifiedSlot);

        modifyWindow->exec();
    }
}

void AboveChartWidget::applyChangesSlot(){
    emit applyChangesSignal();
}

void AboveChartWidget::youCanCheckIfNameIsUnique(const std::vector<Sensor::AbstractSensor*>& sensors){
    emit finallyYouCanApplyChanges(sensors);
}

void AboveChartWidget::saveModifySlot(const std::string& name, const double& min_value, const double& max_value, const double& mean, const double& variance, 
                                      const double& lambda){
    emit saveModifySignal(name, min_value, max_value, mean, variance, lambda);
}

void AboveChartWidget::saveModify(Sensor::AbstractSensor* sensor, const std::string& name, const double& min_value, const double& max_value, 
                                  const double& mean, const double& variance, const double& lambda) {
    if(dynamic_cast<Sensor::DistanceCoveredSensor*>(sensor)){
        Sensor::DistanceCoveredSensor* distanceCoveredSensor = static_cast<Sensor::DistanceCoveredSensor*>(sensor);

        distanceCoveredSensor->setName(name);
        distanceCoveredSensor->setMinValue(min_value);
        distanceCoveredSensor->setMaxValue(max_value);
        distanceCoveredSensor->setMean(mean);
        distanceCoveredSensor->setVariance(variance);
        distanceCoveredSensor->setLambda(lambda);
    }
    else if(dynamic_cast<Sensor::Chronometer*>(sensor)){
        Sensor::Chronometer* chronometer = static_cast<Sensor::Chronometer*>(sensor);

        chronometer->setName(name);
        chronometer->setMinValue(min_value);
        chronometer->setMaxValue(max_value);
        chronometer->setMean(mean);
        chronometer->setVariance(variance);
        chronometer->setLambda(lambda);
    }
    else if(dynamic_cast<Sensor::SpeedSensor*>(sensor)){
        Sensor::SpeedSensor* speedSensor = static_cast<Sensor::SpeedSensor*>(sensor);

        speedSensor->setName(name);

        speedSensor->getDistanceCoveredSensor_NON_Const().setMinValue(min_value);
        speedSensor->getDistanceCoveredSensor_NON_Const().setMaxValue(max_value);
        speedSensor->getDistanceCoveredSensor_NON_Const().setMean(mean);
        speedSensor->getDistanceCoveredSensor_NON_Const().setVariance(variance);
        speedSensor->getDistanceCoveredSensor_NON_Const().setLambda(lambda);

        speedSensor->getChronometer_NON_Const().setMinValue(min_value);
        speedSensor->getChronometer_NON_Const().setMaxValue(max_value);
        speedSensor->getChronometer_NON_Const().setMean(mean);
        speedSensor->getChronometer_NON_Const().setVariance(variance);
        speedSensor->getChronometer_NON_Const().setLambda(lambda);
    }
    else if(dynamic_cast<Sensor::Accelerometer*>(sensor)){
        Sensor::Accelerometer* accelerometer = static_cast<Sensor::Accelerometer*>(sensor);

        accelerometer->setName(name);

        accelerometer->getChronometer_NON_Const().setMinValue(min_value);
        accelerometer->getChronometer_NON_Const().setMaxValue(max_value);
        accelerometer->getChronometer_NON_Const().setMean(mean);
        accelerometer->getChronometer_NON_Const().setVariance(variance);
        accelerometer->getChronometer_NON_Const().setLambda(lambda);

        accelerometer->getSpeedSensor_NON_Const().getDistanceCoveredSensor_NON_Const().setMinValue(min_value);
        accelerometer->getSpeedSensor_NON_Const().getDistanceCoveredSensor_NON_Const().setMaxValue(max_value);
        accelerometer->getSpeedSensor_NON_Const().getDistanceCoveredSensor_NON_Const().setMean(mean);
        accelerometer->getSpeedSensor_NON_Const().getDistanceCoveredSensor_NON_Const().setVariance(variance);
        accelerometer->getSpeedSensor_NON_Const().getDistanceCoveredSensor_NON_Const().setLambda(lambda);

        accelerometer->getSpeedSensor_NON_Const().getChronometer_NON_Const().setMinValue(min_value);
        accelerometer->getSpeedSensor_NON_Const().getChronometer_NON_Const().setMaxValue(max_value);
        accelerometer->getSpeedSensor_NON_Const().getChronometer_NON_Const().setMean(mean);
        accelerometer->getSpeedSensor_NON_Const().getChronometer_NON_Const().setVariance(variance);
        accelerometer->getSpeedSensor_NON_Const().getChronometer_NON_Const().setLambda(lambda);
    }

    // Adesso faccio l'update del widget AboveChartWidget, cioè lo aggiorno tramite i setter
    setSensorNameLabel(name);
    setMinValueLabel(min_value);
    setMaxValueLabel(max_value);
    setMeanLabel(mean);
    setVarianceLabel(variance);
    setLambdaLabel(lambda);

    // Rendo la finestra principale consapevole del fatto che sono avvenute delle modifiche
    emit setIsSaved(false);
}

void AboveChartWidget::nameModifiedSlot(const std::string& previousName, const std::string& newName){
    emit nameHasBeenModified(previousName, newName);
}

void AboveChartWidget::deleteSlot() {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Elimina sensore", "Vuoi eliminare definitivamente questo sensore?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit sensorDeleted();
    }
}

void AboveChartWidget::simulateSlot() {
    emit simulate();
}

void AboveChartWidget::setSensorNameLabel(const std::string& name){
    sensorNameLabel->setText(QString::fromStdString(name));
}

void AboveChartWidget::setMinValueLabel(const double& min_value){
    minValueLabel->setText("Minimo: " + QString::number(min_value));
}

void AboveChartWidget::setMaxValueLabel(const double& max_value){
    maxValueLabel->setText("Massimo: " + QString::number(max_value));
}

void AboveChartWidget::setMeanLabel(const double& mean){
    meanLabel->setText("Media: " + QString::number(mean));
}

void AboveChartWidget::setVarianceLabel(const double& variance){
    varianceLabel->setText("Varianza: " + QString::number(variance));
}

void AboveChartWidget::setLambdaLabel(const double& lambda){
    lambdaLabel->setText("Lambda: " + QString::number(lambda));
}

AboveChartWidget::~AboveChartWidget() {
    delete greyPanel;

    delete sensorNameLabel;
    delete sensorIDLabel;
    delete embeddedSensorsLabel;
    delete minValueLabel;
    delete maxValueLabel;
    delete meanLabel;
    delete varianceLabel;
    delete lambdaLabel;
    delete airplaneEnabledLabel;

    delete simulateButton;
    delete modifyButton;
    delete deleteButton;

    delete modifyWindow;

    delete layout;
}

}
