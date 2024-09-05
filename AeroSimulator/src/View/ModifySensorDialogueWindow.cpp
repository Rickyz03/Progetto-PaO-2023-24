#include "ModifySensorDialogueWindow.h"

namespace View {

ModifySensorDialogueWindow::ModifySensorDialogueWindow(const unsigned int& Id, const std::string& OriginalSensorName, const double& OriginalMinValue, 
                 const double& OriginalMaxValue, const double& OriginalMean, const double& OriginalVariance, const double& OriginalLambda, 
                 AbstractDialogueWindow* parent)
    : AbstractDialogueWindow(parent), id(Id), originalSensorName(OriginalSensorName), originalMinValue(OriginalMinValue), originalMaxValue(OriginalMaxValue), 
      originalMean(OriginalMean), originalVariance(OriginalVariance), originalLambda(OriginalLambda) {

    setWindowTitle("Modifica sensore");

    mainLayout = new QVBoxLayout(this);

    nameLayout = new QHBoxLayout;
    nameLabel = new QLabel("Nome:", this);
    nameLineEdit = new QLineEdit(QString::fromStdString(originalSensorName), this);
    nameLineEdit->setFixedSize(120, 26);
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameLineEdit);

    minLayout = new QHBoxLayout;
    minLabel = new QLabel("Minimo:", this);
    minLineEdit = new QLineEdit(QString::number(originalMinValue), this);
    minLineEdit->setFixedSize(120, 26);
    minLayout->addWidget(minLabel);
    minLayout->addWidget(minLineEdit);

    maxLayout = new QHBoxLayout;
    maxLabel = new QLabel("Massimo:", this);
    maxLineEdit = new QLineEdit(QString::number(originalMaxValue), this);
    maxLineEdit->setFixedSize(120, 26);
    maxLayout->addWidget(maxLabel);
    maxLayout->addWidget(maxLineEdit);

    meanLayout = new QHBoxLayout;
    meanLabel = new QLabel("Media:", this);
    meanLineEdit = new QLineEdit(QString::number(originalMean), this);
    meanLineEdit->setFixedSize(120, 26);
    meanLayout->addWidget(meanLabel);
    meanLayout->addWidget(meanLineEdit);

    varianceLayout = new QHBoxLayout;
    varianceLabel = new QLabel("Varianza:", this);
    varianceLineEdit = new QLineEdit(QString::number(originalVariance), this);
    varianceLineEdit->setFixedSize(120, 26);
    varianceLayout->addWidget(varianceLabel);
    varianceLayout->addWidget(varianceLineEdit);

    lambdaLayout = new QHBoxLayout;
    lambdaLabel = new QLabel("Lambda:", this);
    lambdaLineEdit = new QLineEdit(QString::number(originalLambda), this);
    lambdaLineEdit->setFixedSize(120, 26);
    lambdaLayout->addWidget(lambdaLabel);
    lambdaLayout->addWidget(lambdaLineEdit);


    buttonsLayout = new QHBoxLayout;

    applyButton = new QPushButton("Fatto", this);
    applyButton->setShortcut(Qt::Key_Enter);
    connect(applyButton, &QPushButton::clicked, this, &ModifySensorDialogueWindow::applySlot);

    discardButton = new QPushButton("Annulla", this);
    discardButton->setShortcut(Qt::Key_Escape);
    connect(discardButton, &QPushButton::clicked, this, &ModifySensorDialogueWindow::discardChanges);

    buttonsLayout->addWidget(discardButton);
    buttonsLayout->addWidget(applyButton);


    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(minLayout);
    mainLayout->addLayout(maxLayout);
    mainLayout->addLayout(meanLayout);
    mainLayout->addLayout(varianceLayout);
    mainLayout->addLayout(lambdaLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);


    // Alla fine ho scelto di non implementare quanto segue, ma questo codice è riutilizzabile in futuro

    /*connect(nameLineEdit, &QLineEdit::textChanged, this, &ModifySensorDialogueWindow::afterTextChanged);
    connect(minLineEdit, &QLineEdit::textChanged, this, &ModifySensorDialogueWindow::afterTextChanged);
    connect(maxLineEdit, &QLineEdit::textChanged, this, &ModifySensorDialogueWindow::afterTextChanged);
    connect(meanLineEdit, &QLineEdit::textChanged, this, &ModifySensorDialogueWindow::afterTextChanged);
    connect(varianceLineEdit, &QLineEdit::textChanged, this, &ModifySensorDialogueWindow::afterTextChanged);
    connect(lambdaLineEdit, &QLineEdit::textChanged, this, &ModifySensorDialogueWindow::afterTextChanged);*/
}

bool ModifySensorDialogueWindow::differentFromOriginal(){ // Alla fine risulta inutilizzato, lo tengo per eventuali futuri ampliamenti
    std::string name = nameLineEdit->text().toStdString();
    double min_value = minLineEdit->text().toDouble();
    double max_value = maxLineEdit->text().toDouble();
    double mean = meanLineEdit->text().toDouble();
    double variance = varianceLineEdit->text().toDouble();
    double lambda = lambdaLineEdit->text().toDouble();

    return name != originalSensorName || min_value != originalMinValue || max_value != originalMaxValue || mean != originalMean || 
           variance != originalVariance || lambda != originalLambda;
}

void ModifySensorDialogueWindow::afterTextChanged(){ // Alla fine risulta inutilizzato, lo tengo per eventuali futuri ampliamenti
    if(differentFromOriginal()){
        applyButton->setEnabled(true);
    } 
    else {
        applyButton->setEnabled(false);
    }
}

void ModifySensorDialogueWindow::applySlot(){
    emit applySignal();
}

void ModifySensorDialogueWindow::applyChanges(const std::vector<Sensor::AbstractSensor*> sensors) {
    bool ok1=true, ok2=true, ok3=true, ok4=true, ok5=true;
    std::string name;
    double min_value, max_value, mean, variance, lambda;

    if(nameLineEdit->text().isEmpty()==false && minLineEdit->text().isEmpty()==false && maxLineEdit->text().isEmpty()==false && 
       meanLineEdit->text().isEmpty()==false && varianceLineEdit->text().isEmpty()==false && lambdaLineEdit->text().isEmpty()==false){
        name = nameLineEdit->text().toStdString();
        min_value = minLineEdit->text().toDouble(&ok1);
        max_value = maxLineEdit->text().toDouble(&ok2);
        mean = meanLineEdit->text().toDouble(&ok3);
        variance = varianceLineEdit->text().toDouble(&ok4);
        lambda = lambdaLineEdit->text().toDouble(&ok5);
    }
    else{
        QMessageBox::critical(this, "Errore", "Non tutti i campi di testo sono pieni!!");
        return;
    }

    if(!(ok1 && ok2 && ok3 && ok4 && ok5)){
        QMessageBox::critical(this, "Errore", "Minimo, massimo, media, varianza e lambda devono essere dei numeri!!");
        return;
    }


    bool isNameModified = false;         // Flag to check if name is modified
    bool isSomethingModified = false;    // Flag to check if something is modified

    // Check if name is modified
    if (name != originalSensorName) {

        // Check if the name is unique
        for (Sensor::AbstractSensor* sensor : sensors) {
            if (sensor->getIdentifier() != id  &&  sensor->getName() == name) {
                QMessageBox::critical(this, "Errore", "Nome già utilizzato");
                return;
            }
        }

        // If is all ok
        isNameModified = true;
        isSomethingModified = true;
    }

    // Check if min_value is modified
    if (min_value != originalMinValue){

        // Validate min_value
        if(min_value < 1.0 || min_value > 25.0){
            QMessageBox::critical(this, "Errore", "Il minimo deve essere compreso tra 1.0 e 25.0");
            return;
        }

        // If is all ok
        isSomethingModified = true;
    }

    // Check if max_value is modified
    if (max_value != originalMaxValue){

        // Validate max_value
        if(max_value <= min_value || max_value > 25.0){
            QMessageBox::critical(this, "Errore", "Il massimo deve essere maggiore stretto del minimo e minore o uguale di 25.0");
            return;
        }

        // If is all ok
        isSomethingModified = true;
    }

    // Check if mean is modified
    if (mean != originalMean){

        // Validate mean
        if(mean < 1.0 || mean > 100.0){
            QMessageBox::critical(this, "Errore", "La media deve essere compresa tra 1.0 e 100.0");
            return;
        }

        // If is all ok
        isSomethingModified = true;
    }

    // Check if variance is modified
    if (variance != originalVariance){

        // Validate variance
        if(variance < 1.0 || variance > 10.0){
        QMessageBox::critical(this, "Errore", "La varianza deve essere compresa tra 1.0 e 10.0");
        return;
        }

        // If is all ok
        isSomethingModified = true;
    }

    // Check if lambda is modified
    if (lambda != originalLambda){

        // Validate lambda
        if(lambda < 1.0 || lambda > 10.0){
            QMessageBox::critical(this, "Errore", "La lambda deve essere compresa tra 1.0 e 10.0");
            return;
        }

        // If is all ok
        isSomethingModified = true;
    }


    // Emit signal if something is modified, to update both the sensor object and AboveChartWidget's visualization data. "isSaved = false" will be set.
    if(isSomethingModified)
        emit sensorModified(name, min_value, max_value, mean, variance, lambda);

    // Emit signal if the name is modified, to update SensorPanel's name of the sensor
    if (isNameModified)
        emit sensorNameModified(originalSensorName, name);


    // Close the dialog
    accept();
}

void ModifySensorDialogueWindow::discardChanges() {
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

ModifySensorDialogueWindow::~ModifySensorDialogueWindow()   // La finestra di dialogo viene distrutta quando viene chiusa, non c'è mai una sovrascrizione, 
{                                                           // quindi posso mettere i delete solo nel distruttore e non anche all'inizio del costruttore
    delete nameLabel;
    delete minLabel;
    delete maxLabel;
    delete meanLabel;
    delete varianceLabel;
    delete lambdaLabel;

    delete nameLineEdit;
    delete minLineEdit;
    delete maxLineEdit;
    delete meanLineEdit;
    delete varianceLineEdit;
    delete lambdaLineEdit;

    delete discardButton;
    delete applyButton;

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
