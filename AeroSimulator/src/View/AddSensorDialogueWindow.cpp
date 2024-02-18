#include "AddSensorDialogueWindow.h"

namespace View {

AddSensorDialogueWindow::AddSensorDialogueWindow(AbstractDialogueWindow* parent) : AbstractDialogueWindow(parent) {
    setWindowTitle("Aggiungi sensore");

    mainLayout = new QVBoxLayout(this);

    typeLayout = new QHBoxLayout;
    typeLabel = new QLabel("Tipo:", this);
    typeComboBox = new QComboBox(this);
    typeComboBox->addItem("DistanceCoveredSensor");
    typeComboBox->addItem("Chronometer");
    typeComboBox->addItem("SpeedSensor");
    typeComboBox->addItem("Accelerometer");
    typeLayout->addWidget(typeLabel);
    typeLayout->addWidget(typeComboBox);

    idLayout = new QHBoxLayout;
    idLabel = new QLabel("ID:", this);
    idLineEdit = new QLineEdit(this);
    idLineEdit->setFixedSize(193, 26);
    idLayout->addWidget(idLabel);
    idLayout->addWidget(idLineEdit);

    nameLayout = new QHBoxLayout;
    nameLabel = new QLabel("Nome:", this);
    nameLineEdit = new QLineEdit(this);
    nameLineEdit->setFixedSize(193, 26);
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameLineEdit);

    minLayout = new QHBoxLayout;
    minLabel = new QLabel("Minimo (Facoltativo):", this);
    minLineEdit = new QLineEdit(this);
    minLineEdit->setFixedSize(193, 26);
    minLayout->addWidget(minLabel);
    minLayout->addWidget(minLineEdit);

    maxLayout = new QHBoxLayout;
    maxLabel = new QLabel("Massimo (Facoltativo):", this);
    maxLineEdit = new QLineEdit(this);
    maxLineEdit->setFixedSize(193, 26);
    maxLayout->addWidget(maxLabel);
    maxLayout->addWidget(maxLineEdit);

    meanLayout = new QHBoxLayout;
    meanLabel = new QLabel("Media (Facoltativa):", this);
    meanLineEdit = new QLineEdit(this);
    meanLineEdit->setFixedSize(193, 26);
    meanLayout->addWidget(meanLabel);
    meanLayout->addWidget(meanLineEdit);

    varianceLayout = new QHBoxLayout;
    varianceLabel = new QLabel("Varianza (Facoltativa):", this);
    varianceLineEdit = new QLineEdit(this);
    varianceLineEdit->setFixedSize(193, 26);
    varianceLayout->addWidget(varianceLabel);
    varianceLayout->addWidget(varianceLineEdit);

    lambdaLayout = new QHBoxLayout;
    lambdaLabel = new QLabel("Lambda (Facoltativa):", this);
    lambdaLineEdit = new QLineEdit(this);
    lambdaLineEdit->setFixedSize(193, 26);
    lambdaLayout->addWidget(lambdaLabel);
    lambdaLayout->addWidget(lambdaLineEdit);


    buttonsLayout = new QHBoxLayout;

    createButton = new QPushButton("Crea e aggiungi", this);
    createButton->setShortcut(Qt::Key_Enter);
    connect(createButton, &QPushButton::clicked, this, &AddSensorDialogueWindow::createAndAddSlot);

    discardButton = new QPushButton("Annulla", this);
    discardButton->setShortcut(Qt::Key_Escape);
    connect(discardButton, &QPushButton::clicked, this, &AddSensorDialogueWindow::discardChanges);

    buttonsLayout->addWidget(discardButton);
    buttonsLayout->addWidget(createButton);


    mainLayout->addLayout(typeLayout);
    mainLayout->addLayout(idLayout);
    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(minLayout);
    mainLayout->addLayout(maxLayout);
    mainLayout->addLayout(meanLayout);
    mainLayout->addLayout(varianceLayout);
    mainLayout->addLayout(lambdaLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);


    // Alla fine ho scelto di non implementare quanto segue, ma questo codice è riutilizzabile in futuro

    /*connect(typeComboBox, &QComboBox::currentIndexChanged, this, &AddSensorDialogueWindow::afterSomethingChanged);
    connect(idLineEdit, &QLineEdit::textChanged, this, &AddSensorDialogueWindow::afterSomethingChanged);
    connect(nameLineEdit, &QLineEdit::textChanged, this, &AddSensorDialogueWindow::afterSomethingChanged);
    connect(minLineEdit, &QLineEdit::textChanged, this, &AddSensorDialogueWindow::afterSomethingChanged);
    connect(maxLineEdit, &QLineEdit::textChanged, this, &AddSensorDialogueWindow::afterSomethingChanged);
    connect(meanLineEdit, &QLineEdit::textChanged, this, &AddSensorDialogueWindow::afterSomethingChanged);
    connect(varianceLineEdit, &QLineEdit::textChanged, this, &AddSensorDialogueWindow::afterSomethingChanged);
    connect(lambdaLineEdit, &QLineEdit::textChanged, this, &AddSensorDialogueWindow::afterSomethingChanged);*/
}

bool AddSensorDialogueWindow::differentFromOriginal(){ // Alla fine risulta inutilizzato, lo tengo per eventuali futuri ampliamenti
    // Se sono tutte vuote (e opzione predefinita del menù a tendina), non c'è differenza con l'originale, altrimenti sì
    return !( typeComboBox->currentIndex()==0 && idLineEdit->text().isEmpty()==true && nameLineEdit->text().isEmpty()==true && 
              minLineEdit->text().isEmpty()==true && maxLineEdit->text().isEmpty()==true && meanLineEdit->text().isEmpty()==true && 
              varianceLineEdit->text().isEmpty()==true && lambdaLineEdit->text().isEmpty()==true );
}

void AddSensorDialogueWindow::afterSomethingChanged(){ // Alla fine risulta inutilizzato, lo tengo per eventuali futuri ampliamenti
    if(differentFromOriginal()){
        createButton->setEnabled(true);
    } 
    else {
        createButton->setEnabled(false);
    }
}

void AddSensorDialogueWindow::createAndAddSlot(){
    emit createAndAddSignal();
}

void AddSensorDialogueWindow::createAndAddSensor(const std::vector<Sensor::AbstractSensor*>& sensors) {
    bool ok = true, theLastFiveAreFilled = false;
    unsigned int id;
    std::string name;
    double min_value, max_value, mean, variance, lambda;

    if((idLineEdit->text().isEmpty()==false) && (nameLineEdit->text().isEmpty()==false)){
        id = idLineEdit->text().toUInt(&ok);
        name = nameLineEdit->text().toStdString();
    }
    else {
        QMessageBox::critical(this, "Errore", "I campi di testo dell'id e del nome non possono essere vuoti!!");
        return;
    }

    // Check if the ID is valid
    if(!ok){
        QMessageBox::critical(this, "Errore", "L'ID deve essere un numero intero senza segno!!");
        return;
    }

    if(idLineEdit->text().length() != 6){
        QMessageBox::critical(this, "Errore", "L'ID deve essere composto da esattamente 6 cifre!!");
        return;
    }

    // Check if the ID is unique
    for (Sensor::AbstractSensor* sensor : sensors) {
        if (sensor->getIdentifier() == id) {
            QMessageBox::critical(this, "Errore", "ID già utilizzato");
            return;
        }
    }

    // Check if the name is unique
    for (Sensor::AbstractSensor* sensor : sensors) {
        if (sensor->getName() == name) {
            QMessageBox::critical(this, "Errore", "Nome già utilizzato");
            return;
        }
    }

    if(minLineEdit->text().isEmpty()==false){
        min_value = minLineEdit->text().toDouble(&ok);
        if(!ok){
            QMessageBox::critical(this, "Errore", "Il minimo deve essere un numero!");
            return;
        }
        if (min_value < 1.0 || min_value > 25.0){
            QMessageBox::critical(this, "Errore", "Il minimo deve essere compreso tra 1.0 e 25.0");
            return;
        }

        theLastFiveAreFilled = true;   // Il primo campo di testo tra gli ultimi 5 decide la sorte dei 4 successivi, che sono ora obbligati a essere pieni
    }
    else
        theLastFiveAreFilled = false;  // Il primo campo di testo tra gli ultimi 5 decide la sorte dei 4 successivi, che sono ora obbligati a essere vuoti

    if(maxLineEdit->text().isEmpty()==false){
        if(theLastFiveAreFilled == false){
            QMessageBox::critical(this, "Errore", "Degli ultimi 5 campi di testo, o ne riempi 5 o non ne riempi nessuno!");
            return;
        }

        max_value = maxLineEdit->text().toDouble(&ok);
        if(!ok){
            QMessageBox::critical(this, "Errore", "Il massimo deve essere un numero!");
            return;
        }
        if (max_value <= min_value || max_value > 25.0){
            QMessageBox::critical(this, "Errore", "Il massimo deve essere maggiore stretto del minimo e minore o uguale di 25.0");
            return;
        }
    }
    else{
        if (theLastFiveAreFilled == true){
            QMessageBox::critical(this, "Errore", "Degli ultimi 5 campi di testo, o ne riempi 5 o non ne riempi nessuno!");
            return;
        }
    }

    if(meanLineEdit->text().isEmpty()==false){
        if(theLastFiveAreFilled == false){
            QMessageBox::critical(this, "Errore", "Degli ultimi 5 campi di testo, o ne riempi 5 o non ne riempi nessuno!");
            return;
        }

        mean = meanLineEdit->text().toDouble(&ok);
        if(!ok){
            QMessageBox::critical(this, "Errore", "La media deve essere un numero!");
            return;
        }
        if (mean < 1.0 || mean > 100.0){
            QMessageBox::critical(this, "Errore", "La media deve essere compresa tra 1.0 e 100.0");
            return;
        }
    }
    else{
        if (theLastFiveAreFilled == true){
            QMessageBox::critical(this, "Errore", "Degli ultimi 5 campi di testo, o ne riempi 5 o non ne riempi nessuno!");
            return;
        }
    }

    if(varianceLineEdit->text().isEmpty()==false){
        if(theLastFiveAreFilled == false){
            QMessageBox::critical(this, "Errore", "Degli ultimi 5 campi di testo, o ne riempi 5 o non ne riempi nessuno!");
            return;
        }

        variance = varianceLineEdit->text().toDouble(&ok);
        if(!ok){
            QMessageBox::critical(this, "Errore", "La varianza deve essere un numero!");
            return;
        }
        if (variance < 1.0 || variance > 10.0){
            QMessageBox::critical(this, "Errore", "La varianza deve essere compresa tra 1.0 e 10.0");
            return;
        }
    }
    else{
        if (theLastFiveAreFilled == true){
            QMessageBox::critical(this, "Errore", "Degli ultimi 5 campi di testo, o ne riempi 5 o non ne riempi nessuno!");
            return;
        }
    }

    if(lambdaLineEdit->text().isEmpty()==false){
        if(theLastFiveAreFilled == false){
            QMessageBox::critical(this, "Errore", "Degli ultimi 5 campi di testo, o ne riempi 5 o non ne riempi nessuno!");
            return;
        }

        lambda = lambdaLineEdit->text().toDouble(&ok);
        if(!ok){
            QMessageBox::critical(this, "Errore", "La lambda deve essere un numero!");
            return;
        }
        if (lambda < 1.0 || lambda > 10.0){
            QMessageBox::critical(this, "Errore", "La lambda deve essere compresa tra 1.0 e 10.0");
            return;
        }
    }
    else{
        if (theLastFiveAreFilled == true){
            QMessageBox::critical(this, "Errore", "Degli ultimi 5 campi di testo, o ne riempi 5 o non ne riempi nessuno!");
            return;
        }
    }

    // La costruzione del nuovo sensore
    std::string type = typeComboBox->currentText().toStdString();

    Sensor::AbstractSensor* sensor;

    if(theLastFiveAreFilled){
        if(type == "DistanceCoveredSensor")
            sensor = new Sensor::DistanceCoveredSensor(id, name, min_value, max_value, mean, variance, lambda);
        else if(type == "Chronometer")
            sensor = new Sensor::Chronometer(id, name, min_value, max_value, mean, variance, lambda);
        else if(type == "SpeedSensor"){
            sensor = new Sensor::SpeedSensor(id, name, Sensor::DistanceCoveredSensor(000000, "DistanceSubSensor", min_value, max_value, mean, variance, lambda), 
                                             Sensor::Chronometer(000000, "ChronoSubsensor", min_value, max_value, mean, variance, lambda));
        }
        else{
            sensor = new Sensor::Accelerometer(id, name, Sensor::Chronometer(000000, "ChronoSubsensor", min_value, max_value, mean, variance, lambda),
                     Sensor::SpeedSensor(id, name, Sensor::DistanceCoveredSensor(000000, "DistanceSubSubSensor", min_value, max_value, mean, variance, lambda), 
                                             Sensor::Chronometer(000000, "ChronoSubSubSensor", min_value, max_value, mean, variance, lambda)));
        }
    }
    else{
        if(type == "DistanceCoveredSensor")
            sensor = new Sensor::DistanceCoveredSensor(id, name);
        else if(type == "Chronometer")
            sensor = new Sensor::Chronometer(id, name);
        else if(type == "SpeedSensor"){
            sensor = new Sensor::SpeedSensor(id, name, Sensor::DistanceCoveredSensor(000000, "DistanceSubSensor"), 
                                             Sensor::Chronometer(000000, "ChronoSubsensor"));
        }
        else{
            sensor = new Sensor::Accelerometer(id, name, Sensor::Chronometer(000000, "ChronoSubsensor"),
                                               Sensor::SpeedSensor(id, name, Sensor::DistanceCoveredSensor(000000, "DistanceSubSubSensor"), 
                                                                   Sensor::Chronometer(000000, "ChronoSubSubSensor")));
        }
    }

    // Emit signal with sensor details
    emit sensorAdded(sensor);

    // Close the dialog
    //accept();   // Ho dovuto commentarlo perchè mi dava un segmentation fault
}

void AddSensorDialogueWindow::discardChanges() {
    if(differentFromOriginal()){
        // Show confirmation dialog for discarding changes
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Scartare le modifiche effettuate?", "Sei sicuro di voler scartare le modifiche?", QMessageBox::Yes|QMessageBox::No);
        
        if (reply == QMessageBox::Yes) {
            // Discard changes and close the dialog
            reject();
        }
    }
    else{
        // Discard changes and close the dialog
        reject();
    }
}

AddSensorDialogueWindow::~AddSensorDialogueWindow()  // La finestra di dialogo viene distrutta quando viene chiusa, non c'è mai una sovrascrizione,
{                                                    // quindi posso mettere i delete solo nel distruttore e non anche all'inizio del costruttore
    delete typeLabel;
    delete idLabel;
    delete nameLabel;
    delete minLabel;
    delete maxLabel;
    delete meanLabel;
    delete varianceLabel;
    delete lambdaLabel;

    delete typeComboBox;
    delete idLineEdit;
    delete nameLineEdit;
    delete minLineEdit;
    delete maxLineEdit;
    delete meanLineEdit;
    delete varianceLineEdit;
    delete lambdaLineEdit;

    delete discardButton;
    delete createButton;

    delete typeLayout;
    delete idLayout;
    delete nameLayout;
    delete minLayout;
    delete maxLayout;
    delete meanLayout;
    delete varianceLayout;
    delete lambdaLayout;
    delete buttonsLayout;
    delete mainLayout;
}

}
