#include "Container.hpp"
#include "ui_Form.h"

#include <QApplication>
#include <QQmlApplicationEngine>

class MyWidget
    : public QWidget
    , private Ui::Form
{
    Q_OBJECT
  public:
    explicit MyWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        setupUi(this);
    }
    virtual ~MyWidget(){};
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<QQuickWidgetContainer>("com.private", 1, 0, "WidgetContainer");

    QQmlApplicationEngine engine;
    engine.load(QStringLiteral("qrc:/main.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;

    const auto roots = engine.rootObjects();

    auto *item = roots.first()->findChild<QQuickWidgetContainer *>(QStringLiteral("myWidget"));
    if (item)
        item->setupWidget(new MyWidget);

    return app.exec();
}

#include "main.moc"
