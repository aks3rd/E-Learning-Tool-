#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "canvas.h"
#include <QMainWindow>
#include<QListWidgetItem>
#include<QRadioButton>
#include<QFileDialog>
#include<QMessageBox>
#include<QKeyEvent>
#include<QColorDialog>

#include<QSystemTrayIcon>

#include<QScreen>
#include<QDesktopWidget>
#include<QTimer>
#include <QtCore>
#include<QtGui>
#include<QProgressDialog>

#include<QGridLayout>

#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/video.hpp"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv_modules.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.h>

#include "qmouseeventtransition.h"
#include "tmfreehandcomponent.h"
#include "tmlinecomponent.h"
#include "tmrectanglecomponent.h"
#include "tmcirclecomponent.h"
#include "tmellipsecomponent.h"
#include "tmgroupcomponent.h"
#include "tmpixmapcomponent.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initComponents();
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event)override;
    void keyReleaseEvent(QKeyEvent *event)override;
    void drawComponentListUpdate();
    void read(const QJsonObject &json);
    void write(QJsonObject &json);
    void canvasListUpdate();
    void takeScreenShot();

private slots:
    void on_colorToolBoxRedButton_clicked();

    void on_colorToolBoxBlackButton_clicked();

    void on_colorToolBoxGreenButton_clicked();

    void on_colorToolBoxBlueButton_clicked();

    void on_freeHandDrawButton_clicked();

    void on_clearCanvasButton_clicked();

    void on_lineDrawButton_clicked();

    void on_colorToolBoxYellowButton_clicked();

    void on_colorToolBoxLightBlueButton_clicked();

    void on_rectangleDrawButton_clicked();

    void on_circleDrawButton_clicked();

    void on_backButton_clicked();

    void on_pickButton_clicked();

    void on_ellipseDrawButton_clicked();

    void on_restoreButton_clicked();

    void on_drawComponentList_itemChanged(QListWidgetItem *item);

    void on_drawComponentList_currentRowChanged(int currentRow);

    void on_drawComponentList_clicked(const QModelIndex &index);

    void on_colorToolBoxCyanButton_clicked();

    void on_colorToolBoxGrayButton_clicked();

    void on_colorToolBoxPurpleButton_clicked();

    void on_colorToolBoxMaroonButton_clicked();

    void on_colorToolBoxLimeButton_clicked();

    void on_colorToolBoxPinkButton_clicked();

    void on_addNewCanvasButton_clicked();

    void on_canvasListWidget_rowClicked(bool state);

    void on_backGroundToggle_clicked();

    void on_dsSaveButton_clicked();

    void on_dsOpenButton_clicked();

    void on_penSlider_valueChanged(int value);

    void on_groupButton_clicked();

    void on_unGroupButton_clicked();

    void on_deleteButton_clicked();

    void on_colorPickerButton_clicked();

    void on_showSymbolsButton_clicked();

    void on_showSymbolsCloseButton_clicked();

    void on_imagePickupButton_clicked();

    void on_drawComponentList_customContextMenuRequested(const QPoint &pos);

    void on_addSymbolButton_clicked();

    void on_minusSymbolButton_clicked();

    void on_multiplySymbolButton_clicked();

    void on_divideSymbolButton_clicked();

    void on_infiniteSymbolButton_clicked();

    void on_divideSymbolButton2_clicked();

    void on_rootSymbolButton_clicked();

    void on_percentageSymbolButton_clicked();

    void on_piSymbolButton_clicked();

    void on_leftParentheseSymbolButton_clicked();

    void on_equaltoSymbolButton_clicked();

    void on_sigmaSymbolButton_clicked();

    void on_squareSymbolButton_clicked();

    void on_powerSymbolButton_clicked();

    void on_rightParentheseSymbolButton_clicked();

    void on_copyButton_clicked();

    void on_pasteButton_clicked();

    void on_fullScreenButton_clicked();

    void on_videoRecordingStartButton_clicked();

    void on_videoRecordingStopButton_clicked();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *taskBarIcon;
    QList<QPoint>  *points;
    QList<Canvas *> *canvasList;
    QList<DrawableComponent *> *copyComponentsList;
    QListWidgetItem *qlit;
    QRadioButton *rdb;
    bool controlKey;
    bool shiftKey;
    bool widFlag;
    QPoint widPos;
    int heightOffSet;
    int oldX;
    int oldY;
    int penSize=1;
    QString *color;
    QString *mode;
    QString *previouseMode;
    QPixmap *cursor;
    Canvas *canvas;
    bool recordingFlag;
    bool recordingStateFlag;
    QRect crop_rect;
    QList<QImage *> *imageList;
    QList<QList<QImage *> *> *imageDatabase;
    cv::VideoWriter videoWriter;
    QRect previousGeometry;

    QGridLayout *gridLayout;

    QString videoFileName;
    DrawableComponent *pickedComponent;
    TMFreeHandComponent *freeComponent;
    TMLineComponent *lineComponent;
    TMRectangleComponent *rectangleComponent;
    TMCircleComponent *circleComponent;
    TMEllipseComponent *ellipseComponent;
    TMGroupComponent *groupComponent;
    TMPixmapComponent *pixmapComponent;

};
#endif // MAINWINDOW_H
