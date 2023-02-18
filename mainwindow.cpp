#include "mainwindow.h"
#include "imageprocessor.h"
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Создаю основной макет
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Создаю метку с текстом для кнопки выбора файла
    QLabel *fileLabel = new QLabel("Выберите файл изображения:");
    mainLayout->addWidget(fileLabel);

    // Создаю кнопку выбора файла
    QPushButton *fileButton = new QPushButton("Открыть изображение");
    connect(fileButton, &QPushButton::clicked, this, &MainWindow::onSelectFile);
    mainLayout->addWidget(fileButton);

    // Создаю графическое представление для отображения изображения
    graphicsView = new QGraphicsView;
    graphicsView->setFixedSize(400, 400);
    mainLayout->addWidget(graphicsView);

    // Создаю кнопку инверсии цвета
    QPushButton *invertButton = new QPushButton("Инвертировать");
    connect(invertButton, &QPushButton::clicked, this, &MainWindow::onInvertColors);
    mainLayout->addWidget(invertButton);

    // Устанавливаю основной макет для окна
    setCentralWidget(centralWidget);
}

void MainWindow::onSelectFile()
{
    // Отображение диалогового окна для выбора файла изображения
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть изображение"), ".", tr("Image Files (*.png)"));

    // Загружаю изображение в графическое представление
    QPixmap pixmap(fileName);
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(pixmap);
    graphicsView->setScene(scene);
    currentFile = fileName;
    image = pixmap.toImage();
}

void MainWindow::onInvertColors()
{
    // Создаю новый объект процессора изображений и перемещаю его в новый поток
    ImageProcessor *processor = new ImageProcessor(image);
    QThread *thread = new QThread;
    processor->moveToThread(thread);

    // Подключаю сигналы и слоты для процессора изображения и потока
    connect(thread, SIGNAL(started()), processor, SLOT(process()));
    connect(processor, SIGNAL(finished()), thread, SLOT(quit()));
    connect(processor, SIGNAL(finished()), processor, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(processor, SIGNAL(resultReady(QImage)), this, SLOT(onUpdateImage(QImage)));

    // Запуск обработки изображения в потоке
    thread->start();
}

void MainWindow::onUpdateImage(QImage image)
{
    // Обновляю графическое представление с инверcированным изображением
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(image));
    graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
}
