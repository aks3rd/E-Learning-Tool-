#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H
#include<QPainter>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonArray>
class DrawableComponent
{
public:
    DrawableComponent();
    ~DrawableComponent();
    QString *color;
    QString shape;
    QString objectName;
    int penSize;
    virtual void draw(QPainter *paint)=0;
    virtual QString *getColor()const=0;
    virtual void setColor(QString *color)=0;
    virtual QString toString()=0;
    virtual bool hasCoordinate(const QPoint &point)=0;
    virtual void clickedDrawing(QPainter *paint)=0;
    virtual void setClicked(bool selected)=0;
    //virtual void setMultipleClicked(bool selected)=0;
    virtual bool isClicked()=0;
    virtual void read(const QJsonObject &json)=0;
    virtual void write(QJsonObject &json)=0;
    virtual void moveTo(int x,int y)=0;
    virtual bool isResizable()=0;
    virtual void resize(QPoint point,bool shift)=0;
    virtual void setObjectName(const QString& objectName)=0;
    virtual QString getObjectName()const=0;
};

#endif // DRAWABLECOMPONENT_H
