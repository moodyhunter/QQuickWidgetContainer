#include "Container.hpp"
#include "ui_Form.h"

#include <QApplication>
#include <QQmlApplicationEngine>

// clang-format off
class MyWidget : public QWidget, private Ui::Form
{
  public:
    explicit MyWidget(QWidget *parent = nullptr) : QWidget(parent) { setupUi(this); }
    virtual ~MyWidget(){};
};
// clang-format on

void PopulateWidgetContainer(QObject *qmlRootObject, const QString &objectName, QWidget *instance)
{
    auto *item = qmlRootObject->findChild<QQuickWidgetContainer *>(objectName);
    if (item)
        item->setupWidget(instance);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<QQuickWidgetContainer>("com.private", 1, 0, "WidgetContainer");

    QQmlApplicationEngine engine;
    engine.load(QStringLiteral("qrc:/main.qml"));

    const auto roots = engine.rootObjects();
    if (roots.isEmpty())
        return -1;

    PopulateWidgetContainer(roots.first(), QStringLiteral("myWidget"), new MyWidget);

    return app.exec();
}
