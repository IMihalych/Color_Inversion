#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFileDialog>
#include <QThread>
#include "imageprocessor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onSelectFile();
    void onInvertColors();

private slots:
    void onUpdateImage(QImage image);

private:

    QGraphicsView *graphicsView;
    ImageProcessor *processor;
    QString currentFile;
    QImage image;
        
};

#endif // MAINWINDOW_H
