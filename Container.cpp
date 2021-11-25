#include "Container.hpp"

#include <QGridLayout>
#include <QPainter>
#include <QQuickWindow>
#include <QTimer>

using namespace std::chrono_literals;

QQuickWidgetContainer::RenderW::RenderW(QQuickWidgetContainer *parent)
{
    _parent = parent;
    setLayout(new QGridLayout);
    layout()->setSpacing(0);
    layout()->addWidget(parent->contentItem);
    setContentsMargins(0, 0, 0, 0);
    QTimer::singleShot(100ms, this, qOverload<>(&RenderW::update));
}

void QQuickWidgetContainer::RenderW::paintEvent(QPaintEvent *)
{
    QPainter painter{ this };
    const auto position = mapFromParent(pos());
    const auto &[rx, ry] = std::tuple(position.x(), position.y());
    painter.drawImage(rx, ry, _parent->window()->grabWindow(), x(), y(), width() - rx, height() - ry);
    painter.end();
}

bool QQuickWidgetContainer::RenderW::event(QEvent *event)
{
    const auto events = { QEvent::MouseButtonRelease, QEvent::MouseButtonPress, QEvent::MouseButtonDblClick,
                          QEvent::MouseMove,          QEvent::UpdateRequest,    QEvent::KeyPress,
                          QEvent::KeyRelease,         QEvent::FocusIn,          QEvent::FocusOut };
    if (std::find(events.begin(), events.end(), event->type()) != events.end())
        update();
    return QWidget::event(event);
}

QQuickWidgetContainer::QQuickWidgetContainer(QQuickItem *parent) : QQuickItem(parent)
{
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(Qt::AllButtons);
    setAcceptTouchEvents(true);
    setFocus(true);
}

QQuickWidgetContainer::~QQuickWidgetContainer()
{
    delete renderer;
}

void QQuickWidgetContainer::setupWidget(QWidget *widget)
{
    contentItem = widget;
    renderer = new RenderW(this);
    renderer->setContentsMargins(0, 0, 0, 0);
    renderer->winId();
    renderer->windowHandle()->setParent(window());
    renderer->show();

    const auto resizeToParent = [this]()
    {
        const auto dw = width() == 0 ? renderer->minimumSizeHint().width() : width();
        const auto dh = height() == 0 ? renderer->minimumSizeHint().height() : height();
        const auto dx = parentItem()->x() + x();
        const auto dy = parentItem()->y() + y();
        renderer->setGeometry(dx, dy, dw, dh);
        renderer->update();
    };

    connect(this, &QQuickWidgetContainer::widthChanged, this, resizeToParent);
    connect(this, &QQuickWidgetContainer::heightChanged, this, resizeToParent);
    connect(this, &QQuickWidgetContainer::xChanged, this, resizeToParent);
    connect(this, &QQuickWidgetContainer::yChanged, this, resizeToParent);
    resizeToParent();
}
