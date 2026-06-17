#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"first_game.h"
#include<QSoundEffect>
#include"food_game.h"
#include "world_cup.h"
#include <QTranslator>
#include "picture_world.h"
#include "picture_m.h"
#include <QtSql>
#include <QMediaPlayer>
#include <QAudioOutput>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
struct Sound{
    QString source;
};
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//private slots:

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_about_clicked();

    void on_pushButton_Exit_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_option_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_start_2_clicked();

    void on_pushButton_start_3_clicked();

    void on_pushButton_start_long_play_clicked();

    void on_pushButton_start_long_play_2_clicked();

    void on_pushButton_start_4_clicked();
    void on_pushButton_start_food_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_start_food_quick_game_clicked();

    void on_pushButton_start_food_long_play_3_clicked();

    void on_pushButton_start_food_long_play_4_clicked();

    void on_pushButton_start_mondial_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_start_cup_quick_game_clicked();

    void on_pushButton_start_cup_long_play_clicked();

    void on_pushButton_start_cup_long_play_7_clicked();

    void on_pushButton_start_id_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_start_picureid_world_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_start_picureid_morocco_clicked();

    void on_pushButton_start_picture_world_quick_game_clicked();

    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);

    void loadQuestionsFromJson_audio();

    void playRandomSound();
    /*void on_pushButton_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();*/

    void on_pushButton_click();

    void on_pushButton_start_picture_custom_clicked();

    void on_pushButton_start_picture_long_play_1_clicked();

    void on_pushButton_language_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_start_picture_world_quick_game_m_clicked();

    void on_pushButton_start_picture_long_play_m_clicked();

    void on_pushButton_start_picture_custom_m_clicked();

    void change_volume(int value);


    void on_pushButton_21_clicked();

    void on_pushButton_son_clicked();

    void on_pushButton_start_challenge_clicked();

    void on_pushButton_start_cup_challenge_clicked();

    void on_pushButton_start_food_challenge_clicked();

    void on_pushButton_start_picture_challenge_clicked();

    void on_pushButton_start_picture_challenge_2_clicked();

    //base de donnes
    void on_loginButton_clicked();
    void on_createButton_clicked();

    void on_logout_clicked();

    void on_pushButton_start_5_clicked();

    void on_pushButton_23_clicked();

    void on_checkBox_checkStateChanged(const Qt::CheckState &arg1);

    void initCreditsUI();

    void on_uploadImg_clicked();

    void loadUserPhoto();

    void on_pushButton_pause_clicked();

    void on_pushButton_next_clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
private:
    Ui::MainWindow *ui;
    first_game *first ;
    food_game *second;
    world_cup *third;
    picture_world *quatro;
    picture_m *cinqo;
    QString l = "Eng";
    QSoundEffect clickSound;
    QTranslator translator;

    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QVector<Sound> sounds;
    //database
    void connectDatabase();
    void createTable();
    QSqlDatabase db;
    int currentSoundIndex=0;
    bool soundes;


};
#endif // MAINWINDOW_H
