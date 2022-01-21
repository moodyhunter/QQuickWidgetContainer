#pragma once

#include <QQuickPaintedItem>
#include <QRasterWindow>
#include <QWidget>

class QWidgetPrivate : public QQuickPaintedItem
{
    Q_OBJECT

    class RenderW : public QWidget
    {
      public:
        explicit RenderW(QWidgetPrivate *parent);
        virtual ~RenderW(){};
        virtual bool event(QEvent *event) override;

      private:
        QWidgetPrivate *_parent;
    };

  public:
    explicit QWidgetPrivate(QQuickItem *parent = nullptr);
    ~QWidgetPrivate();
    void setupWidget(QWidget *widget);

  signals:
    void requestUpdate(const QRect &rect = QRect());

  private:
    QWidget *renderer = nullptr;
    QWidget *contentItem = nullptr;

  public:
    virtual bool event(QEvent *event) override;

    // QQuickPaintedItem interface
  public:
    virtual void paint(QPainter *painter) override;
};
