#include "imageprocessor.h"

ImageProcessor::ImageProcessor(const QImage &image)
    : image(image)
{
}

/*void ImageProcessor::process()
{
    QImage result(image.width(), image.height(), QImage::Format_ARGB32);

    for (int y = 0; y < image.height(); y++) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        QRgb *resultScanLine = reinterpret_cast<QRgb*>(result.scanLine(y));
        for (int x = 0; x < image.width(); x++) {
            QRgb pixel = scanLine[x];
            QRgb invertedPixel = qRgba(255 - qRed(pixel),
             255 - qGreen(pixel),
             255 - qBlue(pixel),
             qAlpha(pixel));
            resultScanLine[x] = invertedPixel;
        }
    }

    emit resultReady(result);
    emit finished();
}*/

void ImageProcessor::process()
{
    QImage result = image;
    for (int y = 0; y < result.height(); y++) {
        QRgb *row = (QRgb*)result.scanLine(y);
        for (int x = 0; x < result.width(); x++) {
            QRgb pixel = row[x];
            row[x] = qRgb(255 - qRed(pixel), 255 - qGreen(pixel), 255 - qBlue(pixel));
        }
    }

    emit resultReady(result);
    emit finished();
}
