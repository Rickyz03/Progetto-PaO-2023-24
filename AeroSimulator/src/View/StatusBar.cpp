#include "StatusBar.h"

namespace View {

StatusBar::StatusBar(QStatusBar* parent)
    : QStatusBar(parent)
{
    updateBecauseSensorPanelIsEmpty();
}

QString StatusBar::getStatusMessage() const {
    return statusMessage;
}

void StatusBar::setStatusMessage(const std::string& newStatusMessage){
    statusMessage = QString::fromStdString(newStatusMessage);
}

void StatusBar::updateStatus()
{
    showMessage(statusMessage);
}

void StatusBar::updateBecauseSensorPanelIsEmpty(){
    statusMessage = "Carica o aggiungi un sensore.";
    updateStatus();
}

void StatusBar::updateBecauseSensorPanelIsNotEmpty(){
    statusMessage = "Pronto a testare.";
    updateStatus();
}

void StatusBar::updateAfterSensorSelected()
{
    statusMessage = "Puoi avviare una simulazione.";
    updateStatus();
}

/*void StatusBar::updateAfterOneCharacterSearched(){
    statusMessage = "Non ha senso cercare un carattere solo. Riprova!";
    updateStatus();
}*/

void StatusBar::updateAfterResearch(const unsigned int& resultsNumber){
    if(resultsNumber > 1)
        statusMessage = "La ricerca ha prodotto " + QString::number(resultsNumber) + " risultati";
    else if(resultsNumber == 1)
        statusMessage = "La ricerca ha prodotto 1 risultato";
    else
        statusMessage = "Nessun sensore trovato";

    updateStatus();
}

void StatusBar::updateAfterSimulation() 
{
    statusMessage = "Risultati interessanti!";
    updateStatus();
}

void StatusBar::updateAfterAccelerometerSimulation(const bool& isLineRed)
{
    if (isLineRed) {
        statusMessage = "Ahia, occorre effettuare ulteriori test per questo aereo!";
    } else {
        statusMessage = "Ottimo. Signore e signori, questo nuovo aereo presto falcherà i nostri cieli!";
    }

    updateStatus();
}

}
