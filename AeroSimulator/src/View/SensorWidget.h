#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QLineEdit>
#include <QMouseEvent>

namespace View {

class SensorWidget : public QWidget {
    Q_OBJECT

private:
    QWidget* backgroundWidget;
    QHBoxLayout* layout;

    QLabel* iconLabel;
    
    QVBoxLayout* dataLayout;
    QLabel* nameLabel;
    QLabel* idLabel;
    QLabel* typeLabel;

signals:
    void selected(SensorWidget *sender);

public:
    explicit SensorWidget(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;
    void setBackgroundColor(const QColor &color);

    std::string getName() const;
    unsigned int getId() const;

    void setIcon(const QIcon& icon);
    void setName(const QString& name);
    void setId(const int& id);
    void setType(const QString& type);

    ~SensorWidget();
};

}