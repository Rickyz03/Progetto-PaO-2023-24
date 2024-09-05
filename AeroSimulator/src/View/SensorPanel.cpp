#include "SensorPanel.h"
#include "SetTypeAndIconOfSensorWidgetVisitor.h"
#include <stdexcept>

namespace View {

SensorPanel::SensorPanel(const std::vector<Sensor::AbstractSensor*>& sensors, QWidget *parent)
    : QWidget(parent), mainLayout(nullptr), searchLayout(nullptr), searchBar(nullptr), //goButton(nullptr), 
      returnBackButton(nullptr), sensorLayout(nullptr), scrollArea(nullptr), sensorWidgetContainer(nullptr), 
      addSensorButton(nullptr), addWindow(nullptr), sensorWidget(nullptr)
{
    createPanel(sensors);
}

void SensorPanel::createPanel(const std::vector<Sensor::AbstractSensor*>& sensors)
{
    // Rimozione degli oggetti allocati dinamicamente in precedenza
    delete searchBar; delete returnBackButton; //delete goButton;
    for(SensorWidget* widget : sensorWidgets) { delete widget; } sensorWidgets.clear(); delete addSensorButton; delete addWindow; 
    delete sensorLayout; delete sensorWidgetContainer; delete scrollArea; delete searchLayout; delete mainLayout;

    // Piazzo a nullptr i puntatori i cui oggetti puntati sono stati appena disallocati
    searchBar = nullptr; returnBackButton = nullptr; // goButton = nullptr;
    addSensorButton = nullptr; addWindow = nullptr; sensorLayout = nullptr; sensorWidgetContainer = nullptr; scrollArea = nullptr;
    searchLayout = nullptr; mainLayout = nullptr;


    // La barra di ricerca

    searchBar = new QLineEdit(this);
    searchBar->setEnabled(false); // Disabilita il QLineEdit all'avvio

    //goButton = new QPushButton(QIcon("Assets/Pulsanti/Vai.svg"), "", this);
    //goButton->setShortcut(Qt::Key_Return);
    //goButton->setFixedSize(30, 25);

    returnBackButton = new QPushButton(QIcon("Assets/Pulsanti/Ritorna_indietro.svg"), "", this);
    returnBackButton->setShortcut(Qt::Key_Escape);
    returnBackButton->setFixedSize(30, 25);

    //goButton->setEnabled(false);
    returnBackButton->setEnabled(false);

    searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchBar);
    searchLayout->addWidget(returnBackButton);
    //searchLayout->addWidget(goButton);


    // Il vero e proprio pannello dei sensori

    scrollArea = new QScrollArea(this);

    if(! sensors.empty()){

        sensorLayout = new QVBoxLayout();

        for (Sensor::AbstractSensor *sensor : sensors) {
            sensorWidget = new SensorWidget(this);
            sensorWidget->setName(QString::fromStdString(sensor->getName()));
            sensorWidget->setId(sensor->getIdentifier());

            SetTypeAndIconOfSensorWidgetVisitor setTypeAndIconOfSensorWidgetVisitor(this);
            sensor->accept(setTypeAndIconOfSensorWidgetVisitor);

            sensorLayout->addWidget(sensorWidget);
            sensorWidgets.push_back(sensorWidget); // Aggiunta al vettore SensorWidgets

            // Ora che ha fatto la copia shallow, sensorWidget può "staccare la sua freccia"
            sensorWidget = nullptr;
        }

        sensorWidgetContainer = new QWidget();
        sensorWidgetContainer->setLayout(sensorLayout);
        scrollArea->setWidget(sensorWidgetContainer);

    }


    // Il pulsante "Aggiungi"

    addSensorButton = new QPushButton(QIcon("Assets/Pulsanti/Aggiungi.svg"), tr("Aggiungi"), this);
    addSensorButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_A));
    addSensorButton->setStyleSheet("text-align: center; padding-right: 15px;");


    mainLayout = new QVBoxLayout(this);
    
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(addSensorButton);


    //connect(goButton, &QPushButton::clicked, this, &SensorPanel::search);
    connect(returnBackButton, &QPushButton::clicked, this, &SensorPanel::returnBackFromSearch);
    connect(addSensorButton, &QPushButton::clicked, this, &SensorPanel::addSensorSlot);

    connect(searchBar, &QLineEdit::textChanged, this, &SensorPanel::afterTextChangedSlot);
    
    for (SensorWidget* sensorWidget : sensorWidgets) {
        connect(sensorWidget, &SensorWidget::selected, this, &SensorPanel::handleSensorWidgetSelected);
    }
}

void SensorPanel::updateSearchResults(const std::vector<Sensor::AbstractSensor*>& sensors) {
    for(SensorWidget* widget : sensorWidgets) { delete widget; }
    sensorWidgets.clear();

    delete sensorLayout; delete sensorWidgetContainer;
    sensorLayout = nullptr; sensorWidgetContainer = nullptr;


    QString searchString = searchBar->text();

    // Mappa per associare ogni sensore alla lunghezza della sottostringa comune più lunga
    QMultiMap<int, Sensor::AbstractSensor*> sensorMatchLengthMap;

    // Calcola la sottostringa comune più lunga per ciascun sensore
    for (auto it = sensors.rbegin(); it != sensors.rend(); ++it) {
        Sensor::AbstractSensor* sensor = *it;
        int maxLength = 0;
        QString sensorName = QString::fromStdString(sensor->getName());
        QString sensorId = QString::number(sensor->getIdentifier());
        QString sensorType;
        if(dynamic_cast<Sensor::DistanceCoveredSensor*>(sensor))
            sensorType = "DistanceCoveredSensor";
        else if(dynamic_cast<Sensor::Chronometer*>(sensor))
            sensorType = "Chronometer";
        else if(dynamic_cast<Sensor::SpeedSensor*>(sensor))
            sensorType = "SpeedSensor";
        else
            sensorType = "Accelerometer";

        // Calcola la lunghezza della sottostringa comune più lunga tra il nome, l'ID e il tipo del sensore
        int nameMatchLength = findLengthOfLongestCommonSubstring(searchString, sensorName);
        int idMatchLength = findLengthOfLongestCommonSubstring(searchString, sensorId);
        int typeMatchLength = findLengthOfLongestCommonSubstring(searchString, sensorType);

        int matchLength = qMax(nameMatchLength, qMax(idMatchLength, typeMatchLength));

        if(searchString.length()==1){
            // Aggiorna la lunghezza massima della sottostringa comune più lunga.
            if (matchLength > maxLength)
                maxLength = matchLength;

            // Associa il sensore alla lunghezza della sottostringa comune più lunga, se essa è diversa da 0
            if(maxLength != 0)
                sensorMatchLengthMap.insert(maxLength, sensor);
            }
        else{ // Adesso considero solo un match maggiore uguale della metà della stringa di ricerca, perchè sennò non è una ricerca seria e selettiva
            if (matchLength>=(searchString.length()/2) && matchLength > maxLength)
                maxLength = matchLength;

            if(maxLength >= (searchString.length()/2))
                sensorMatchLengthMap.insert(maxLength, sensor);
        }
    }

    // Creo una lista che preleva le chiavi della mappa multipla
    QList<int> sortedKeys = sensorMatchLengthMap.keys();

    // Rimuovi i duplicati dalla lista
    sortedKeys.erase(std::unique(sortedKeys.begin(), sortedKeys.end()), sortedKeys.end());

    // Ordina le chiavi della mappa multipla in modo crescente basandosi sulla lunghezza della sottostringa comune più lunga
    std::sort(sortedKeys.begin(), sortedKeys.end());

    sensorLayout = new QVBoxLayout();

    // Aggiunge i sensori al layout della scroll area in base all'ordinamento
    for (int i = sortedKeys.size() - 1; i >= 0; --i) {
        // Preleva i sensori corrispondenti alla chiave, che potrebbero essere più di uno siccome sto usando una QMultiMap
        std::vector<Sensor::AbstractSensor*> sensorsForKey = getSensorsForKey(sensorMatchLengthMap, sortedKeys[i]);
        
        for(Sensor::AbstractSensor* sensor : sensorsForKey){
            // Crea un widget per visualizzare il sensore
            sensorWidget = new SensorWidget(this);

            sensorWidget->setName(QString::fromStdString(sensor->getName()));
            sensorWidget->setId(sensor->getIdentifier());

            SetTypeAndIconOfSensorWidgetVisitor setTypeAndIconOfSensorWidgetVisitor(this);
            sensor->accept(setTypeAndIconOfSensorWidgetVisitor);

            sensorLayout->addWidget(sensorWidget);
            sensorWidgets.push_back(sensorWidget); // Aggiunta al vettore SensorWidgets

            // Ora che ha fatto la copia shallow, sensorWidget può "staccare la sua freccia"
            sensorWidget = nullptr;
        }
    }

    sensorWidgetContainer = new QWidget();
    sensorWidgetContainer->setLayout(sensorLayout);
    scrollArea->setWidget(sensorWidgetContainer);
    
    // Collega i segnali e gli slot per i nuovi sensorWidget aggiunti
    for (SensorWidget* sensorWidget : sensorWidgets) {
        connect(sensorWidget, &SensorWidget::selected, this, &SensorPanel::handleSensorWidgetSelected);
    }

    emit searchResults(sensorWidgets);
}

int SensorPanel::findLengthOfLongestCommonSubstring(const QString& str1, const QString& str2) {
    int m = str1.length();
    int n = str2.length();
    
    // Matrice per memorizzare la lunghezza delle sottostringhe comuni
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    
    // Lunghezza massima trovata finora
    int maxLength = 0;
    
    // Calcola la lunghezza delle sottostringhe comuni
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                maxLength = std::max(maxLength, dp[i][j]);
            }
        }
    }
    
    // Restituisce la lunghezza della sottostringa comune più lunga
    return maxLength;
}

// Funzione per estrarre i sensori associati a una specifica chiave dalla mappa multipla
std::vector<Sensor::AbstractSensor*> SensorPanel::getSensorsForKey(const QMultiMap<int, Sensor::AbstractSensor*>& sensorMap, int key) {
    std::vector<Sensor::AbstractSensor*> result;

    // Ottieni un intervallo di iteratori che copre tutti i valori associati alla chiave specificata
    auto range = sensorMap.equal_range(key);

    // Itera attraverso gli elementi nell'intervallo
    for (auto it = range.first; it != range.second; ++it) {
        result.push_back(it.value()); // Inserisci il sensore nel vettore
    }

    return result;
}

void SensorPanel::setTypeAndIconOfSensorWidget(const QString& type, const QIcon& icon){
    sensorWidget->setType(type);
    sensorWidget->setIcon(icon);
}

void SensorPanel::mousePressEvent(QMouseEvent *event){
    if (searchBar->rect().contains(event->pos())){
        // Se il clic del mouse è avvenuto all'interno della barra di ricerca, essa viene abilitata
        searchBar->setEnabled(true);
    }
    else
    {
        // Altrimenti, gestisci normalmente l'evento mousePressEvent
        QWidget::mousePressEvent(event);
    }
}

void SensorPanel::afterTextChangedSlot(){
    emit areThereAnySensors();
}

void SensorPanel::afterTextChanged(const bool& thereAreSensors)
{
    QString text = searchBar->text();

    if(thereAreSensors){
        if (text.isEmpty()) {
            //goButton->setEnabled(false);
            returnBackFromSearch();
        } 
        else {
            //goButton->setEnabled(true);
            search();
        }
    }
}

void SensorPanel::search(){
    //goButton->setEnabled(false);
    returnBackButton->setEnabled(true);

    // Non occorre controllare se c'è del testo nella searchBar, perchè, quando non c'è, il tasto "Go" ed Enter sono disattivati, quindi qui non ci arrivi
    QString searchString = searchBar->text();

    /*if(searchString.length() == 1){   // Ora che c'è l'aggiornamento live della ricerca non ha più senso un segnale dedicato se viene digitato un carattere
        emit oneCharacterSearch();      // perchè la ricerca live serve proprio per godersi la "magia" del numero di sensori del pannello che diminuisce
        return;                         // mano mano.
    }*/

    emit searchSignal();
}

void SensorPanel::returnBackFromSearch()
{
    searchBar->clear();
    
    //goButton->setEnabled(false);
    returnBackButton->setEnabled(false);

    emit returnBackSignal();
}

void SensorPanel::handleSensorWidgetSelected(SensorWidget* sender) {
    if (!sender) {
        qWarning() << "Il puntatore al widget del sensore è nullo!";
        return;
    }

    try{
        emit sensorSelected(sender->getId()); // Il segnale prende come argomento l'ID del sensore del widget appena selezionato
    }
    catch(const std::exception& e){ // Se l'ID non è un unsigned int, non è possibile continuare con la selezione, quindi non viene emesso nessun segnale
        return;
    }
}

void SensorPanel::addSensorSlot(){
    addWindow = new AddSensorDialogueWindow();
    
    connect(addWindow, &AddSensorDialogueWindow::createAndAddSignal, this, &SensorPanel::createAndAddSensorSlot);
    connect(this, &SensorPanel::finallyYouCanCreateAndAddSensor, addWindow, &AddSensorDialogueWindow::createAndAddSensor);
    connect(addWindow, &AddSensorDialogueWindow::sensorAdded, this, &SensorPanel::handleSensorAdded);

    addWindow->exec();
}

void SensorPanel::createAndAddSensorSlot(){
    emit createAndAddSensorSignal();
}

void SensorPanel::nowIGiveYouTheSensorsSoYouCanCheckIfNameAndIDAreUnique(const std::vector<Sensor::AbstractSensor*>& sensors){
    emit finallyYouCanCreateAndAddSensor(sensors);
}

void SensorPanel::handleSensorAdded(Sensor::AbstractSensor* sensor){
    /* Non posso aggiungere direttamente qua un sensorWidget del nuovo sensore perchè rischio di aggiungerlo quando sono presenti i risultati di una ricerca
       e allora aggingere il nuovo sensore in quell'insieme lì sarebbe sbagliato. Dunque, dalla MainWindow ho fatto fare un refresh perchè appaia il 
       SensorPanel predefinito che visualizza tutti i sensori */

    emit sensorAdded(sensor);
}

void SensorPanel::modifyOneName(const std::string& previousName, const std::string& newName){
    for (SensorWidget* sensorWidget : sensorWidgets) {
        // Se il nome corrente corrisponde a previousName, sostituisci con newName
        if (sensorWidget->getName() == previousName){
            sensorWidget->setName(QString::fromStdString(newName));
            return;
        }
    }
}

void SensorPanel::setColors(Sensor::AbstractSensor* previousCurrentSensor, Sensor::AbstractSensor* newCurrentSensor){
    try{
        if(previousCurrentSensor != nullptr){  // Se questo è il primo sensore creato, non c'è nessun predecessore selezionato
            // Ricerca del previousCurrentSensor tra i sensorWidgets
            for(SensorWidget* widget : sensorWidgets){
                if(widget->getId() == previousCurrentSensor->getIdentifier()){
                    widget->setBackgroundColor(QColor("#FFFFFF")); // Imposta il colore di sfondo del backgroundWidget a bianco
                    break;
                }
            }
        }

        // Ricerca del newCurrentSensor tra i sensorWidgets
        for(SensorWidget* widget : sensorWidgets){
            if(widget->getId() == newCurrentSensor->getIdentifier()){
                widget->setBackgroundColor(QColor("#CCCCCC")); // Imposta il colore di sfondo del backgroundWidget a grigio chiaro
                break;
            }
        }
    }
    catch(const std::exception& e){ // Se un ID non si legge, non viene cambiato nessun colore
        return;
    }
}

SensorPanel::~SensorPanel() {
    delete searchBar;
    //delete goButton;
    delete returnBackButton;

    for(SensorWidget* widget : sensorWidgets) { delete widget; }
    sensorWidgets.clear();

    delete addSensorButton;

    delete addWindow;

    delete sensorLayout;
    delete sensorWidgetContainer;
    delete scrollArea;
    delete searchLayout;
    delete mainLayout;
}

}
