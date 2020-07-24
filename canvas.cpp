#include "canvas.h"
#include<QRect>
#include<iostream>
using namespace std;
QString *Canvas::getMode() const
{
    return this->mode;
}

void Canvas::setMode(QString *mode)
{
    this->mode = mode;
}

void Canvas::backgroundToggle()
{
    this->backgroundFlag=(!this->backgroundFlag);
}

Canvas::Canvas()
{

}
Canvas::Canvas(QWidget *parent):QWidget(parent)
{
    //this->painter=new QPainter(this);
    this->view=new TMView();
    this->backup_list=new QList<DrawableComponent*>();
    this->group_list=new QList<DrawableComponent*>();
    this->mode=new QString("view");
    this->pickedComponent=nullptr;
    this->pickedComponentIndex=-1;
    this->backgroundFlag=false;
}
void Canvas::paintEvent(QPaintEvent *event)
{
    if(this->mode->toUpper()==QString("pickup").toUpper() || this->mode->toUpper()==QString("grouping").toUpper())
    {
        //QPixmap p = QPixmap(":/icons/handPickup_icon.png");
        QPixmap p = QPixmap(":/icons/hand_pointer_icon.png");
        //QPixmap p = QPixmap(":/icons/hand_pointer_icon2.png");
        QCursor c = QCursor(p, 10, 0);
        setCursor(c);
    }
    else
    {
        //QPixmap p = QPixmap(":/icons/pencil_pink_icon.png");
        QPixmap p = QPixmap(":/icons/edit_icon.png");
        QCursor c = QCursor(p, 0, 0);
        setCursor(c);
    }
    QPainter *myPaint=new QPainter(this);
    //if(this->backgroundFlag)myPaint->drawPixmap(0,0,QPixmap(":/icons/backgroundImage.png"));
    if(this->backgroundFlag)drawBackground(myPaint);
    this->view->draw(myPaint);
    this->draw(myPaint);
}

bool Canvas::hasCoordinate(const QPoint &point)
{
    int xOffSet=13;
    int yOffSet=13;
    if((point.x()>=this->x()+xOffSet) && (point.x()<=this->width()+this->x()-xOffSet))
    {
        if((point.y()>=this->y()+yOffSet) && (point.y()<=this->height()+this->y()-yOffSet))return true;
    }
    return false;
}

void Canvas::read(const QJsonObject &json)
{
    QJsonObject j;
    if(json.contains("mode") && json["mode"].isString())
    {
        this->mode=new QString(json["shape"].toString());
    }
    if(json.contains("backgroundFlag") && json["backgroundFlag"].isBool())
    {
        this->backgroundFlag=json["backgroundFlag"].toBool();
    }
    if(json.contains("view") && json["view"].isObject())
    {
        j=json["view"].toObject();
        this->view=new TMView();
        this->view->read(j);
    }
/*
    if(json.contains("backup_list") && json["backup_list"].isArray())
    {
        QJsonArray componentsArray = json["backup_list"].toArray();
        this->backup_list->clear();
        this->backup_list->reserve(componentsArray.size());
        for(int index=0;index < componentsArray.size();++index)
        {
            QJsonObject comObject=componentsArray[index].toObject();
            if(comObject.contains("shape") && comObject["shape"].isString() && comObject["shape"].toString().toUpper()==QString("Line").toUpper())
            {
                TMLineComponent *line=new TMLineComponent();
                line->read(comObject);
                this->backup_list->append(line);
            }
            if(comObject.contains("shape") && comObject["shape"].isString() && comObject["shape"].toString().toUpper()==QString("Rectangle").toUpper())
            {
                TMRectangleComponent *rectangle=new TMRectangleComponent();
                rectangle->read(comObject);myPaint->drawPixmap(0,0,QPixmap(":/icons/backgroundImage2.png"));
                this->backup_list->append(rectangle);
            }
            if(comObject.contains("shape") && comObject["shape"].isString() && comObject["shape"].toString().toUpper()==QString("Circle").toUpper())
            {
                TMCircleComponent *circle=new TMCircleComponent();
                circle->read(comObject);
                this->backup_list->append(circle);
            }
            if(comObject.contains("shape") && comObject["shape"].isString() && comObject["shape"].toString().toUpper()==QString("Ellipse").toUpper())
            {
                TMEllipseComponent *ellipse=new TMEllipseComponent();
                ellipse->read(comObject);
                this->backup_list->append(ellipse);
            }
            if(comObject.contains("shape") && comObject["shape"].isString() && comObject["shape"].toString().toUpper()==QString("FreeHand").toUpper())
            {
                TMFreeHandComponent *freeHand=new TMFreeHandComponent();
                freeHand->read(comObject);
                this->backup_list->append(freeHand);
            }
        }
    }

    if(json.contains("pickedComponent") && json["pickedComponent"].isObject())
    {
        j=json["pickedComponent"].toObject();
        if(j.contains("shape") && j["shape"].isString() && j["shape"].toString().toUpper()==QString("Line").toUpper())
        {
            TMLineComponent *line=new TMLineComponent();
            line->read(j);
            this->pickedComponent=line;
        }
        if(j.contains("shape") && j["shape"].isString() && j["shape"].toString().toUpper()==QString("Rectangle").toUpper())
        {
            TMRectangleComponent *rectangle=new TMRectangleComponent();
            rectangle->read(j);
            this->pickedComponent=rectangle;
        }
        if(j.contains("shape") && j["shape"].isString() && j["shape"].toString().toUpper()==QString("Circle").toUpper())
        {
            TMCircleComponent *circle=new TMCircleComponent();
            circle->read(j);
            this->pickedComponent=circle;
        }
        if(j.contains("shape") && j["shape"].isString() && j["shape"].toString().toUpper()==QString("Ellipse").toUpper())
        {
            TMEllipseComponent *ellipse=new TMEllipseComponent();
            ellipse->read(j);
            this->pickedComponent=ellipse;
        }
        if(j.contains("shape") && j["shape"].isString() && j["shape"].toString().toUpper()==QString("FreeHand").toUpper())
        {
            TMFreeHandComponent *freeHand=new TMFreeHandComponent();
            freeHand->read(j);
            this->pickedComponent=freeHand;
        }

    }
    if(json.contains("pickedComponentIndex") && json["pickedComponentIndex"].isDouble())
    {
        this->pickedComponentIndex=json["pickedComponentIndex"].toInt();
    }
*/
}

void Canvas::write(QJsonObject &json)
{
    //cout<<"Chala 1"<<endl;
    json["mode"]=*this->mode;
    json["backgroundFlag"]=this->backgroundFlag;

    //cout<<"Chala 2"<<endl;
    QJsonObject viewJson;
    this->view->write(viewJson);
    json["view"]=viewJson;
    //cout<<"Chala 3"<<endl;
/*
    QJsonArray drawableArray;
    for(auto drawOb :*this->backup_list)
    {
        if(drawOb!=nullptr)
        {
            QJsonObject drawableObject;
            drawOb->write(drawableObject);
            drawableArray.append(drawableObject);
        }
    }
    json["backup_list"] =drawableArray;
    cout<<"Chala 4"<<endl;
    QJsonObject pickedJson;
    if(this->pickedComponent!=nullptr)this->pickedComponent->write(pickedJson);
    json["pickedComponent"]=pickedJson;
    json["pickedComponentIndex"]=this->pickedComponentIndex;
*/
}

void Canvas::enterEvent(QEvent *event)
{
    if(this->mode->toUpper()==QString("pickup").toUpper() || this->mode->toUpper()==QString("grouping").toUpper())
    {
        //QPixmap p = QPixmap(":/icons/handPickup_icon.png");
        QPixmap p = QPixmap(":/icons/hand_pointer_icon.png");
        //QPixmap p = QPixmap(":/icons/hand_pointer_icon2.png");
        QCursor c = QCursor(p,9,2);
        setCursor(c);
    }
    else
    {
        //QPixmap p = QPixmap(":/icons/pencil_pink_icon.png");
        QPixmap p = QPixmap(":/icons/edit_icon.png");
        QCursor c = QCursor(p, 0, 0);
        setCursor(c);
    }
}

void Canvas::leaveEvent(QEvent *event)
{

}

void Canvas::drawBackground(QPainter *paint)
{
    int xOffSet=13;
    int yOffSet=13;
    int i=30;
    QPen p;
    //p.setColor(QColor("Lightblue"));
    p.setColor(QColor("lightgray"));
    p.setWidth(1);
    paint->setPen(p);
    while(i<this->height()-yOffSet)
    {
        paint->drawLine(xOffSet,i,this->width()-xOffSet,i);
        i+=35;
    }
    //paint->drawPixmap(0,0,QPixmap(":/icons/backgroundImage2.png"));
}

void Canvas::undo()
{
    if(this->view->getComponents()->length()>0)
    {
        DrawableComponent *c=this->view->getComponents()->takeLast();
        c->setClicked(false);
        this->backup_list->append(c);
    }
}

void Canvas::redo()
{
    if(this->backup_list->length()>0)
    {
        this->view->getComponents()->append(this->backup_list->takeLast());
    }
}
void Canvas::draw(QPainter *paint)
{
    paint->drawPixmap(QRect(this->width()/2-50,0,100,60),QPixmap(":/icons/tmlogo.png"));
    paint->drawPixmap(-6,-6,QPixmap(":/icons/border.png"));
}
void Canvas::setView(TMView *view)
{
    this->view=view;
}
TMView* Canvas::getView()
{
    return this->view;
}
