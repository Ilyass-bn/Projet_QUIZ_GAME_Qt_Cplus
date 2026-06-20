#ifndef WORLD_CUP_H
#define WORLD_CUP_H


#include <QWidget>
#include<QString>
#include<QSoundEffect>
#include<QVector>
#include<QPushButton>
#include <QMediaPlayer>
#include "aichat.h"
#include <QAudioOutput>
#include <QtSql>
namespace Ui {
class world_cup;
}
struct Question_mondiale{
    QString imagepath ;
    QString questiontext;
    QString correctanswer;
    QStringList options;
    int difficulty;
};
class world_cup : public QWidget
{
    Q_OBJECT

public:
    explicit world_cup(QWidget *parent = nullptr);
    ~world_cup();
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
    Ui::world_cup *ui;
    int score;
    QVector<Question_mondiale>questions ;
    int qi = 0 ;
    int nombrequestions;
    QString lang;
    QSoundEffect clicks ;
    QTimer *timer ;
    int timecount;
    int time_left;
    QSoundEffect click_timer;
    int gamemode;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QString currentUser;
    void updateScoreInDatabase(int score);
    bool check_5050;
    bool soundes;

    int revealClickCount = 0;
    const int REVEAL_CLICKS_NEEDED = 85;
    bool check_reveal = true;
    bool revealStarted = false;
    bool check_time=true;
    bool isclicked_reveal=true;
    bool AI_click=true;
    AIchat *ai;
};

#endif // WORLD_CUP_H
