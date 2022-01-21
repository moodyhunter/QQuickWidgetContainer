#include "Container.hpp"
#include "ui_Form.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

using namespace std::chrono_literals;

// clang-format off
class MyWidget : public QWidget, private Ui::Form
{
  public:
    explicit MyWidget(QWidget *parent = nullptr) : QWidget(parent) { setupUi(this); }
    virtual ~MyWidget(){};
};
// clang-format on

void PopulateWidgetContainer(QQuickWindow *qmlRootObject, const QString &objectName, QWidget *instance)
{
    auto *item = qmlRootObject->findChild<QWidgetPrivate *>(objectName);
    if (item)
        item->setupWidget(instance);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<QWidgetPrivate>("com.private", 1, 0, "WidgetContainer");

    QQmlApplicationEngine engine;
    engine.load(QStringLiteral("qrc:/main.qml"));

    const auto roots = engine.rootObjects();
    if (roots.isEmpty())
        return -1;

    const auto first = (QQuickWindow *) engine.rootObjects().first();
    PopulateWidgetContainer(first, QStringLiteral("myWidget"), new MyWidget);

    return app.exec();
}
