#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QToolButton>
#include <string>

#include "../Sensor/Repository/JsonRepository.h"

namespace View {

class ToolBar : public QToolBar {
    Q_OBJECT

private:
    QAction* openAction;
    QAction* saveAction;
    QAction* saveAsAction;

signals:
    void openSignal();
    void saveSignal();
    void saveAsSignal();
    void fileOpened();
    void setIsSaved(const bool& value);

public slots:
    void openSlot();
    void saveSlot();
    void saveAsSlot();

public:
    ToolBar(QToolBar *parent = nullptr);

    void activateSaveAction();
    void activateSaveAsAction();
    void disactivateSaveAction();
    void disactivateSaveAsAction();
    void openJsonFile(Sensor::Repository::JsonRepository*& repository);
    void saveJsonFile(const std::vector<Sensor::AbstractSensor*>& sensors, Sensor::Repository::JsonRepository*& repository);
    void saveJsonFileAs(const std::vector<Sensor::AbstractSensor*>& sensors, Sensor::Repository::JsonRepository*& repository);

    ~ToolBar();
};

}

#endif
