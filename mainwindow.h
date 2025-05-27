#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtTextToSpeech>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_playButton_clicked();
    void setUpVoice(QVector<QVoice> voices, QString voiceName, QTextToSpeech &speech);

    void on_horizontalSlider_sliderPressed();

    void on_horizontalSlider_sliderReleased();

    void on_horizontalSlider_valueChanged(int value);

    void on_speech_end();

    void on_textToRead_textChanged();

    void on_stopButton_clicked();

    void on_locationsList_currentIndexChanged(int index);

    void setup_voicesList();

private:
    Ui::MainWindow *ui;
    QTextToSpeech speech;
    QVector<QVoice> voices;
    bool StopSpeech = true;
    bool PauseSpeech = false;
};
#endif // MAINWINDOW_H
