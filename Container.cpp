#include "Container.hpp"

#include <QDateTime>
#include <QGridLayout>
#include <QMdiSubWindow>
#include <QPainter>
#include <QQuickWindow>
#include <QTimer>
#include <private/qwindow_p.h>

using namespace std::chrono_literals;

QWidgetPrivate::RenderW::RenderW(QWidgetPrivate *parent)
{
    _parent = parent;
    setLayout(new QGridLayout);
    layout()->setSpacing(0);
    layout()->addWidget(parent->contentItem);
    setContentsMargins(0, 0, 0, 0);
    //    _parent->contentItem->installEventFilter(this);
    //    QTimer::singleShot(100ms, this, qOverload<>(&RenderW::update));
    //    setFocusProxy(_parent->contentItem);
}

bool QWidgetPrivate::RenderW::event(QEvent *event)
{
    _parent->requestUpdate();
    qDebug() << QDateTime::currentDateTime() << event;
    return QWidget::event(event);
}

QWidgetPrivate::QWidgetPrivate(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(Qt::AllButtons);
    setAcceptTouchEvents(true);
    setFocus(true);
    QObject::connect(this, &QWidgetPrivate::requestUpdate, this, &QQuickPaintedItem::update);
}

QWidgetPrivate::~QWidgetPrivate()
{
}

void QWidgetPrivate::setupWidget(QWidget *widget)
{
    contentItem = widget;
    renderer = new RenderW(this);
    renderer->setAttribute(Qt::WA_TranslucentBackground);
    //    renderer->setAttribute(Qt::WA_WState_Created);
    renderer->setContentsMargins(0, 0, 0, 0);
    renderer->setVisible(true);
    renderer->setAttribute(Qt::WA_WState_Created, false);
    renderer->window()->setVisible(false);
    renderer->windowHandle()->setVisible(false);

    Q_ASSERT(!contentItem->isWindow());
    Q_ASSERT(contentItem->parent());
    Q_ASSERT(contentItem->parentWidget()->isVisible());
    Q_ASSERT(!contentItem->parentWidget()->testAttribute(Qt::WA_WState_Created));

    if (contentItem->isWindow() || !contentItem->parentWidget() || !contentItem->parentWidget()->isVisible() ||
        contentItem->parentWidget()->testAttribute(Qt::WA_WState_Created))
    {
        Q_ASSERT(false);
    }

    //    renderer->winId();
    //    renderer->show();
    //    renderer->windowHandle()->setParent(window());
    //    renderer->windowHandle()->setVisible(false);
    //    installEventFilter(renderer);

    const auto resizeToParent = [this]()
    {
        const auto dw = width() == 0 ? renderer->minimumSizeHint().width() : width();
        const auto dh = height() == 0 ? renderer->minimumSizeHint().height() : height();
        const auto dx = parentItem()->x() + x();
        const auto dy = parentItem()->y() + y();
        renderer->setGeometry(dx, dy, dw, dh);
        renderer->update();
    };

    connect(this, &QWidgetPrivate::widthChanged, this, resizeToParent);
    connect(this, &QWidgetPrivate::heightChanged, this, resizeToParent);
    connect(this, &QWidgetPrivate::xChanged, this, resizeToParent);
    connect(this, &QWidgetPrivate::yChanged, this, resizeToParent);
    resizeToParent();
}

bool QWidgetPrivate::event(QEvent *event)
{
    if (renderer && renderer->windowHandle())
    {
        auto x = QCoreApplication::sendSpontaneousEvent(renderer->windowHandle(), event);
        update();
        return x;
    }
    return QQuickItem::event(event);
}

void QWidgetPrivate::paint(QPainter *painter)
{
    contentItem->render(painter, {}, {}, QWidget::DrawChildren);
}
