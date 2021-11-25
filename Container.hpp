#pragma once

#include <QQuickPaintedItem>
#include <QRasterWindow>
#include <QWidget>

class QQuickWidgetContainer : public QQuickItem
{
    Q_OBJECT

    class RenderW : public QWidget
    {
      public:
        explicit RenderW(QQuickWidgetContainer *parent);
        virtual ~RenderW(){};

      protected:
        virtual void paintEvent(QPaintEvent *e) override;
        virtual bool event(QEvent *event) override;

      private:
        QQuickWidgetContainer *_parent;
    };

  public:
    explicit QQuickWidgetContainer(QQuickItem *parent = nullptr);
    ~QQuickWidgetContainer();
    void setupWidget(QWidget *widget);

  private:
    QWidget *renderer = nullptr;
    QWidget *contentItem = nullptr;
};
