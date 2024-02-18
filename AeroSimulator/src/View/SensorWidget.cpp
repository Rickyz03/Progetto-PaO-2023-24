#include "SensorWidget.h"
#include <stdexcept>

namespace View {

SensorWidget::SensorWidget(QWidget *parent) : QWidget(parent) {
    // Creazione del backgroundWidget personalizzato come sfondo
    backgroundWidget = new QWidget(this);
    backgroundWidget->setObjectName("backgroundWidget"); // Imposta un nome per poterlo stilizzare con CSS
    backgroundWidget->setFixedSize(270, 100);

    QPalette pal = backgroundWidget->palette(); // Ottiene la palette di colori del backgroundWidget
    pal.setColor(QPalette::Window, Qt::white); // Imposta il colore di sfondo (in questo caso bianco)
    backgroundWidget->setAutoFillBackground(true);
    backgroundWidget->setPalette(pal);

    // Imposta il layout per il backgroundWidget
    layout = new QHBoxLayout(backgroundWidget);

    // Crea l'icona e imposta la sua dimensione
    iconLabel = new QLabel(backgroundWidget);
    iconLabel->setFixedSize(32, 32);

    // Aggiunge l'icona al layout del backgroundWidget
    layout->addWidget(iconLabel);

    // Creazione del layout delle etichette
    dataLayout = new QVBoxLayout;

    // Crea le etichette per i dati del sensore
    nameLabel = new QLabel(backgroundWidget);
    idLabel = new QLabel(backgroundWidget);
    typeLabel = new QLabel(backgroundWidget);

    // Imposta la dimensione del carattere per il nome del sensore
    QFont font = nameLabel->font();
    font.setPointSize(14);
    nameLabel->setFont(font);

    // Aggiunge le etichette al dataLayout
    dataLayout->addWidget(nameLabel);
    dataLayout->addWidget(idLabel);
    dataLayout->addWidget(typeLabel);

    // Aggiunge il dataLayout al layout del backgroundWidget
    layout->addLayout(dataLayout);

    // Imposta la dimensione del SensorWidget
    setFixedSize(270, 100);

    // Imposta il layout del sensore come layout principale del widget
    setLayout(layout);
}

void SensorWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit selected(this);
    }
    QWidget::mousePressEvent(event);
}

void SensorWidget::setBackgroundColor(const QColor &color) {
    QPalette pal = backgroundWidget->palette();
    pal.setColor(QPalette::Window, color);
    backgroundWidget->setPalette(pal);
    backgroundWidget->update();  // Aggiorna il widget per applicare i cambiamenti
}

std::string SensorWidget::getName() const {
    return nameLabel->text().toStdString();
}

unsigned int SensorWidget::getId() const {
    bool ok;
    unsigned int id = idLabel->text().right(6).toUInt(&ok);
    if (ok) {
        return id;
    } else {
        // Gestione dell'errore se il testo non è un numero intero valido
        qWarning() << "ID non valido!";
        throw std::exception();
    }
}

void SensorWidget::setIcon(const QIcon& icon) {
    iconLabel->setPixmap(icon.pixmap(32, 32)); // Imposta l'icona con dimensioni fisse
}

void SensorWidget::setName(const QString& name) {
    nameLabel->setText(name);
}

void SensorWidget::setId(const int& id) {
    idLabel->setText(QString("ID: %1").arg(id));
}

void SensorWidget::setType(const QString& type) {
    if(typeLabel==nullptr) 
        qDebug()<<"Ciao";
    typeLabel->setText(QString("Tipo: %1").arg(type));
}

SensorWidget::~SensorWidget()  // Un sensorWidget non verrà mai sovrascritto a runtime, verrà solo creato, settato ed eliminato, quindi
{                              // Posso mettere i delete solo nel distruttore
    delete iconLabel;

    delete nameLabel;
    delete idLabel;
    delete typeLabel;

    delete dataLayout;
    delete backgroundWidget;
    delete layout;
}

}