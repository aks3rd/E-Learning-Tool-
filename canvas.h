#ifndef CANVAS_H
#define CANVAS_H
#include "tmview.h"
#include <QWidget>
#include<QPainter>
class Canvas:public QWidget
{
private:
    QPainter *painter;
    QString *mode;
    bool backgroundFlag;
public:
    TMView *view;
    QList<DrawableComponent *> *backup_list;
    QList<DrawableComponent *> *group_list;
    DrawableComponent *pickedComponent;
    int pickedComponentIndex;
public:
    Canvas();
    Canvas(QWidget *parent=nullptr);
    void draw(QPainter *paint);
    void setView(TMView  *view);
    TMView* getView();
    virtual void paintEvent(QPaintEvent *event) override;
    bool hasCoordinate(const QPoint &point);
    void read(const QJsonObject &json);
    void write(QJsonObject &json);

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void drawBackground(QPainter *paint);
    void undo();
    void redo();
    QString *getMode() const;
    void setMode(QString *mode);
    void backgroundToggle();
};


#endif // CANVAS_H
