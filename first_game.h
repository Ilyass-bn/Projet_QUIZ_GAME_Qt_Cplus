#ifndef FIRST_GAME_H
#define FIRST_GAME_H

#include <QWidget>
#include<QPushButton>
#include<QSoundEffect>
#include<QTimer>
#include<QSoundEffect>
#include<QMediaPlayer>
#include <QtSql>
#include "aichat.h"
#include <QMediaPlayer>
#include <QAudioOutput>


namespace Ui {
class first_game;
}
struct Question{
    QString imagepath ;
    QString questiontext;
    QString correctanswer;
    QStringList options;
    int difficulty;
};
class first_game : public QWidget
{
    Q_OBJECT

public:
    explicit first_game(QWidget *parent = nullptr);
    ~first_game();
    void setLevel(int value,int t);
    void setlang(QString langag);
    void game(int challenge);
    void setCurrentUser(const QString &user);
    void setsoundes(bool s);

signals:
    void backToMain();
private slots:
    void on_pushButton_8_clicked();
    void loadQuestionsFromJson();
    void loadQuestion();
    void checkanswer(QPushButton*button);

    void on_pushButton_option1_clicked();

    void on_pushButton_option2_clicked();

    void on_pushButton_option3_clicked();

    void on_pushButton_option4_clicked();

    void on_pushButton_next_clicked();

    void scoring_result(int score);

    void on_pushButton_play_again_clicked();

    void timefonction();
    void on_pushButton_suppr_clicked();
    void on_pushButton_reveal_clicked();

    void on_pushButton_time_clicked();

    void on_pushButton_AI_clicked();

private:
    Ui::first_game *ui;
    int score;
    QVector<Question>questions ;
    int qi = 0 ;
    int nombrequestions;
    QString lang;
    QSoundEffect clicks ;
    QTimer *timer ;
    int timecount;
    int time_left;
    QSoundEffect click_timer;
    int gamemode;
    QString currentUser;
    void updateScoreInDatabase(int score);
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    bool check_5050;
    bool soundes;
    AIchat *ai;
    int revealClickCount = 0;
    const int REVEAL_CLICKS_NEEDED = 85;
    bool check_reveal = true;
    bool revealStarted = false;
    bool check_time=true;
    bool isclicked_reveal=true;
    bool AI_click=true;
};




#endif // FIRST_GAME_H
