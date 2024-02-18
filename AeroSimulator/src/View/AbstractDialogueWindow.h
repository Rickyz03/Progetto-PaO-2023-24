#ifndef ABSTRACT_DIALOGUE_WINDOW_H
#define ABSTRACT_DIALOGUE_WINDOW_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "../Sensor/Accelerometer.h"

namespace View {

class AbstractDialogueWindow : public QDialog {
    Q_OBJECT

public:
    AbstractDialogueWindow(QDialog* parent = nullptr);

    // Interfaccia per eventuali futuri metodi virtuali puri in comune tra le due finestre di dialogo

    virtual ~AbstractDialogueWindow() = 0;
};

}

#endif