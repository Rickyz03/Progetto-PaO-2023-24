#include "MainWindow.h"
#include <stdexcept>

namespace View {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), repository(nullptr), isSaved(true), centralWidget(nullptr), mainLayout(nullptr), centralLayout(nullptr), chartLayout(nullptr), 
    toolBar(nullptr), sensorPanel(nullptr), aboveChartWidget(nullptr), chartWidget(nullptr), statusBar(nullptr)
{
    setWindowTitle("Aerosimulator");

    mainLayout = new QVBoxLayout;
    centralLayout = new QHBoxLayout;
    chartLayout = new QVBoxLayout;

    toolBar = new ToolBar();
    sensorPanel = new SensorPanel(sensors, this);
    aboveChartWidget = new AboveChartWidget(this);
    chartWidget = new ChartWidget(this);
    statusBar = new StatusBar();

    toolBar->setFixedSize(1024, 30);
    sensorPanel->setFixedSize(310, 506);
    aboveChartWidget->setFixedSize(714, 85);
    chartWidget->setFixedSize(714,421);
    statusBar->setFixedSize(1024, 20);

    chartLayout->addWidget(aboveChartWidget);
    chartLayout->addWidget(chartWidget);
    
    centralLayout->addWidget(sensorPanel);
    centralLayout->addLayout(chartLayout);

    mainLayout->addWidget(toolBar);
    mainLayout->addLayout(centralLayout);
    mainLayout->addWidget(statusBar);

    // Sets main panel
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(mainLayout);
    

    connect(toolBar, &ToolBar::openSignal, this, &MainWindow::openHandler);
    connect(toolBar, &ToolBar::saveSignal, this, &MainWindow::saveHandler);
    connect(toolBar, &ToolBar::saveAsSignal, this, &MainWindow::saveAsHandler);
    connect(toolBar, &ToolBar::fileOpened, this, &MainWindow::fileOpenedHandler);
    connect(toolBar, &ToolBar::setIsSaved, this, &MainWindow::setIsSaved);

    connect(sensorPanel, &SensorPanel::areThereAnySensors, this, &MainWindow::checkIfAreThereAnySensors);
    connect(sensorPanel, &SensorPanel::searchSignal, this, &MainWindow::searchHandler);
    //connect(sensorPanel, &SensorPanel::oneCharacterSearch, this, &MainWindow::oneCharacterSearchHandler);
    connect(sensorPanel, &SensorPanel::searchResults, this, &MainWindow::searchResultsHandler);
    connect(sensorPanel, &SensorPanel::returnBackSignal, this, &MainWindow::returnBackHandler);
    connect(sensorPanel, &SensorPanel::sensorSelected, this, &MainWindow::sensorSelectedHandler);
    connect(sensorPanel, &SensorPanel::sensorAdded, this, &MainWindow::sensorAddedHandler);
    connect(sensorPanel, &SensorPanel::createAndAddSensorSignal, this, &MainWindow::createAndAddSensorHandler);
    connect(this, &MainWindow::youCanCheckIfNameAndIDAreUnique, sensorPanel, &SensorPanel::youCanCheckIfNameAndIDAreUnique);

    connect(aboveChartWidget, &AboveChartWidget::modifySignal, this, &MainWindow::modifyHandler);
    connect(aboveChartWidget, &AboveChartWidget::applyChangesSignal, this, &MainWindow::applyChangesHandler);
    connect(this, &MainWindow::youCanCheckIfNameIsUnique, aboveChartWidget, &AboveChartWidget::youCanCheckIfNameIsUnique);
    connect(aboveChartWidget, &AboveChartWidget::saveModifySignal, this, &MainWindow::saveModifyHandler);
    connect(aboveChartWidget, &AboveChartWidget::setIsSaved, this, &MainWindow::setIsSaved);
    connect(aboveChartWidget, &AboveChartWidget::nameHasBeenModified, this, &MainWindow::nameModifiedHandler);
    connect(aboveChartWidget, &AboveChartWidget::sensorDeleted, this, &MainWindow::sensorDeletedHandler);
    connect(aboveChartWidget, &AboveChartWidget::simulate, this, &MainWindow::simulationHandler);

    connect(chartWidget, &ChartWidget::accelerationLineColor, this, &MainWindow::afterAccelerationSimulationHandler);
}

bool MainWindow::maybeSave(){
    if(sensors.empty() && repository==nullptr)  // Se si ha creato roba a caso e poi la si ha eliminata tutta, senza collegarsi a un JSON, 
    {                                           // non ha senso proporre di archiviare qualcosa! Quindi, si può chiudere la finestra
        return true;
    }

    if (! isSaved) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, "Applicazione", "Salvare le modifiche non salvate?",
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (ret == QMessageBox::Cancel) {
            return false;
        }
        // Da qui in poi si entra se e solo se il tasto cliccato non è "Cancel"

        if (ret == QMessageBox::Save) {
            toolBar->saveJsonFile(sensors, repository);
        } 
        // Se l'utente ha cliccato su "Discard", non avviene il salvataggio

        /* Importante approfondire questa possibilità per il caso in cui l'utente clicchi "Apri" e scarti le modifiche fatte in precedenza, però poi non 
        selezioni nessun nuovo file. E anche serve per poter così aprire un nuovo file senza avere il bug in cui il sensore selezionato in precedenza aveva 
        lo stesso ID*/
        sensors.clear();
        delete repository;     // L'utente, appena clicca "Apri", ha scelto definitivamente di uscire da quel repository,
        repository = nullptr;  // a prescindere dal fatto che poi ne scelga un altro o meno.
        sensorPanel->createPanel(sensors);
        aboveChartWidget->createGreyPanel();
        chartWidget->initialChartWidget();
        setIsSaved(true);
        toolBar->disactivateSaveAsAction();
    }

    return true;
}

Sensor::AbstractSensor* MainWindow::getCurrentlySelectedSensor() {
    try{
        unsigned int id = aboveChartWidget->getId();

        for(Sensor::AbstractSensor* sensor : sensors){
            if(sensor->getIdentifier() == id){
                return sensor;
            }
        }

        // Se l'id non corrisponde a nessun sensore
        return nullptr;
    }
    catch(const std::exception& e){ // Se non c'è nessun sensore selezionato in AboveChartWidget (oppure l'ID non è un unsigned int)
        return nullptr;
    }
}

void MainWindow::setSensors() {
    if(!sensors.empty()){
        for (Sensor::AbstractSensor* sensor : sensors) {
            delete sensor;
        }
        sensors.clear();
    }

    std::vector<Sensor::AbstractSensor*> new_sensors(repository->readAll());
    for (Sensor::AbstractSensor* sensor : new_sensors) {
        sensors.push_back(sensor->clone());
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore(); // Se l'utente ha cliccato su "Cancel", non avviene la chiusura
    }
}

void MainWindow::openHandler(){
    if(maybeSave()) // Se l'utente ha cliccato su "Cancel", non avviene l'apertura
        toolBar->openJsonFile(repository);
}

void MainWindow::saveHandler(){
    toolBar->saveJsonFile(sensors, repository);
}

void MainWindow::saveAsHandler(){
    toolBar->saveJsonFileAs(sensors, repository);
}

void MainWindow::fileOpenedHandler(){
    // Aggiorno sensors
    setSensors();

    // Creo (o ricreo) il SensorPanel
    sensorPanel->createPanel(sensors);

    // Seleziono (non occorre controllare che il file sia vuoto, perchè non si possono creare file vuoti (e dunque non ce ne sono da aprire))
    sensorSelectedHandler(sensors[0]->getIdentifier());

    // Aggiorno la StatusBar
    statusBar->updateBecauseSensorPanelIsNotEmpty();

    // Accendo il pulsante "Salva con nome". Non "Salva" perchè, siccome abbiamo appena aperto, è ancora tutto salvato!
    toolBar->activateSaveAsAction();
}

void MainWindow::setIsSaved(const bool& value){
    isSaved = value;

    if(isSaved == true)
        toolBar->disactivateSaveAction();
    else
        toolBar->activateSaveAction();
}

void MainWindow::checkIfAreThereAnySensors(){
    sensorPanel->afterTextChanged(! sensors.empty());
}

void MainWindow::searchHandler(){
    sensorPanel->updateSearchResults(sensors);
}

/*void MainWindow::oneCharacterSearchHandler(){
    statusBar->updateAfterOneCharacterSearched();
}*/

void MainWindow::searchResultsHandler(const std::vector<SensorWidget*>& sensorWidgets){
    if(sensorWidgets.empty()){
        aboveChartWidget->createGreyPanel();
        chartWidget->initialChartWidget();
        statusBar->updateAfterResearch(0);
    }
    else{
        sensorPanel->handleSensorWidgetSelected(sensorWidgets[0]);
        statusBar->updateAfterResearch(sensorWidgets.size());
    }
}

void MainWindow::returnBackHandler(){
    sensorPanel->createPanel(sensors);

    /* Bisogna controllare se il vector "sensors" è vuoto o meno, perchè l'utente potrebbe aver eliminato tutti i sensori risultati di ricerca, che, fatalità, 
    potrebbero essere stati coincidenti con tutti i sensori di "sensors", e quindi avrebbe svuotato il vector */
    if(! sensors.empty())
        sensorSelectedHandler(sensors[0]->getIdentifier());
}

void MainWindow::sensorSelectedHandler(const unsigned int& id)  // Sono costretto a usare l'id perchè il SensorPanel non ha accesso al sensore selezionato, 
{                                                                    // solo al suo id, perchè lo legge dall'etichetta
    Sensor::AbstractSensor* currentSensor = getCurrentlySelectedSensor();

    if(currentSensor==nullptr)   // Se al momento non è selezionato nessun sensore (o schermata vuota oppure sensore appena eliminato), posso tranquillamente 
    {                            // visualizzare il sensore selezionato
        for(Sensor::AbstractSensor* sensor : sensors){
            if(sensor->getIdentifier() == id){
                sensorPanel->setColors(nullptr, sensor);
                aboveChartWidget->createAboveChartForSensor(sensor);
                chartWidget->chartWidgetOnSelection(sensor);
                statusBar->updateAfterSensorSelected();
                return;
            }
        }
    }
    
    if(id != currentSensor->getIdentifier())  // Se è stato cliccato un sensore diverso dall'attuale, avviene un change 
    {                                                        // delle schermate che stanno a destra, altrimenti il click risulterà inutile
        for(Sensor::AbstractSensor* sensor : sensors){
            if(sensor->getIdentifier() == id){
                sensorPanel->setColors(currentSensor, sensor);
                aboveChartWidget->createAboveChartForSensor(sensor);
                chartWidget->chartWidgetOnSelection(sensor);
                statusBar->updateAfterSensorSelected();
                return;
            }
        }
    }
    else{
        for(Sensor::AbstractSensor* sensor : sensors){
            if(sensor->getIdentifier() == id){
                sensorPanel->setColors(currentSensor, sensor); // Serve comunque aggiornare il colore, perchè sennò quando avviene una ricerca successiva
                                                               // ad un'altra ricerca, si ricrea il pannello ed è importante che si resetti anche il colore
                statusBar->updateAfterSensorSelected(); // Serve anche aggiornare la status bar, quando si torna indietro da una ricerca
                return;
            }
        }
    }  
}

void MainWindow::sensorAddedHandler(Sensor::AbstractSensor* sensor){
    // Aggiunta a sensors in coda
    sensors.push_back(sensor);

    // Refresh del SensorPanel. Se si stava visualizzando i risultati di ricerca, essi spariscono, e si torna al pannello che visualizza tutti i sensori
    sensorPanel->createPanel(sensors);

    // Seleziono il sensore appena creato
    sensorSelectedHandler(sensor->getIdentifier());

    // Attivo il pulsante "Salva"
    setIsSaved(false);

    // Se questo è il primo sensore aggiunto, attivo il pulsante "Salva con nome"
    if(sensors.size() == 1)
        toolBar->activateSaveAsAction();
}

void MainWindow::createAndAddSensorHandler(){
    emit youCanCheckIfNameAndIDAreUnique(sensors);
}

void MainWindow::modifyHandler(){
    aboveChartWidget->modify(getCurrentlySelectedSensor());
}

void MainWindow::applyChangesHandler(){
    emit youCanCheckIfNameIsUnique(sensors);
}

void MainWindow::saveModifyHandler(const std::string& name, const double& min_value, const double& max_value, const double& mean, const double& variance, 
                                   const double& lambda){
    aboveChartWidget->saveModify(getCurrentlySelectedSensor(), name, min_value, max_value, mean, variance, lambda);
}

void MainWindow::nameModifiedHandler(const std::string& previousName, const std::string& newName){
    sensorPanel->modifyOneName(previousName, newName);
}

void MainWindow::sensorDeletedHandler(){
    // Eliminazione del sensore corrente
    Sensor::AbstractSensor* sensor = getCurrentlySelectedSensor();
    auto it = sensors.begin();
    for( ; it != sensors.end(); ++it){
        if(sensor->getIdentifier() == (*it)->getIdentifier()){
            delete *it;
            it = sensors.erase(it);
            break;
        }
    }

    // Faccio il refresh del SensorPanel
    sensorPanel->createPanel(sensors);  // Il controllo se "sensors" è vuoto viene già eseguito dentro la funzione "createPanel"

    if(! sensors.empty()){
        // Se il sensore eliminato non era l'ultimo sensore, allora seleziona il successivo, mentre se era l'ultimo si deve per forza selezionare il precedente
        if(it != sensors.end())
            sensorSelectedHandler((*it)->getIdentifier());
        else{
            it--;
            sensorSelectedHandler((*it)->getIdentifier());
        }
    }
    else{ // Se "sensors" è vuoto, ricrea la schermata iniziale
        aboveChartWidget->createGreyPanel();
        chartWidget->initialChartWidget();
        statusBar->updateBecauseSensorPanelIsEmpty();

        // Visto che l'utente ha eliminato tutti i sensori, viene disattivato il pulsante "Salva con nome"
        toolBar->disactivateSaveAsAction();

        if(repository==nullptr)                 // Se si ha creato roba a caso e poi la si ha eliminata tutta, senza collegarsi a un JSON,
        {                                       // non ha senso proporre di archiviare qualcosa! Quindi, viene disattivato "Salva"
            toolBar->disactivateSaveAction(); 
            return;                             // Finisco qui, altrimenti la riga finale di questo metodo renderebbe inutile la disattivazione
        }
    }  

    // Attivo il pulsante "Salva"
    setIsSaved(false);
}

void MainWindow::simulationHandler(){
    if(dynamic_cast<Sensor::DistanceCoveredSensor*>(getCurrentlySelectedSensor())){
        chartWidget->insertDistanceChart(static_cast<Sensor::DistanceCoveredSensor*>(getCurrentlySelectedSensor()));
        statusBar->updateAfterSimulation();
    }
    else if(dynamic_cast<Sensor::Chronometer*>(getCurrentlySelectedSensor())){
        chartWidget->insertChronoChart(static_cast<Sensor::Chronometer*>(getCurrentlySelectedSensor()));
        statusBar->updateAfterSimulation();
    }
    else if(dynamic_cast<Sensor::SpeedSensor*>(getCurrentlySelectedSensor())){
        chartWidget->insertSpeedChart(static_cast<Sensor::SpeedSensor*>(getCurrentlySelectedSensor()));
        statusBar->updateAfterSimulation();
    }
    else if(dynamic_cast<Sensor::Accelerometer*>(getCurrentlySelectedSensor()))
        chartWidget->insertAccelerationChart(static_cast<Sensor::Accelerometer*>(getCurrentlySelectedSensor()));
}

void MainWindow::afterAccelerationSimulationHandler(const Sensor::Accelerometer& accelerometer, const bool& isLineRed){
    aboveChartWidget->recreateAfterAccelerometerSimulation(const_cast<Sensor::Accelerometer*>(&accelerometer), isLineRed);
    statusBar->updateAfterAccelerometerSimulation(isLineRed);
}

MainWindow::~MainWindow()        // Solo alla chiusura dell'app la MainWindow viene eliminata, non c'è mai una sovrascrizione a runtime,
{                                // quindi posso mettere i delete solo nel distruttore e non anche all'inizio del costruttore
    for(Sensor::AbstractSensor* sensor : sensors){ delete sensor; }
    sensors.clear();
    delete repository;

    delete toolBar;
    delete sensorPanel;
    delete aboveChartWidget;
    delete chartWidget;
    delete statusBar;

    delete chartLayout;
    delete centralLayout;
    delete mainLayout;
    delete centralWidget;
}

}