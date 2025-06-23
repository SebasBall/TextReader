#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->locationsList->addItem("Spanish");
    ui->locationsList->addItem("Italian");
    ui->locationsList->addItem("English");
    ui->locationsList->addItem("German");

    connect(&speech, &QTextToSpeech::stateChanged, this, &MainWindow::on_speech_end);

    ui->voiceSelection->setDuplicatesEnabled(false);
    qDebug() << "The application has been opened succesfully";

    QString stateStr = "Speaker State: ";
    switch (speech.state()) {
    case QTextToSpeech::Ready:
        stateStr += "Ready";
        break;
    case QTextToSpeech::Speaking:
        stateStr += "Speaking";
        break;
    case QTextToSpeech::Paused:
        stateStr += "Paused";
        break;
    default:
        stateStr += "Unknown";
        break;
    }
    qDebug() << stateStr;
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_playButton_clicked()
{
    qDebug() << "The play button has been pressed";
    if(StopSpeech){
        speech.stop();
        setUpVoice(voices, ui->voiceSelection->currentText(), speech);
        if(!(ui->textToRead->toPlainText().isEmpty())){
            ui->playButton->setText("Pause");
            speech.say(ui->textToRead->toPlainText());
            StopSpeech = false;
            PauseSpeech = false;
        }
    }else if(PauseSpeech){
        speech.resume();
        ui->playButton->setText("Pause");
        PauseSpeech = false;
    }else if(!PauseSpeech){
        speech.pause();
        ui->playButton->setText("Play");
        PauseSpeech = true;
    }

    qDebug() << "The play button has been executed successfuly";
}

void MainWindow::setUpVoice(QVector<QVoice> voices,QString voiceName, QTextToSpeech &speech){
    for (const QVoice &voice : voices) {
        if (voice.name() == voiceName){
            speech.setVoice(voice);
        }
    }
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    speech.pause();
}


void MainWindow::on_horizontalSlider_sliderReleased()
{
    speech.resume();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    double rate = value/100.0;
    speech.setRate(rate);
}

void MainWindow::on_speech_end(){
    if (speech.state() == QTextToSpeech::Ready && !StopSpeech){
        ui->playButton->setText("Play");
        StopSpeech = true;
    }
}

void MainWindow::on_textToRead_textChanged()
{
    speech.pause();
    StopSpeech = true;
    ui->playButton->setText("Play");
}


void MainWindow::on_stopButton_clicked()
{
    speech.pause();
    StopSpeech = true;
    ui->playButton->setText("Play");
}

void MainWindow::on_locationsList_currentIndexChanged(int index)
{
    if(index == 0){
        speech.setLocale(QLocale(QLocale::Spanish));
    }
    if(index == 1){
        speech.setLocale(QLocale(QLocale::Italian));
    }
    if(index == 2){
        speech.setLocale(QLocale(QLocale::English));
    }
    if(index == 3){
        speech.setLocale(QLocale(QLocale::German));
    }
    setup_voicesList();
}

void MainWindow::setup_voicesList(){
    voices.clear();
    ui->voiceSelection->clear();
    voices = speech.availableVoices();
    for (QVoice &voice : voices){
        ui->voiceSelection->addItem(voice.name());
    }
}

void MainWindow::setTestMode(bool enabled){
    qDebug() << "Test Started";
    if (enabled) {
        ui->textToRead->setPlainText("El geranio rojo es una flor vibrante y resistente que ha ganado popularidad en jardines y balcones por su color intenso y facilidad de cultivo. "
                                     "Su tonalidad roja simboliza la pasión y la energía, transmitiendo calidez en cualquier entorno donde se encuentre. "
                                     "Además de su belleza, el geranio es valorado por sus propiedades repelentes de insectos y su uso en aceites esenciales y productos naturales. "
                                     "Su presencia aporta alegría visual y un toque de vitalidad, convirtiéndolo en una opción ideal tanto para espacios ornamentales como funcionales.");
        QTimer::singleShot(1000, this, SLOT(on_playButton_clicked()));
        QTimer::singleShot(2000, this, [this]() {
            QString stateStr = "Speaker State: ";
            switch (speech.state()) {
                case QTextToSpeech::Ready:
                    stateStr += "Ready";
                    break;
                case QTextToSpeech::Speaking:
                    stateStr += "Speaking";
                    break;
                case QTextToSpeech::Paused:
                    stateStr += "Paused";
                    break;
                default:
                    stateStr += "Unknown";
                    break;
                }
            qDebug() << stateStr;
        });
        QTimer::singleShot(3000,this,[this](){qDebug() << "Test Finished";});
    }

}
