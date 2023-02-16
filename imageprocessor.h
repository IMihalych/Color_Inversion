#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>
#include <QImage>
//#include <QMessageBox>

class ImageProcessor : public QObject
{
    Q_OBJECT

public:
    ImageProcessor(const QImage &image);

public slots:
    void process();

signals:
    void finished();
    void resultReady(const QImage &result);

private:
    QImage image;
};

#endif // IMAGEPROCESSOR_H
