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

    QString stateStr;
    switch (speech.state()) {
    case QTextToSpeech::Ready:
        stateStr = "Ready";
        break;
    case QTextToSpeech::Speaking:
        stateStr = "Speaking";
        break;
    case QTextToSpeech::Paused:
        stateStr = "Paused";
        break;
    default:
        stateStr = "Unknown";
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
        ui->textToRead->setPlainText("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. "
                                     "Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. "
                                     "Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi. "
                                     "Proin porttitor, orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat. "
                                     "Duis semper. Duis arcu massa, scelerisque vitae, consequat in, pretium a, enim. Pellentesque congue. "
                                     "Ut in risus volutpat libero pharetra tempor. Cras vestibulum bibendum augue. "
                                     "Praesent egestas leo in pede. Praesent blandit odio eu enim. Pellentesque sed dui ut augue blandit sodales. "
                                     "Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; "
                                     "Aliquam nibh. Mauris ac mauris sed pede pellentesque fermentum. "
                                     "Maecenas adipiscing ante non diam sodales hendrerit.");
        QTimer::singleShot(1000, this, SLOT(on_playButton_clicked()));
        QTimer::singleShot(2000, this, [this]() {
            QString stateStr;
            switch (speech.state()) {
                case QTextToSpeech::Ready:
                    stateStr = "Ready";
                    break;
                case QTextToSpeech::Speaking:
                    stateStr = "Speaking";
                    break;
                case QTextToSpeech::Paused:
                    stateStr = "Paused";
                    break;
                default:
                    stateStr = "Unknown";
                    break;
                }
            qDebug() << stateStr;
        });
        QTimer::singleShot(3000,this,[this](){qDebug() << "Test Finished";});
    }

}
