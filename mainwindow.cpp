#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<QScreen>
#include<QDesktopWidget>
#include<QStyleFactory>
using namespace std;
using namespace cv;
#include<QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->taskBarIcon=new QSystemTrayIcon(this);
    this->taskBarIcon->setIcon(QIcon(QPixmap(":/icons/mathBoardIcon4.png")));
    this->taskBarIcon->setVisible(true);
    this->taskBarIcon->show();
    this->taskBarIcon->showMessage(QString("Math Board"),QString("Loading Modules..."));
    QTimer::singleShot(5000,this->taskBarIcon,SLOT(hide()));
    QTimer::singleShot(5000,this->taskBarIcon,SLOT(show()));
    initComponents();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initComponents()
{
    auto statusBarWidget = statusBar();
    statusBarWidget->setSizeGripEnabled(true);
    //this->setWindowIcon(QIcon(QPixmap(":/icons/appDesktop.png")));
    this->setWindowIcon(QIcon(QPixmap(":/icons/mathBoardIcon4.png")));
    this->setWindowTitle("Math Board");
    this->setIconSize(QSize(24,24));

    this->heightOffSet=30;
    this->oldX=-1;
    this->oldY=-1;


    this->freeComponent=nullptr;
    this->lineComponent=nullptr;
    this->rectangleComponent=nullptr;
    this->circleComponent=nullptr;
    this->ellipseComponent=nullptr;
    this->groupComponent=nullptr;
    this->pickedComponent=nullptr;
    this->controlKey=false;
    this->shiftKey=false;
    this->copyComponentsList=new QList<DrawableComponent *>();
    this->recordingFlag=false;
    this->recordingStateFlag=false;
    this->imageList=new QList<QImage *>();
    this->imageDatabase=new QList<QList<QImage *>*>();
    this->imageDatabase->append(this->imageList);
    QRect deskRect = QApplication::desktop()->screenGeometry();

    this->setFixedSize(1220,870);
    //this->setMinimumSize(1220,870);
    //this->setMaximumSize(deskRect.width(),deskRect.height());

    this->move(QPoint((deskRect.width()-this->width())/2,(deskRect.height()-this->height())/2));
    this->setStyleSheet("background-color:lightblue;color:black;");
    this->widFlag=false;
    this->widPos=this->pos();
    this->color=new QString("black");

    this->crop_rect=this->geometry();

    this->ui->toolPanel->setGeometry(10,20,130,820);
    this->ui->toolsLabel->setGeometry(this->ui->toolPanel->x()+10,15,52,16);
    this->ui->lineDrawButton->setIcon(QIcon(QPixmap(":/icons/line-icon.png")));
    this->ui->lineDrawButton->setIconSize(QSize(51,41));

    this->ui->rectangleDrawButton->setIcon(QIcon(QPixmap(":/icons/rectangle_icon.png")));
    this->ui->rectangleDrawButton->setIconSize(QSize(51,41));
    this->ui->circleDrawButton->setIcon(QIcon(QPixmap(":/icons/circle_icon2.png")));
    this->ui->circleDrawButton->setIconSize(QSize(48,38));
    this->ui->freeHandDrawButton->setIcon(QIcon(QPixmap(":/icons/freeHand_icon.png")));
    this->ui->freeHandDrawButton->setIconSize(QSize(51,41));
    this->ui->ellipseDrawButton->setIcon(QIcon(QPixmap(":/icons/circle_icon.png")));
    this->ui->ellipseDrawButton->setIconSize(QSize(48,38));
    this->ui->pickButton->setIcon(QIcon(QPixmap(":/icons/hand_pick_icon.png")));
    this->ui->pickButton->setIconSize(QSize(51,41));
    this->ui->backButton->setIcon(QIcon(QPixmap(":/icons/back_icon.png")));
    this->ui->backButton->setIconSize(QSize(51,41));
    this->ui->restoreButton->setIcon(QIcon(QPixmap(":/icons/restore_icon.png")));
    this->ui->restoreButton->setIconSize(QSize(51,41));
    this->ui->clearCanvasButton->setIcon(QPixmap(":/icons/blanck_icon2.png"));
    this->ui->clearCanvasButton->setIconSize(QSize(51,41));
    this->ui->dsSaveButton->setIcon(QPixmap(":/icons/save_icon.png"));
    this->ui->dsSaveButton->setIconSize(QSize(51,41));
    this->ui->dsOpenButton->setIcon(QPixmap(":/icons/open_icon.png"));
    this->ui->dsOpenButton->setIconSize(QSize(51,41));
    this->ui->groupButton->setIcon(QPixmap(":/icons/group_icon4.png"));
    this->ui->groupButton->setIconSize(QSize(51,41));
    this->ui->unGroupButton->setIcon(QPixmap(":/icons/ungroup_icon.png"));
    this->ui->unGroupButton->setIconSize(QSize(51,41));
    this->ui->addNewCanvasButton->setIcon(QPixmap(":/icons/newCanvas.png"));
    this->ui->addNewCanvasButton->setIconSize(QSize(51,41));
    this->ui->backGroundToggle->setIcon(QPixmap(":/icons/paperline_icon.png"));
    this->ui->backGroundToggle->setIconSize(QSize(51,41));
    this->ui->deleteButton->setIcon(QPixmap(":/icons/delete_icon.png"));
    this->ui->deleteButton->setIconSize(QSize(51,41));

    this->ui->colorToolBoxRedButton->setStyleSheet("background-color:red");
    this->ui->colorPickerButton->setIcon(QPixmap(":/icons/colorPicker_icon.png"));
    this->ui->colorPickerButton->setIconSize(QSize(51,41));
    this->ui->showSymbolsButton->setIcon(QPixmap(":/icons/symbolsIcon.png"));
    this->ui->showSymbolsButton->setIconSize(QSize(51,41));
    this->ui->imagePickupButton->setIcon(QPixmap(":/icons/photos_icon.png"));
    this->ui->imagePickupButton->setIconSize(QSize(51,41));
    this->ui->copyButton->setIcon(QPixmap(":/icons/copy_icon2.png"));
    this->ui->copyButton->setIconSize(QSize(51,41));
    this->ui->pasteButton->setIcon(QPixmap(":/icons/paste_icon2.png"));
    this->ui->pasteButton->setIconSize(QSize(51,41));
    this->ui->fullScreenButton->setIcon(QPixmap(":/icons/fullScreenIcon.png"));
    this->ui->fullScreenButton->setIconSize(QSize(51,41));
    this->ui->fullScreenButton->setToolTip("FullScreen");
    this->ui->videoRecordingStartButton->setIcon(QPixmap(":/icons/video_camera_icon.png"));
    this->ui->videoRecordingStartButton->setIconSize(QSize(51,41));
    this->ui->videoRecordingStartButton->setToolTip("Start Recording");
    this->ui->videoRecordingStopButton->setIcon(QPixmap(":/icons/stop_video_icon2.png"));
    this->ui->videoRecordingStopButton->setIconSize(QSize(51,41));
    this->ui->videoRecordingStopButton->setToolTip("Stop Recording");


    this->mode=new QString("View");
    this->previouseMode=new QString("View");
    this->canvasList=new QList<Canvas *>();
    this->canvas=new Canvas(this);
    this->canvas->setGeometry(this->ui->toolPanel->x()+this->ui->toolPanel->width()+10,this->ui->toolPanel->y(),910,820);
    this->canvas->setStyleSheet("border:1px solid white;background-color:white;color:black;");
    this->canvas->setVisible(true);
    this->canvas->setMode(this->mode);
    this->canvas->pickedComponent=nullptr;
    this->canvas->update();
    this->canvasList->append(this->canvas);

    this->ui->canvasListWidget->setGeometry(this->canvas->x()+this->canvas->width()+5,20,20,820);
    this->ui->canvasListWidget->setFlow(QListView::TopToBottom);

    this->qlit = new QListWidgetItem(this->ui->canvasListWidget);
    this->rdb=new QRadioButton(QString::number(this->canvasList->length()-1));
    this->rdb->setObjectName(QString::number(this->canvasList->length()-1));
    this->rdb->setText(QString::number(this->canvasList->length()-1));
    //this->rdb->setText("");
    this->rdb->setFocusPolicy(Qt::NoFocus);
    QObject::connect( this->rdb, SIGNAL( toggled( bool ) ), this,SLOT( on_canvasListWidget_rowClicked( bool ) ) );
    this->ui->canvasListWidget->setItemWidget(this->qlit, this->rdb);
    this->rdb->setChecked(true);

    this->ui->componentsPanel->setGeometry(this->ui->canvasListWidget->x()+this->ui->canvasListWidget->width(),20,125,820);
    this->ui->drawComponentsLabel->setGeometry(this->ui->componentsPanel->x()+10,15,100,20);
    this->ui->drawComponentList->setGeometry(10,25,this->ui->componentsPanel->width()-20,this->ui->componentsPanel->height()-35);

    this->ui->symbolsFrame->setGeometry(this->x()+this->ui->showSymbolsButton->x()+this->ui->showSymbolsButton->width()+20,this->y()+this->ui->toolPanel->y()+this->ui->showSymbolsButton->y()+35,201,141);
    this->ui->symbolsFrame->setWindowTitle("Symbols");
    this->ui->symbolsFrame->setWindowFlags(Qt::FramelessWindowHint);
    this->ui->symbolsFrame->setWindowFlag(Qt::Dialog,true);
    //this->ui->symbolsFrame->setWindowFlag(Qt::Tool,true);

    //this->ui->symbolsFrame->setWindowFlags(Qt::FramelessWindowHint| Qt::WindowSystemMenuHint);
    //this->ui->symbolsFrame->setVisible(false);
    this->ui->symbolsFrame->hide();
    this->ui->showSymbolsCloseButton->setGeometry(this->ui->symbolsFrame->width()-21,0,21,21);
    this->ui->showSymbolsCloseButton->setIcon(QPixmap(":/icons/cross_icon.png"));
    this->ui->showSymbolsCloseButton->setIconSize(QSize(21,21));
    this->ui->addSymbolButton->setIcon(QPixmap(":/icons/plus_icon.png"));
    this->ui->addSymbolButton->setIconSize(QSize(31,31));
    this->ui->minusSymbolButton->setIcon(QPixmap(":/icons/minus_icon.png"));
    this->ui->minusSymbolButton->setIconSize(QSize(31,31));
    this->ui->multiplySymbolButton->setIcon(QPixmap(":/icons/multiply_icon.png"));
    this->ui->multiplySymbolButton->setIconSize(QSize(31,31));
    this->ui->divideSymbolButton->setIcon(QPixmap(":/icons/divide_icon.png"));
    this->ui->divideSymbolButton->setIconSize(QSize(31,31));
    this->ui->divideSymbolButton2->setIcon(QPixmap(":/icons/divide_icon2.png"));
    this->ui->divideSymbolButton2->setIconSize(QSize(31,31));
    this->ui->piSymbolButton->setIcon(QPixmap(":/icons/pi_icon.png"));
    this->ui->piSymbolButton->setIconSize(QSize(31,31));
    this->ui->rootSymbolButton->setIcon(QPixmap(":/icons/root_icon.png"));
    this->ui->rootSymbolButton->setIconSize(QSize(31,31));
    this->ui->percentageSymbolButton->setIcon(QPixmap(":/icons/percentage_icon.png"));
    this->ui->percentageSymbolButton->setIconSize(QSize(31,31));
    this->ui->leftParentheseSymbolButton->setIcon(QPixmap(":/icons/left_parenthese_icon.png"));
    this->ui->leftParentheseSymbolButton->setIconSize(QSize(31,31));
    this->ui->rightParentheseSymbolButton->setIcon(QPixmap(":/icons/right_parenthese_icon.png"));
    this->ui->rightParentheseSymbolButton->setIconSize(QSize(31,31));
    this->ui->percentageSymbolButton->setIcon(QPixmap(":/icons/percentage_icon.png"));
    this->ui->percentageSymbolButton->setIconSize(QSize(31,31));
    this->ui->equaltoSymbolButton->setIcon(QPixmap(":/icons/equalto_icon.png"));
    this->ui->equaltoSymbolButton->setIconSize(QSize(31,31));
    this->ui->squareSymbolButton->setIcon(QPixmap(":/icons/square_icon.png"));
    this->ui->squareSymbolButton->setIconSize(QSize(31,31));
    this->ui->powerSymbolButton->setIcon(QPixmap(":/icons/pow_sign_icon.png"));
    this->ui->powerSymbolButton->setIconSize(QSize(31,31));
    this->ui->infiniteSymbolButton->setIcon(QPixmap(":/icons/infinite_icon.png"));
    this->ui->infiniteSymbolButton->setIconSize(QSize(31,31));
    this->ui->sigmaSymbolButton->setIcon(QPixmap(":/icons/sigma_icon.png"));
    this->ui->sigmaSymbolButton->setIconSize(QSize(31,31));

    this->ui->progressBar->setGeometry(this->x()+(this->width()-211)/2,this->y()+(this->height()-23)/2,211,23);
    this->ui->progressBar->setWindowFlag(Qt::Popup);
    QPalette p = this->ui->progressBar->palette();
    p.setColor(QPalette::Highlight,Qt::green);
    this->ui->progressBar->setPalette(p);
    //this->ui->progressBar->setStyleSheet("background-color:lightblue;color:green;");
    this->ui->progressBar->hide();
    this->ui->progressBar->setRange(0,1);
    this->ui->progressBar->setValue(0);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    this->ui->symbolsFrame->hide();
    if(this->canvas->hasCoordinate(event->pos()))
    {
        this->oldX=event->pos().x()-this->canvas->x();
        this->oldY=event->pos().y()-this->canvas->y();
        //cout<<"Canvas Start here .."<<this->oldX<<" : "<<this->oldY<<endl;
        if(this->mode->toUpper()==QString("freeHand").toUpper())
        {
            if(this->freeComponent==nullptr)
            {
                this->freeComponent=new TMFreeHandComponent();
                this->freeComponent->setColor(this->color);
                this->freeComponent->add(QPoint(event->pos().x()-this->canvas->x(),event->pos().y()-this->canvas->y()));
                this->freeComponent->add(QPoint(event->pos().x()-this->canvas->x(),event->pos().y()-this->canvas->y()));
                this->freeComponent->penSize=this->penSize;
                this->canvas->view->add(this->freeComponent);
                this->canvas->backup_list->clear();
                this->canvas->group_list->clear();
                this->drawComponentListUpdate();
                this->ui->drawComponentList->setCurrentRow(0);
                this->canvas->update();
            }
        }
        if(this->mode->toUpper()==QString("line").toUpper())
        {
            if(this->lineComponent==nullptr)
            {
                this->lineComponent=new TMLineComponent();
                this->lineComponent->setColor(this->color);
                this->lineComponent->setP1(QPoint(event->pos().x()-this->canvas->x(),event->pos().y()-this->canvas->y()));
                this->lineComponent->setP2(QPoint(event->pos().x()-this->canvas->x(),event->pos().y()-this->canvas->y()));
                this->lineComponent->penSize=this->penSize;
                this->canvas->view->add(this->lineComponent);
                this->canvas->backup_list->clear();
                this->canvas->group_list->clear();
                this->drawComponentListUpdate();
                this->ui->drawComponentList->setCurrentRow(0);
                this->canvas->update();
            }
        }
        if(this->mode->toUpper()==QString("rectangle").toUpper())
        {
            if(this->rectangleComponent==nullptr)
            {
                this->rectangleComponent=new TMRectangleComponent();
                this->rectangleComponent->setColor(this->color);
                this->rectangleComponent->setX(event->pos().x()-this->canvas->x());
                this->rectangleComponent->setY(event->pos().y()-this->canvas->y());
                this->rectangleComponent->setWidth(0);
                this->rectangleComponent->setHeight(0);
                this->rectangleComponent->penSize=this->penSize;
                this->canvas->view->add(this->rectangleComponent);
                this->canvas->backup_list->clear();
                this->canvas->group_list->clear();
                this->drawComponentListUpdate();
                this->ui->drawComponentList->setCurrentRow(0);
                this->canvas->update();
            }
        }
        if(this->mode->toUpper()==QString("circle").toUpper())
        {
            if(this->circleComponent==nullptr)
            {
                this->circleComponent=new TMCircleComponent();
                this->circleComponent->setColor(this->color);
                this->circleComponent->setP1(QPoint(event->pos().x()-this->canvas->x(),event->pos().y()-this->canvas->y()));
                this->circleComponent->setP2(QPoint(event->pos().x()-this->canvas->x(),event->pos().y()-this->canvas->y()));
                this->circleComponent->setDrawFlag(false);
                this->circleComponent->setClicked(false);
                this->circleComponent->penSize=this->penSize;
                this->canvas->view->add(this->circleComponent);
                this->canvas->backup_list->clear();
                this->canvas->group_list->clear();
                this->drawComponentListUpdate();
                this->ui->drawComponentList->setCurrentRow(0);
                this->canvas->update();
            }
        }
        if(this->mode->toUpper()==QString("ellipse").toUpper())
        {
            if(this->ellipseComponent==nullptr)
            {
                this->ellipseComponent=new TMEllipseComponent();
                this->ellipseComponent->setColor(this->color);
                QRect rect;
                rect.setX(event->pos().x()-this->canvas->x());
                rect.setY(event->pos().y()-this->canvas->y());
                rect.setWidth(0);
                rect.setHeight(0);
                this->ellipseComponent->setRect(rect);
                this->ellipseComponent->penSize=this->penSize;
                this->canvas->view->add(this->ellipseComponent);
                this->canvas->backup_list->clear();
                this->canvas->group_list->clear();
                this->drawComponentListUpdate();
                this->ui->drawComponentList->setCurrentRow(0);
                this->canvas->update();
            }
        }
        if(this->canvas->pickedComponent!=nullptr)
        {
            this->canvas->pickedComponent->setClicked(false);
            this->canvas->pickedComponent=nullptr;
            this->canvas->pickedComponentIndex=-1;
            this->canvas->update();
        }
        if(this->mode->toUpper()==QString("pickup").toUpper())
        {
            int i=this->canvas->getView()->getComponents()->length()-1;
            for(auto com:*this->canvas->getView()->getComponents())
            {
                com->setClicked(false);
                if(com->hasCoordinate(QPoint(event->pos().x()-this->canvas->x(),event->pos().y()-this->canvas->y())))
                {
                   this->oldX=event->pos().x()-this->canvas->x();
                   this->oldY=event->pos().y()-this->canvas->y();
                   this->canvas->pickedComponent=com;
                   this->canvas->pickedComponent->setClicked(true);
                   this->canvas->update();
                   break;
                }
                i--;
            }
            if(i>=0)
            {
                this->ui->drawComponentList->setCurrentRow(i);
                this->canvas->pickedComponentIndex=i;
            }
        }
        if(this->controlKey && this->mode->toUpper()==QString("grouping").toUpper())
        {
            for(auto com:*this->canvas->getView()->getComponents())
            {
                if(com->hasCoordinate(QPoint(event->pos().x()-this->canvas->x(),event->pos().y()-this->canvas->y())))
                {
                   if(!com->isClicked())
                   {
                       com->setClicked(true);
                       this->canvas->group_list->append(com);
                       this->canvas->update();
                   }
                   else
                   {
                       com->setClicked(false);
                       this->canvas->group_list->removeOne(com);
                       this->canvas->update();
                   }
                }
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(this->canvas->hasCoordinate(event->pos()))
    {
        if(this->freeComponent!=nullptr && this->mode->toUpper()==QString("freeHand").toUpper())
        {
            this->freeComponent->add(QPoint(event->pos().x()-this->canvas->x(),event->pos().y()-this->canvas->y()));
            this->canvas->update();
        }
        if(this->lineComponent!=nullptr && this->mode->toUpper()==QString("line").toUpper())
        {
            this->lineComponent->setP2(QPoint(event->pos().x()-this->canvas->x(),event->pos().y()-this->canvas->y()));
            this->canvas->update();
        }
        if(this->rectangleComponent!=nullptr && this->mode->toUpper()==QString("rectangle").toUpper())
        {
            int height=event->pos().y()-this->canvas->y();
            int width=event->pos().x()-this->canvas->x();
            this->rectangleComponent->setWidth(width-this->rectangleComponent->getX());
            this->rectangleComponent->setHeight(height-this->rectangleComponent->getY());
            this->canvas->update();
        }
        if(this->circleComponent!=nullptr && this->mode->toUpper()==QString("circle").toUpper())
        {
            this->circleComponent->setP2(QPoint(event->pos().x()-this->canvas->x(),event->pos().y()-this->canvas->y()));
            this->canvas->update();
        }
        if(this->ellipseComponent!=nullptr && this->mode->toUpper()==QString("ellipse").toUpper())
        {
            int height=event->pos().y()-this->canvas->y();
            int width=event->pos().x()-this->canvas->x();
            QRect rect=this->ellipseComponent->getRect();
            rect.setWidth(width-rect.x());
            rect.setHeight(height-rect.y());
            this->ellipseComponent->setRect(rect);
            this->canvas->update();
        }
        if(this->canvas->pickedComponent!=nullptr && this->mode->toUpper()==QString("pickup").toUpper())
        {
            int x=event->pos().x()-this->canvas->x();
            int y=event->pos().y()-this->canvas->y();
            if(this->canvas->pickedComponent->isResizable())
            {
                this->canvas->pickedComponent->resize(QPoint(x,y),this->shiftKey);
            }
            else
            {
                this->canvas->pickedComponent->moveTo(x-this->oldX,y-this->oldY);
            }
            this->oldX=x;
            this->oldY=y;
            this->canvas->update();
        }

    }

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    /*
    if(this->canvas->hasCoordinate(event->pos()))
    {*/
        this->freeComponent=nullptr;
        this->lineComponent=nullptr;
        this->rectangleComponent=nullptr;
        this->ellipseComponent=nullptr;
        if(this->circleComponent!=nullptr && this->mode->toUpper()==QString("circle").toUpper())
        {
            this->circleComponent->setDrawFlag(true);
            this->canvas->update();
            this->circleComponent=nullptr;
        }
    //}
}



void MainWindow::drawComponentListUpdate()
{
    QList<DrawableComponent *> *list=this->canvas->getView()->getComponents();
    QList<DrawableComponent *>::const_reverse_iterator itr;
    this->ui->drawComponentList->clear();
    for(itr=list->crbegin();itr != list->crend();itr++)
    {
        DrawableComponent *const dc=*itr;
        this->qlit=new QListWidgetItem(dc->toString().toUpper());

        this->ui->drawComponentList->addItem(this->qlit);
        //this->ui->drawComponentList->addItem(dc->toString().toUpper());
    }
}



void MainWindow::on_colorToolBoxRedButton_clicked()
{
    this->color=new QString("red");
}

void MainWindow::on_colorToolBoxBlackButton_clicked()
{
    this->color=new QString("black");
}

void MainWindow::on_colorToolBoxGreenButton_clicked()
{
    this->color=new QString("green");
}

void MainWindow::on_colorToolBoxBlueButton_clicked()
{
    this->color=new QString("blue");
}
void MainWindow::on_colorToolBoxYellowButton_clicked()
{
    this->color=new QString("yellow");
}
void MainWindow::on_colorToolBoxLightBlueButton_clicked()
{
    this->color=new QString("lightblue");
}


void MainWindow::on_freeHandDrawButton_clicked()
{
    this->mode=new QString("freehand");
    this->canvas->setMode(this->mode);
}

void MainWindow::on_clearCanvasButton_clicked()
{
    this->canvas->view->clear();
    this->canvas->backup_list->clear();
    this->canvas->pickedComponent=nullptr;
    this->canvas->pickedComponentIndex=-1;
    this->canvas->group_list->clear();
    if(this->mode->toUpper()==QString("grouping").toUpper())
    {
        this->mode=this->previouseMode;
        this->canvas->setMode(this->mode);
    }
    this->drawComponentListUpdate();
    this->canvas->update();
}

void MainWindow::on_lineDrawButton_clicked()
{
    this->mode=new QString("line");
    this->canvas->setMode(this->mode);
}

void MainWindow::on_rectangleDrawButton_clicked()
{
    this->mode=new QString("rectangle");
    this->canvas->setMode(this->mode);
}

void MainWindow::on_circleDrawButton_clicked()
{
    this->mode=new QString("circle");
    this->canvas->setMode(this->mode);
}

void MainWindow::on_backButton_clicked()
{
    if(this->canvas->getView()->getComponents()->length()>0)
    {
        this->canvas->undo();
        this->drawComponentListUpdate();
        this->canvas->update();
    }

}
void MainWindow::on_restoreButton_clicked()
{
    if(this->canvas->backup_list->length()>0)
    {
        this->canvas->redo();
        this->drawComponentListUpdate();
        this->canvas->update();
    }
}

void MainWindow::on_pickButton_clicked()
{
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->canvas->group_list->clear();
}

void MainWindow::on_ellipseDrawButton_clicked()
{
    this->mode=new QString("ellipse");
    this->canvas->setMode(this->mode);
}


void MainWindow::on_drawComponentList_itemChanged(QListWidgetItem *item)
{
    //cout<<"ItemChanged event raise"<<endl;
    //cout<<"ItemChanged event raise current row : "<<this->ui->drawComponentList->currentRow()<<endl;
    //cout<<"ItemChanged event raise and Item text is : "<<item->text().toStdString()<<endl;
    QList<DrawableComponent *> *list=this->canvas->getView()->getComponents();
    DrawableComponent *com=list->at((list->length()-1)-this->ui->drawComponentList->currentRow());
    item->setText(item->text().toUpper());
    com->setObjectName(item->text().toUpper());

    this->canvas->update();

}

void MainWindow::on_drawComponentList_currentRowChanged(int currentRow)
{
    //cout<<"Row Changed : "<<currentRow<<endl;
    if(currentRow==-1)return;
}

void MainWindow::on_drawComponentList_clicked(const QModelIndex &index)
{
    //cout<<"Clicked chala : "<<index.row()<<endl;
    if(this->canvas->pickedComponent!=nullptr)
    {
        this->canvas->pickedComponent->setClicked(false);
        this->canvas->pickedComponent=nullptr;
        this->canvas->pickedComponentIndex=-1;
        this->canvas->update();
    }
    if(this->controlKey && this->mode->toUpper()==QString("grouping").toUpper())
    {
        QList<DrawableComponent *> *list=this->canvas->getView()->getComponents();
        DrawableComponent *com=list->at((list->length()-1)-index.row());
        if(!com->isClicked())
        {
            com->setClicked(true);
            this->canvas->group_list->append(com);
            this->canvas->update();
        }
        else
        {
            com->setClicked(false);
            this->canvas->group_list->removeOne(com);
            this->canvas->update();
        }
        return;
    }
    else if(this->mode->toUpper()==QString("grouping").toUpper())return;

    QList<DrawableComponent *> *list=this->canvas->getView()->getComponents();
    this->canvas->pickedComponent=list->at((list->length()-1)-index.row());
    this->canvas->pickedComponent->setClicked(true);
    this->canvas->pickedComponentIndex=(list->length()-1)-index.row();
    this->canvas->update();
}

void MainWindow::on_colorToolBoxCyanButton_clicked()
{
    this->color=new QString("cyan");
}

void MainWindow::on_colorToolBoxGrayButton_clicked()
{
    this->color=new QString("gray");
}

void MainWindow::on_colorToolBoxPurpleButton_clicked()
{
    this->color=new QString("purple");

}

void MainWindow::on_colorToolBoxMaroonButton_clicked()
{
    this->color=new QString("maroon");
}

void MainWindow::on_colorToolBoxLimeButton_clicked()
{
    this->color=new QString("lime");
}

void MainWindow::on_colorToolBoxPinkButton_clicked()
{
    this->color=new QString("pink");
}

void MainWindow::on_addNewCanvasButton_clicked()
{
    this->canvas=new Canvas(this);
    this->canvas->setGeometry(this->ui->toolPanel->x()+this->ui->toolPanel->width()+10,this->ui->toolPanel->y(),910,820);
    this->canvas->setStyleSheet("border:1px solid white;background-color:white;color:black;");
    for(auto c:*this->canvasList)c->setVisible(false);
    this->canvas->setVisible(true);
    this->canvas->update();
    this->canvasList->append(this->canvas);

    this->rdb->setChecked(false);

    this->qlit = new QListWidgetItem(this->ui->canvasListWidget);
    this->rdb=new QRadioButton(QString::number(this->canvasList->length()-1));
    this->rdb->setObjectName(QString::number(this->canvasList->length()-1));
    this->rdb->setText(QString::number(this->canvasList->length()-1));
    this->rdb->setFocusPolicy(Qt::NoFocus);
    QObject::connect( this->rdb, SIGNAL( toggled( bool ) ), this,SLOT( on_canvasListWidget_rowClicked( bool ) ) );
    this->ui->canvasListWidget->setItemWidget(this->qlit, this->rdb);
    this->rdb->setChecked(true);
    this->ui->canvasListWidget->scrollToBottom();
}
void MainWindow::on_canvasListWidget_rowClicked(bool state)
{
    QObject *object = QObject::sender();
    QRadioButton *btn = qobject_cast<QRadioButton *>(object);
    if(state)
    {
        //cout<<btn->text().toStdString()<<endl;
        this->canvas->setVisible(false);
        this->canvas=this->canvasList->at(btn->text().toInt());
        this->canvas->setVisible(true);
        this->canvas->setMode(this->mode);
        this->canvas->update();
        this->drawComponentListUpdate();
        if(this->mode->toUpper()!=QString("pickup").toUpper())
        if(this->canvas->pickedComponent!=nullptr)
        {
            this->canvas->pickedComponent->setClicked(false);
            this->canvas->pickedComponent=nullptr;
            this->canvas->pickedComponentIndex=-1;
            this->canvas->update();
        }
        if(this->mode->toUpper()==QString("pickup").toUpper())
        {
            if(this->canvas->pickedComponent!=nullptr && this->canvas->pickedComponentIndex>=0)
            {
                this->ui->drawComponentList->setCurrentRow(this->canvas->pickedComponentIndex);
            }
        }
    }
    else
    {
    }
}

void MainWindow::on_backGroundToggle_clicked()
{
    this->canvas->backgroundToggle();
    this->canvas->update();
}

void MainWindow::on_dsSaveButton_clicked()
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("Save File"),"",tr("(*.board)"));
    cout<<"File Name : "<<fileName.toStdString()<<endl;
    if(fileName.isEmpty())return;
    if(fileName.endsWith(".board"));
    else if(fileName.endsWith("."))fileName=fileName+"board";
    else fileName=fileName+".board";

    QFile saveFile(fileName);
    if(!saveFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open file  "),saveFile.errorString());
        return;
    }
    this->mode=new QString("view");
    this->canvas->setMode(this->mode);
    if(this->canvas->pickedComponent!=nullptr)
    {
        this->canvas->pickedComponent->setClicked(false);
        this->canvas->pickedComponent=nullptr;
        this->canvas->pickedComponentIndex=-1;
        this->canvas->update();
    }
    for(auto can:*this->canvasList)
    {
        can->setMode(this->mode);
        if(can->pickedComponent!=nullptr)
        {
            can->pickedComponent->setClicked(false);
            can->pickedComponent=nullptr;
            can->pickedComponentIndex=-1;
            can->update();
        }
    }
    QJsonObject saveObject;
    //this->canvas->write(saveObject);
    this->write(saveObject);
    saveFile.write(QJsonDocument(saveObject).toJson());
    saveFile.close();
    QMessageBox::information(this, tr("Notification    "),tr("Data Saved.."));
}

void MainWindow::on_dsOpenButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("(*.board)"));
    if(fileName.isEmpty())return;
    if(!fileName.endsWith(".board"))
    {
        QMessageBox::information(this, tr("Notification    "),tr("Unable to open this file"));
        return;
    }
    QFile loadFile(fileName);
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save file.");
        return;
    }
    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    //this->canvas->read(loadDoc.object());
    this->read(loadDoc.object());
    this->canvasListUpdate();
    this->canvas->update();
    this->drawComponentListUpdate();
}
void MainWindow::read(const QJsonObject &json)
{
    QJsonObject j;
    if(json.contains("mode") && json["mode"].isString())
    {
        this->mode=new QString(json["shape"].toString());
    }
    if(json.contains("color") && json["color"].isString())
    {
        this->color=new QString(json["color"].toString());
    }
    if(json.contains("canvasList") && json["canvasList"].isArray())
    {
        QJsonArray componentsArray = json["canvasList"].toArray();
        this->canvasList->clear();
        this->canvasList->reserve(componentsArray.size());
        for(int index=0;index < componentsArray.size();++index)
        {
            QJsonObject comObject=componentsArray[index].toObject();
            Canvas *newCanvas=new Canvas(this);
            newCanvas->setGeometry(this->ui->toolPanel->x()+this->ui->toolPanel->width()+10,this->ui->toolPanel->y(),910,820);
            newCanvas->setStyleSheet("border:1px solid white;background-color:white;color:black;");
            newCanvas->read(comObject);
            this->canvasList->append(newCanvas);
        }
    }
    for(auto c:*this->canvasList)cout<<c->getMode()<<endl;

}

void MainWindow::write(QJsonObject &json)
{
    json["mode"]=*this->mode;
    json["color"]=*this->color;
    QJsonArray drawableArray;
    for(auto drawOb :*this->canvasList)
    {
        if(drawOb!=nullptr)
        {
            QJsonObject drawableObject;
            drawOb->write(drawableObject);
            drawableArray.append(drawableObject);
        }
    }
    json["canvasList"] =drawableArray;
}

void MainWindow::canvasListUpdate()
{
    int i=0;
    this->ui->canvasListWidget->clear();
    QRadioButton *selectRdb;
    for(auto c:*this->canvasList)
    {
        c->setVisible(false);
        this->qlit=new QListWidgetItem(this->ui->canvasListWidget);
        this->rdb=new QRadioButton(QString::number(i));
        if(i==0)
        {
            selectRdb=this->rdb;
        }
        this->rdb->setObjectName(QString::number(i));
        this->rdb->setText(QString::number(i));
        this->rdb->setFocusPolicy(Qt::NoFocus);
        QObject::connect( this->rdb, SIGNAL( toggled( bool ) ), this,SLOT( on_canvasListWidget_rowClicked( bool ) ) );
        this->ui->canvasListWidget->setItemWidget(this->qlit, this->rdb);
        this->ui->canvasListWidget->scrollToBottom();
        i++;
    }
    if(i>=0)
    {
        selectRdb->setChecked(true);
        this->canvas=this->canvasList->at(0);
        this->canvas->update();
        this->drawComponentListUpdate();
    }
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control)
    {
        if(!(this->mode->toUpper()==QString("grouping").toUpper()))
        {
            this->previouseMode=this->mode;
            this->mode=new QString("grouping");
            this->canvas->setMode(this->mode);
        }
        this->canvas->update();
        this->controlKey=true;
    }
    if(event->key()==Qt::Key_Shift)
    {
        this->shiftKey=true;
    }
    if(this->controlKey && event->key()==Qt::Key_Z)
    {
        cout<<"Chala Z"<<endl;
        this->on_backButton_clicked();
    }
    if(this->controlKey && event->key()==Qt::Key_R)
    {
        cout<<"Chala R"<<endl;
        this->on_restoreButton_clicked();
    }
    if(this->controlKey && event->key()==Qt::Key_S)
    {
        this->on_dsSaveButton_clicked();
    }
    if(this->controlKey && event->key()==Qt::Key_O)
    {
        this->on_dsOpenButton_clicked();
    }
    if(this->controlKey && event->key()==Qt::Key_C)
    {
        this->on_copyButton_clicked();
    }
    if(this->controlKey && event->key()==Qt::Key_V)
    {
        this->on_pasteButton_clicked();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control)
    {
        this->controlKey=false;
        if(this->canvas->group_list->length()==0)
        {
            this->mode=this->previouseMode;
            this->canvas->setMode(this->mode);
            this->previouseMode=this->mode;
        }
        this->canvas->update();
    }
    if(event->key()==Qt::Key_Shift)
    {
        this->shiftKey=false;
    }
}

void MainWindow::on_penSlider_valueChanged(int value)
{
    if(value>0)this->penSize=value;
}

void MainWindow::on_groupButton_clicked()
{
    if(this->canvas->group_list->length()==0)return;
    this->groupComponent=new TMGroupComponent();
    this->groupComponent->setColor(this->color);
    this->groupComponent->penSize=this->penSize;
    for(auto com:*this->canvas->group_list)
    {
        this->groupComponent->add(com);
        this->canvas->getView()->getComponents()->removeOne(com);
    }
    this->canvas->view->add(this->groupComponent);
    this->canvas->pickedComponent=this->groupComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->canvas->backup_list->clear();
    this->canvas->group_list->clear();
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
}

void MainWindow::on_unGroupButton_clicked()
{
    if(this->canvas->group_list->length()!=0 && this->mode->toUpper()==QString("Grouping").toUpper())
    {
        cout<<"Chala "<<endl;
        for(auto com:*this->canvas->group_list)com->setClicked(false);
        this->canvas->update();
        this->mode=this->previouseMode;
        this->canvas->setMode(this->mode);
        this->canvas->group_list->clear();
    }
    if(this->canvas->pickedComponent!=nullptr && this->canvas->pickedComponent->shape.toUpper()==QString("Group").toUpper())
    {
        TMGroupComponent *group=(TMGroupComponent *)this->canvas->pickedComponent;
        this->canvas->getView()->getComponents()->removeOne(group);
        for(auto com:*group->getChilds())
        {
            com->setClicked(false);
            this->canvas->getView()->getComponents()->append(com);
        }
        this->drawComponentListUpdate();
        this->canvas->pickedComponent=nullptr;
        this->canvas->update();
    }
}

void MainWindow::on_deleteButton_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)
    {
        this->canvas->pickedComponent->setClicked(false);
        this->canvas->backup_list->append(this->canvas->pickedComponent);
        this->canvas->getView()->getComponents()->removeOne(this->canvas->pickedComponent);
        this->drawComponentListUpdate();
        this->canvas->update();
        this->canvas->pickedComponent=nullptr;
        this->canvas->pickedComponentIndex=-1;
    }
}

void MainWindow::on_colorPickerButton_clicked()
{
    QColor color=QColorDialog::getColor(Qt::yellow,this);
    if(color.isValid())
    {
        //cout<< "Color Choosen : " << color.name().toStdString()<<endl;
        this->color=new QString(color.name());
    }
}

void MainWindow::on_showSymbolsButton_clicked()
{
    //this->ui->symbolsFrame->setVisible(true);
    this->ui->symbolsFrame->show();
}

void MainWindow::on_showSymbolsCloseButton_clicked()
{
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_imagePickupButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("Select Image File"),"",tr("(*.jpeg);;(*.png);;(*.jpg)"));
    //QString fileName=QFileDialog::getOpenFileName(this,tr("Select Image File"),"",tr("(*)"));
    if(fileName.isEmpty())return;
    cout<<"Image filename : "<<fileName.toStdString()<<endl;
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(fileName);
    this->pixmapComponent->setRect(QRect(100,100,200,200));
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
}

void MainWindow::on_drawComponentList_customContextMenuRequested(const QPoint &pos)
{

    QPoint point = this->ui->drawComponentList->mapToGlobal(pos);
    QMenu submenu(this);
    //submenu.addAction("ADD");
    submenu.setStyleSheet("background-color:lightblue;color:black;");
    submenu.addAction("Rename");
    QAction* rightClickItem =submenu.exec(point);
    if (rightClickItem && rightClickItem->text().contains("Rename") )
    {
        QListWidgetItem *listItem=this->ui->drawComponentList->itemAt(pos);
        if(listItem==nullptr)return;
        listItem->setFlags(listItem->flags() | Qt::ItemIsEditable);
        this->ui->drawComponentList->editItem(listItem);
        //cout<<"Menu item index row :"<<this->ui->drawComponentList->indexAt(pos).row()<<",And Text : "<<listItem->text().toStdString()<<endl;
    }
}

void MainWindow::on_addSymbolButton_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(":/icons/plus_icon.png");
    this->pixmapComponent->setRect(QRect(300,300,24,24));
    this->pixmapComponent->setObjectName("Symbol");
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_minusSymbolButton_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(":/icons/minus_icon.png");
    this->pixmapComponent->setRect(QRect(300,300,24,24));
    this->pixmapComponent->setObjectName("Symbol");
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_multiplySymbolButton_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(":/icons/multiply_icon.png");
    this->pixmapComponent->setRect(QRect(300,300,24,24));
    this->pixmapComponent->setObjectName("Symbol");
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_divideSymbolButton_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(":/icons/divide_icon.png");
    this->pixmapComponent->setRect(QRect(300,300,24,24));
    this->pixmapComponent->setObjectName("Symbol");
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_infiniteSymbolButton_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(":/icons/infinite_icon.png");
    this->pixmapComponent->setRect(QRect(300,300,24,24));
    this->pixmapComponent->setObjectName("Symbol");
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_divideSymbolButton2_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(":/icons/divide_icon2.png");
    this->pixmapComponent->setRect(QRect(300,300,24,24));
    this->pixmapComponent->setObjectName("Symbol");
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_rootSymbolButton_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(":/icons/root_icon.png");
    this->pixmapComponent->setRect(QRect(300,300,24,24));
    this->pixmapComponent->setObjectName("Symbol");
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_percentageSymbolButton_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(":/icons/percentage_icon.png");
    this->pixmapComponent->setRect(QRect(300,300,24,24));
    this->pixmapComponent->setObjectName("Symbol");
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_piSymbolButton_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(":/icons/pi_icon.png");
    this->pixmapComponent->setRect(QRect(300,300,24,24));
    this->pixmapComponent->setObjectName("Symbol");
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_leftParentheseSymbolButton_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(":/icons/left_parenthese_icon.png");
    this->pixmapComponent->setRect(QRect(300,300,24,24));
    this->pixmapComponent->setObjectName("Symbol");
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_equaltoSymbolButton_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(":/icons/equalto_icon.png");
    this->pixmapComponent->setRect(QRect(300,300,24,24));
    this->pixmapComponent->setObjectName("Symbol");
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_sigmaSymbolButton_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(":/icons/sigma_icon.png");
    this->pixmapComponent->setRect(QRect(300,300,24,24));
    this->pixmapComponent->setObjectName("Symbol");
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_squareSymbolButton_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(":/icons/square_icon.png");
    this->pixmapComponent->setRect(QRect(300,300,24,24));
    this->pixmapComponent->setObjectName("Symbol");
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_powerSymbolButton_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(":/icons/pow_sign_icon.png");
    this->pixmapComponent->setRect(QRect(300,300,24,24));
    this->pixmapComponent->setObjectName("Symbol");
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_rightParentheseSymbolButton_clicked()
{
    if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
    this->pixmapComponent=new TMPixmapComponent();
    this->pixmapComponent->setColor(this->color);
    this->pixmapComponent->penSize=this->penSize;
    this->pixmapComponent->setPixMapPath(":/icons/right_parenthese_icon.png");
    this->pixmapComponent->setRect(QRect(300,300,24,24));
    this->pixmapComponent->setObjectName("Symbol");
    this->canvas->view->add(this->pixmapComponent);
    this->canvas->pickedComponent=this->pixmapComponent;
    this->canvas->pickedComponent->setClicked(true);
    this->drawComponentListUpdate();
    this->ui->drawComponentList->setCurrentRow(0);
    this->canvas->update();
    this->mode=new QString("pickup");
    this->canvas->setMode(this->mode);
    this->ui->symbolsFrame->hide();
}

void MainWindow::on_copyButton_clicked()
{
    if(this->copyComponentsList!=nullptr)this->copyComponentsList->clear();
    if(this->canvas->pickedComponent!=nullptr)
    {
        if(this->canvas->pickedComponent->shape.toUpper()==QString("Line").toUpper())
        {
            this->copyComponentsList->append(new TMLineComponent((TMLineComponent *)this->canvas->pickedComponent));
        }
        if(this->canvas->pickedComponent->shape.toUpper()==QString("Circle").toUpper())
        {
            this->copyComponentsList->append(new TMCircleComponent((TMCircleComponent *)this->canvas->pickedComponent));
        }
        if(this->canvas->pickedComponent->shape.toUpper()==QString("Ellipse").toUpper())
        {
            this->copyComponentsList->append(new TMEllipseComponent((TMEllipseComponent *)this->canvas->pickedComponent));
        }
        if(this->canvas->pickedComponent->shape.toUpper()==QString("FreeHand").toUpper())
        {
            this->copyComponentsList->append(new TMFreeHandComponent((TMFreeHandComponent *)this->canvas->pickedComponent));
        }
        if(this->canvas->pickedComponent->shape.toUpper()==QString("Group").toUpper())
        {
            this->copyComponentsList->append(new TMGroupComponent((TMGroupComponent *)this->canvas->pickedComponent));
        }
        if(this->canvas->pickedComponent->shape.toUpper()==QString("Pixmap").toUpper())
        {
            this->copyComponentsList->append(new TMPixmapComponent((TMPixmapComponent *)this->canvas->pickedComponent));
        }
        if(this->canvas->pickedComponent->shape.toUpper()==QString("Rectangle").toUpper())
        {
            this->copyComponentsList->append(new TMRectangleComponent((TMRectangleComponent *)this->canvas->pickedComponent));
        }
    }
    if(this->canvas->group_list->length()!=0 && this->mode->toUpper()==QString("Grouping").toUpper())
    {
        if(this->canvas->group_list->length()==0)return;
        for(auto com:*this->canvas->group_list)
        {
            if(com->shape.toUpper()==QString("Line").toUpper())
            {
                this->copyComponentsList->append(new TMLineComponent((TMLineComponent *)com));
            }
            if(com->shape.toUpper()==QString("Circle").toUpper())
            {
                this->copyComponentsList->append(new TMCircleComponent((TMCircleComponent *)com));
            }
            if(com->shape.toUpper()==QString("Ellipse").toUpper())
            {
                this->copyComponentsList->append(new TMEllipseComponent((TMEllipseComponent *)com));
            }
            if(com->shape.toUpper()==QString("FreeHand").toUpper())
            {
                this->copyComponentsList->append(new TMFreeHandComponent((TMFreeHandComponent *)com));
            }
            if(com->shape.toUpper()==QString("Group").toUpper())
            {
                this->copyComponentsList->append(new TMGroupComponent((TMGroupComponent *)com));
            }
            if(com->shape.toUpper()==QString("Pixmap").toUpper())
            {
                this->copyComponentsList->append(new TMPixmapComponent((TMPixmapComponent *)com));
            }
            if(com->shape.toUpper()==QString("Rectangle").toUpper())
            {
                this->copyComponentsList->append(new TMRectangleComponent((TMRectangleComponent *)com));
            }
        }
    }
}

void MainWindow::on_pasteButton_clicked()
{
    if(this->copyComponentsList->length()!=0)
    {
        QList<DrawableComponent *> *tmpList=new QList<DrawableComponent *>();
        for(auto com:*this->copyComponentsList)
        {

            if(this->canvas->pickedComponent!=nullptr)this->canvas->pickedComponent->setClicked(false);
            if(com->shape.toUpper()==QString("Line").toUpper())
            {
                TMLineComponent *line=new TMLineComponent((TMLineComponent *)com);
                this->canvas->view->add(line);
                line->moveTo(10,10);
                tmpList->append(new TMLineComponent(line));
                this->canvas->pickedComponent=line;
                this->canvas->pickedComponent->setClicked(true);
            }
            if(com->shape.toUpper()==QString("Circle").toUpper())
            {
                TMCircleComponent *circle=new TMCircleComponent((TMCircleComponent *)com);
                this->canvas->view->add(circle);
                circle->moveTo(10,10);
                tmpList->append(new TMCircleComponent(circle));
                this->canvas->pickedComponent=circle;
                this->canvas->pickedComponent->setClicked(true);
            }
            if(com->shape.toUpper()==QString("Ellipse").toUpper())
            {
                TMEllipseComponent *ellipse=new TMEllipseComponent((TMEllipseComponent *)com);
                this->canvas->view->add(ellipse);
                ellipse->moveTo(10,10);
                tmpList->append(new TMEllipseComponent(ellipse));
                this->canvas->pickedComponent=ellipse;
                this->canvas->pickedComponent->setClicked(true);
            }
            if(com->shape.toUpper()==QString("FreeHand").toUpper())
            {
                TMFreeHandComponent *freeHand=new TMFreeHandComponent((TMFreeHandComponent *)com);
                this->canvas->view->add(freeHand);
                freeHand->moveTo(10,10);
                tmpList->append(new TMFreeHandComponent(freeHand));
                this->canvas->pickedComponent=freeHand;
                this->canvas->pickedComponent->setClicked(true);
            }
            if(com->shape.toUpper()==QString("Group").toUpper())
            {
                TMGroupComponent *group=new TMGroupComponent((TMGroupComponent *)com);
                this->canvas->view->add(group);
                group->moveTo(10,10);
                tmpList->append(new TMGroupComponent(group));
                this->canvas->pickedComponent=group;
                this->canvas->pickedComponent->setClicked(true);
            }
            if(com->shape.toUpper()==QString("Pixmap").toUpper())
            {
                TMPixmapComponent *pixmap=new TMPixmapComponent((TMPixmapComponent *)com);
                this->canvas->view->add(pixmap);
                pixmap->moveTo(10,10);
                tmpList->append(new TMPixmapComponent(pixmap));
                this->canvas->pickedComponent=pixmap;
                this->canvas->pickedComponent->setClicked(true);
            }
            if(com->shape.toUpper()==QString("Rectangle").toUpper())
            {
                TMRectangleComponent *rectangle=new TMRectangleComponent((TMRectangleComponent *)com);
                this->canvas->view->add(rectangle);
                rectangle->moveTo(10,10);
                tmpList->append(new TMRectangleComponent(rectangle));
                this->canvas->pickedComponent=rectangle;
                this->canvas->pickedComponent->setClicked(true);
            }
            this->drawComponentListUpdate();
            this->ui->drawComponentList->setCurrentRow(0);
            this->canvas->update();
        }
        this->copyComponentsList->clear();
        this->copyComponentsList=tmpList;
        this->mode=new QString("pickup");
        this->canvas->setMode(this->mode);
    }

}

void MainWindow::on_fullScreenButton_clicked()
{
    if(!this->widFlag)
    {
        this->ui->fullScreenButton->setIcon(QPixmap(":/icons/reduceScreenIcon.png"));
        this->ui->fullScreenButton->setIconSize(QSize(51,41));
        this->ui->fullScreenButton->setToolTip("Window");
        this->widPos=this->pos();
        this->setWindowFlags(Qt::FramelessWindowHint);

        /*
        this->setWindowState(Qt::WindowFullScreen);
*/
        //this->setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowSystemMenuHint);
        this->move(this->widPos);
        //this->previousGeometry=this->geometry();
        this->showFullScreen();
        this->widFlag=true;
    }
    else
    {                
        this->ui->fullScreenButton->setIcon(QPixmap(":/icons/fullScreenIcon.png"));
        this->ui->fullScreenButton->setIconSize(QSize(51,41));
        this->ui->fullScreenButton->setToolTip("FullScreen");

        this->setWindowFlags(Qt::Window);
        this->move(this->widPos);        
        //this->setGeometry(this->previousGeometry);
        //this->show();
        this->showFullScreen();
        this->widFlag=false;
    }
}

void MainWindow::on_videoRecordingStartButton_clicked()
{
    if(!this->recordingFlag)
    {
        /*
        QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),".",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
        cout<<"Directory"<<dir.toStdString()<<endl;
            */
        this->videoFileName=QFileDialog::getSaveFileName(this,tr("File"),"",tr("(*.avi)"));

        if(this->videoFileName.isEmpty())return;
        if(this->videoFileName.endsWith(".avi"));
        else if(this->videoFileName.endsWith("."))this->videoFileName=this->videoFileName+"avi";
        else this->videoFileName=this->videoFileName+".avi";
        cout<<"File Name : "<<this->videoFileName.toStdString()<<endl;

        std::string filename=this->videoFileName.toStdString();
        int fcc=cv::VideoWriter::fourcc('D','I','V','X');
        int fps=5;
        cv::Size frameSize(this->crop_rect.width(),this->crop_rect.height());
        this->videoWriter=cv::VideoWriter(filename,fcc,fps,frameSize,true);//CV_FOURCC_PROMPT
        if(this->videoWriter.isOpened())cout<<"Video file open"<<endl;

        this->recordingFlag=true;
        this->ui->videoRecordingStartButton->setIcon(QPixmap(":/icons/pause_video_icon2.png"));
        this->ui->videoRecordingStartButton->setIconSize(QSize(51,41));
        this->ui->videoRecordingStartButton->setToolTip("Pause");
        this->recordingStateFlag=true;
        QTimer::singleShot(1000,this,&MainWindow::takeScreenShot);
    }
    else
    {
        if(this->recordingStateFlag)
        {
            cout<<"Image List(Pause) : "<<this->imageList->length()<<endl;
            this->ui->videoRecordingStartButton->setIcon(QPixmap(":/icons/play_video_icon.png"));
            this->ui->videoRecordingStartButton->setIconSize(QSize(51,41));
            this->ui->videoRecordingStartButton->setToolTip("Resume");
            this->recordingStateFlag=false;
        }
        else
        {
            cout<<"Image List(Resume) : "<<this->imageList->length()<<endl;
            this->recordingStateFlag=true;
            this->takeScreenShot();
            this->ui->videoRecordingStartButton->setIcon(QPixmap(":/icons/pause_video_icon2.png"));
            this->ui->videoRecordingStartButton->setIconSize(QSize(51,41));
            this->ui->videoRecordingStartButton->setToolTip("Pause");
        }
    }
}

void MainWindow::on_videoRecordingStopButton_clicked()
{
    if(this->recordingFlag)
    {

        cout<<"Image Database List(Saving) : "<<this->imageDatabase->length()<<endl;
        this->recordingStateFlag=false;
        this->ui->progressBar->setMinimum(0);
        this->ui->progressBar->setMaximum(1000);
        this->ui->progressBar->setRange(0,1000);
        this->ui->progressBar->setValue(0);
        this->ui->progressBar->show();
        this->setDisabled(true);
        QEventLoop loop;
        int i=0;
        while(i<1000)
        {
            this->ui->progressBar->setValue(i++);
            loop.processEvents();
        }
        this->videoWriter.release();
        this->ui->progressBar->hide();
        if(!this->videoWriter.isOpened())cout<<"Video file close"<<endl;
        cout<<"Saved"<<endl;


        /*
        this->recordingStateFlag=false;
        this->ui->progressBar->setMinimum(0);
        this->ui->progressBar->setMaximum(this->imageDatabase->length()*1000);
        this->ui->progressBar->setRange(0,this->imageDatabase->length()*1000);
        this->ui->progressBar->setValue(0);
        this->ui->progressBar->show();
        this->setDisabled(true);

        std::string filename=this->videoFileName.toStdString();
        int fcc=cv::VideoWriter::fourcc('D','I','V','X');
        int fps=5;
        cv::Size frameSize(this->crop_rect.width(),this->crop_rect.height());
        cv::VideoWriter writer = cv::VideoWriter(filename,fcc,fps,frameSize,true);//CV_FOURCC_PROMPT
        //writer.release();
        //writer.open(filename,fcc,fps,frameSize,true);
        if(writer.isOpened())cout<<"Video file open"<<endl;
        //int step=this->imageList->length()/100;
        //assert(writer.isOpened());
        int i=0;
        QEventLoop loop;
        for(auto imageList:*this->imageDatabase)
        {
            cout<<"Image Database( "<<i<<" )(Saving) : "<<imageList->length()<<endl;
            for(auto inImage:*imageList)
            {
                cv::Mat  mat( inImage->height(), inImage->width(),CV_8UC4,const_cast<uchar*>(inImage->bits()),static_cast<size_t>(inImage->bytesPerLine()));
                cv::cvtColor(mat,mat,cv::COLOR_BGR2RGB);//CV_BGR2RGB
                cv::cvtColor(mat,mat,cv::COLOR_RGB2BGR);
                if(mat.empty())cout<<"Empty"<<endl;
                if(!mat.empty())writer.write(mat);
                this->ui->progressBar->setValue(i++);
                loop.processEvents();
            }
        }
        writer.release();
        this->ui->progressBar->hide();
        if(!writer.isOpened())cout<<"Video file close"<<endl;
        cout<<"Saved"<<endl;

        */
//Second Way
        /*
        cout<<"Image List(Saving) : "<<this->imageList->length()<<endl;
        cout<<CV_VERSION<<endl;
        this->recordingStateFlag=false;

        this->ui->progressBar->setMinimum(0);
        this->ui->progressBar->setMaximum(this->imageList->length());
        this->ui->progressBar->setRange(0,this->imageList->length());
        this->ui->progressBar->setValue(0);
        this->ui->progressBar->show();
        this->setDisabled(true);

        std::string filename=this->videoFileName.toStdString();
        //std::string filename="video.avi";
        //int fcc=cv::CV_FOURCC('D','I','V','X');
        int fcc=cv::VideoWriter::fourcc('D','I','V','X');
        int fps=5;

        //cv::Size frameSize(cap.get(CV_CAP_PROP_FRAME_WIDTH),cap.get(CV_CAP_PROP_FRAME_HEIGHT));
        cv::Size frameSize(this->crop_rect.width(),this->crop_rect.height());

        cv::VideoWriter writer = cv::VideoWriter(filename,fcc,fps,frameSize,true);//CV_FOURCC_PROMPT
        //writer.release();
        //writer.open(filename,fcc,fps,frameSize,true);
        if(writer.isOpened())cout<<"Video file open"<<endl;

        int step=this->imageList->length()/100;
        //assert(writer.isOpened());
        int i=0;
        int j=0;
        QEventLoop loop;

        for(auto inImage:*this->imageList)
        {
            cv::Mat  mat( inImage->height(), inImage->width(),CV_8UC4,const_cast<uchar*>(inImage->bits()),static_cast<size_t>(inImage->bytesPerLine()));
            cv::cvtColor(mat,mat,cv::COLOR_BGR2RGB);//CV_BGR2RGB
            cv::cvtColor(mat,mat,cv::COLOR_RGB2BGR);
            if(mat.empty())cout<<"Empty"<<endl;
            //waitKey(1000);
            if(!mat.empty())writer.write(mat);
            this->ui->progressBar->setValue(i++);
            loop.processEvents();
        }
        writer.release();
        this->ui->progressBar->hide();
        if(!writer.isOpened())cout<<"Video file close"<<endl;
        cout<<"Saved"<<endl;


        */



        this->ui->videoRecordingStartButton->setIcon(QPixmap(":/icons/video_camera_icon.png"));
        this->ui->videoRecordingStartButton->setIconSize(QSize(51,41));
        this->ui->videoRecordingStartButton->setToolTip("Start Recording");        
        this->recordingFlag=false;

        //this->imageList->clear();
        //this->imageDatabase->clear();
        //this->imageDatabase->append(this->imageList);
        this->setDisabled(false);
    }
}
void MainWindow::takeScreenShot()
{
    if(!this->recordingStateFlag)return;
    this->crop_rect=this->geometry();
    QImage inputImage;
    inputImage=qApp->screens().at(0)->grabWindow(QDesktopWidget().winId(),crop_rect.x(),crop_rect.y(),crop_rect.width(),crop_rect.height()).toImage();
    if((!inputImage.isNull()) && (this->windowState()!=Qt::WindowMinimized))
    {
        cv::Mat  mat( inputImage.height(), inputImage.width(),CV_8UC4,const_cast<uchar*>(inputImage.bits()),static_cast<size_t>(inputImage.bytesPerLine()));
        cv::cvtColor(mat,mat,cv::COLOR_BGR2RGB);//CV_BGR2RGB
        cv::cvtColor(mat,mat,cv::COLOR_RGB2BGR);
        if(!mat.empty())this->videoWriter.write(mat);
    }
    /*
    if(!inputImage.isNull())
    {
        if(this->imageList->length()==1000)
        {
            cout<<"Image List length greater than 1000 "<<endl;
            this->imageList=new QList<QImage *>();
            this->imageDatabase->append(this->imageList);
        }
        this->imageList->append(new QImage(inputImage));
    }
    */
    QTimer::singleShot(200,this,&MainWindow::takeScreenShot);
}


