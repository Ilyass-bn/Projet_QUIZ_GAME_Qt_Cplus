#ifndef PICTURE_M_H
#define PICTURE_M_H

#include <QWidget>
#include<QPushButton>
#include<QSoundEffect>
#include <QtSql>
#include <QMediaPlayer>
#include <QAudioOutput>
namespace Ui {
class picture_m;
}
struct Question_morocco{
    QString imagepath ;
    QString questiontext;
    QString correctanswer;
    QStringList options;
    int difficulty;
};
class picture_m : public QWidget
{
    Q_OBJECT

public:
    explicit picture_m(QWidget *parent = nullptr);
    ~picture_m();
    void setLevel(int value,int t);
    void setlangw(QString langag);
    void game(int challenge);
    void setCurrentUser(const QString &user);
    void setsoundes(bool s);
signals:
    void backToMain();
private slots:
    void on_pushButton_8_clicked();
    void loadQuestionsFromJsonw();
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

private:
    Ui::picture_m *ui;
    int score;
    QVector<Question_morocco>questions ;
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

    int revealClickCount = 0;
    const int REVEAL_CLICKS_NEEDED = 85;
    bool check_reveal = true;
    bool revealStarted = false;
    bool check_time=true;
    bool isclicked_reveal=true;
};

#endif // PICTURE_M_H
