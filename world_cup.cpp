#include "world_cup.h"
#include "ui_world_cup.h"
#include<QFile>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include<QRandomGenerator>
#include<algorithm>
#include<QTimer>
#include<QTime>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSqlQuery>
#include <QSqlError>
#include <QMovie>
#include <QShortcut>
bool time_bool_mondiale =false ;
world_cup::world_cup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::world_cup)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    QShortcut *spaceShortcut = new QShortcut(Qt::Key_Space, this);
    spaceShortcut->setAutoRepeat(false);
    connect(spaceShortcut, &QShortcut::activated, this, [this]() {
        if(check_reveal && ui->pushButton_reveal->isEnabled() && revealStarted)
        {
            on_pushButton_reveal_clicked();
        }
    });
    ui->hiding->hide();
    ui->pushButton_next->hide();
    ui->pushButton_next->setEnabled(false);
    timecount = 15;
    time_left = 15;
    score=0;
    qi=0;
    check_5050=true;
    timer = new QTimer(this);
    ui->pushButton_8->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_next->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_option1->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_option2->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_option3->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_option4->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_suppr->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_reveal->setFocusPolicy(Qt::NoFocus);
    connect(timer, &QTimer::timeout,this, &world_cup::timefonction);
    timer->start(1000);
}

world_cup::~world_cup()
{
    delete ui;
}

void world_cup::on_pushButton_8_clicked()
{
    check_5050=true;
    ui->pushButton_suppr->setEnabled(true);
    timer->stop();
    close();
    emit backToMain();
    qi=0;
    timecount=15;
    score=0;
}

void world_cup::loadQuestionsFromJson()
{
    QFile file;
    QString base = QCoreApplication::applicationDirPath() + "/";
    if(gamemode==1){
        if(lang=="Eng"){
            file.setFileName(base +"Json/question_mondial/questions_mondial_progressive.json");
        }else{
            file.setFileName(base +"Json/question_mondial/questions_mondial_progressive_arab.json");
        }
    }else{
        if(lang=="Eng"){
            file.setFileName(base+"Json/question_mondial/questions_mondial.json");
        }else{
            file.setFileName(base+"Json/question_mondial/questions_mondial_arab.json");
        }
    }

    /*
    if(!file.open(QIODevice::ReadOnly))
        return;

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    for(auto value : array)
    {
        QJsonObject obj = value.toObject();

        Question_mondiale q;
        q.imagepath = obj["image"].toString();
        q.questiontext = obj["question"].toString();
        q.correctanswer = obj["correct"].toString();

        QJsonArray optionsArray = obj["options"].toArray();
        for(auto opt : optionsArray)
            q.options.append(opt.toString());

        questions.append(q);
    }
    std::shuffle(questions.begin(), questions.end(), *QRandomGenerator::global());*/
    if(!file.open(QIODevice::ReadOnly)) return;

    QByteArray data = file.readAll();
    QJsonArray array = QJsonDocument::fromJson(data).array();

    questions.clear();

    if(gamemode == 1) {

        QList<Question_mondiale> easy, medium, hard, extreme;

        // Step A: Read JSON and put questions into 4 separate "boxes"
        for(auto value : array) {
            QJsonObject obj = value.toObject();
            Question_mondiale q;
            q.imagepath = obj["image"].toString();
            q.questiontext = obj["question"].toString();
            q.correctanswer = obj["correct"].toString();
            q.difficulty = obj["difficulty"].toInt(); // Must be 1, 2, 3, or 4

            QJsonArray optionsArray = obj["options"].toArray();
            for(auto opt : optionsArray) q.options.append(opt.toString());

            // Sort into boxes based on difficulty
            if(q.difficulty == 1) easy.append(q);
            else if(q.difficulty == 2) medium.append(q);
            else if(q.difficulty == 3) hard.append(q);
            else extreme.append(q);
        }

        // Step B: Shuffle each box so it's random every time you play
        auto* rng = QRandomGenerator::global();
        std::shuffle(easy.begin(), easy.end(), *rng);
        std::shuffle(medium.begin(), medium.end(), *rng);
        std::shuffle(hard.begin(), hard.end(), *rng);
        std::shuffle(extreme.begin(), extreme.end(), *rng);

        // Step C: Take exactly 5 from each box and put them in the final list
        for(int i = 0; i < 5 && i < easy.size(); i++)
            questions.append(easy[i]);

        for(int i = 0; i < 5 && i < medium.size(); i++)
            questions.append(medium[i]);

        for(int i = 0; i < 5 && i < hard.size(); i++)
            questions.append(hard[i]);

        for(int i = 0; i < 5 && i < extreme.size(); i++)
            questions.append(extreme[i]);

        nombrequestions = 20; // Force the game to stop at 20

    } else {
        // ==========================================
        // NORMAL QUICK PLAY (RANDOM)
        // ==========================================
        for(auto value : array) {
            QJsonObject obj = value.toObject();
            Question_mondiale q;
            q.imagepath = obj["image"].toString();
            q.questiontext = obj["question"].toString();
            q.correctanswer = obj["correct"].toString();

            QJsonArray optionsArray = obj["options"].toArray();
            for(auto opt : optionsArray) q.options.append(opt.toString());

            questions.append(q);
        }
        // Shuffle all of them randomly
        std::shuffle(questions.begin(), questions.end(), *QRandomGenerator::global());
    }
}

void world_cup::loadQuestion()
{
    if(qi > questions.size())
        return;

    time_bool_mondiale=true;
    timefonction();
    Question_mondiale q = questions[qi];
    ui->label_question->setText(q.questiontext);
    if (ui->label_flag->movie()) {
        ui->label_flag->movie()->stop();
        ui->label_flag->movie()->deleteLater();
        ui->label_flag->setMovie(nullptr);
    }


    if (q.imagepath.endsWith(".gif", Qt::CaseInsensitive)) {

        QMovie *movie = new QMovie(q.imagepath, QByteArray(), this);


        movie->setScaledSize(ui->label_flag->size());


        ui->label_flag->setMovie(movie);
        movie->start();
    }else{
        QPixmap pixmap(q.imagepath);
        QPixmap resize = pixmap.scaled(ui->label_flag->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);

        ui->label_flag->setPixmap(QPixmap(resize));
    }



    ui->pushButton_option1->setText(q.options[0]);
    ui->pushButton_option2->setText(q.options[1]);
    ui->pushButton_option3->setText(q.options[2]);
    ui->pushButton_option4->setText(q.options[3]);


}
void world_cup::on_pushButton_option1_clicked()
{
    checkanswer(ui->pushButton_option1);
}


void world_cup::on_pushButton_option2_clicked()
{
    checkanswer(ui->pushButton_option2);
}


void world_cup::on_pushButton_option3_clicked()
{
    checkanswer(ui->pushButton_option3);
}


void world_cup::on_pushButton_option4_clicked()
{
    checkanswer(ui->pushButton_option4);
}
void world_cup::checkanswer(QPushButton *button)
{
    QString correct = questions[qi].correctanswer ;
    if(button->text()==correct){
        if(soundes){
            clicks.setSource(QUrl::fromLocalFile("soundes/correct.wav"));
            clicks.setVolume(0.1);
            clicks.play();
        }
        if(check_reveal==false){
            if(ui->pushButton_reveal->isEnabled() == false){
                ui->pushButton_reveal->setStyleSheet("#pushButton_reveal{image: url(img/icon/ic/mondial_icon/button/show_red.png)0 0 0 0 scretch  scretch; border-radius:18px;}");
                ui->pushButton_reveal->setEnabled(false);
            }
        }

        button->setStyleSheet("border-image: url(img/icon/ic/mondial_icon/button/backgr_button_correct.png) 0 0 0 0 scretch scretch;font: 900 12.5pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px; min-width: 20px;min-height: 20px;");
        ui->pushButton_option1->setEnabled(false);
        ui->pushButton_option2->setEnabled(false);
        ui->pushButton_option3->setEnabled(false);
        ui->pushButton_option4->setEnabled(false);
        if(gamemode==1){
            if(qi<5){
                score+=5;
            }else if(qi<10){
                score+=15;
            }else if(qi<15){
                score+=30;
            }else if(qi<=18){
                score+=50;
            }else{
                score+=100;
            }
        }else{
            score+=1;
        }
        if(lang=="Eng"){
            ui->label_point->setText("   Point : "+QString::number(score));
        }else{
            ui->label_point->setText("      النقاط : "+QString::number(score));
        }
        if(check_5050){
            if(ui->pushButton_suppr->isEnabled()){
                ui->pushButton_suppr->setEnabled(false);
            }
        }
        timer->stop();
    }else{
        button->setStyleSheet("border-image: url(img/icon/ic/mondial_icon/button/backgr_button_wrong.png) 0 0 0 0 scretch scretch;font: 900 12.5pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;");
        if(soundes){
            clicks.setSource(QUrl::fromLocalFile("soundes/wrong.wav"));
            clicks.setVolume(0.1);
            clicks.play();
        }

        ui->pushButton_option1->setEnabled(false);
        ui->pushButton_option2->setEnabled(false);
        ui->pushButton_option3->setEnabled(false);
        ui->pushButton_option4->setEnabled(false);
        timer->stop();//time
        if(correct==ui->pushButton_option1->text()){
            ui->pushButton_option1->setStyleSheet("border-image: url(img/icon/ic/mondial_icon/button/backgr_button_correct.png) 0 0 0 0 scretch scretch;font: 900 12.5pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");
        }
        else if(correct==ui->pushButton_option2->text()){
            ui->pushButton_option2->setStyleSheet("border-image: url(img/icon/ic/mondial_icon/button/backgr_button_correct.png) 0 0 0 0 scretch scretch;font: 900 12.5pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");
        }else if(correct==ui->pushButton_option3->text()){
            ui->pushButton_option3->setStyleSheet("border-image: url(img/icon/ic/mondial_icon/button/backgr_button_correct.png) 0 0 0 0 scretch scretch;font: 900 12.5pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");
        }else{
            ui->pushButton_option4->setStyleSheet("border-image: url(img/icon/ic/mondial_icon/button/backgr_button_correct.png) 0 0 0 0 scretch scretch;font: 900 12.5pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");
        }
        if(gamemode==1){
            qi=100000;
        }
    }
    ui->pushButton_next->show();
    ui->pushButton_next->setEnabled(true);
}

void world_cup::on_pushButton_next_clicked()
{
    qi+=1;
    if(lang=="Eng"){
        ui->label_question_number->setText(" Question "+QString::number(qi+1)+" :");
    }else{
        ui->label_question_number->setText("    السؤال"+QString::number(qi+1)+" :");
    }
    click_timer.stop();
    timecount = time_left;
    timer->start(1000);
    if(qi>=nombrequestions){
        updateScoreInDatabase(score);
        scoring_result(score);
        ui->stackedWidget->setCurrentIndex(1);
        timer->stop();
        return ;
    }
    loadQuestion();
    ui->pushButton_next->setEnabled(false);
    ui->pushButton_next->hide();
    ui->pushButton_option1->setStyleSheet("#pushButton_option1{font: 900 12.5pt Segoe UI;border-image: url(img/icon/ic/mondial_icon/button/backgr_button.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}#pushButton_option1:hover{border-image: url(img/icon/ic/mondial_icon/button/backgr_button_hover.png) 0 0 0 0 scretch scretch;}");
    ui->pushButton_option2->setStyleSheet("#pushButton_option2{font: 900 12.5pt Segoe UI;border-image: url(img/icon/ic/mondial_icon/button/backgr_button.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}#pushButton_option2:hover{border-image: url(img/icon/ic/mondial_icon/button/backgr_button_hover.png) 0 0 0 0 scretch scretch;}");
    ui->pushButton_option3->setStyleSheet("#pushButton_option3{font: 900 12.5pt Segoe UI;border-image: url(img/icon/ic/mondial_icon/button/backgr_button.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}#pushButton_option3:hover{border-image: url(img/icon/ic/mondial_icon/button/backgr_button_hover.png) 0 0 0 0 scretch scretch;}");
    ui->pushButton_option4->setStyleSheet("#pushButton_option4{font: 900 12.5pt Segoe UI;border-image: url(img/icon/ic/mondial_icon/button/backgr_button.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}#pushButton_option4:hover{border-image: url(img/icon/ic/mondial_icon/button/backgr_button_hover.png) 0 0 0 0 scretch scretch;}");

    ui->pushButton_option1->setEnabled(true);ui->pushButton_option2->setEnabled(true);
    ui->pushButton_option3->setEnabled(true);ui->pushButton_option4->setEnabled(true);
    if(check_5050){
        if(ui->pushButton_suppr->isEnabled() == false){
            ui->pushButton_suppr->setEnabled(true);
        }
    }
    if(check_time){
        ui->pushButton_time->setEnabled(true);
    }
    if(check_reveal==false||isclicked_reveal==false){
        ui->pushButton_reveal->setStyleSheet("#pushButton_reveal{image: url(img/icon/ic/mondial_icon/button/show_red.png)0 0 0 0 scretch  scretch; border-radius:18px;}");
        revealClickCount = 0;
        ui->pushButton_reveal->setEnabled(false);
        ui->hiding->hide();
    }
    if(isclicked_reveal==true){
        ui->pushButton_reveal->setEnabled(true);
    }
}

void world_cup::scoring_result(int score)
{
    QString base = QCoreApplication::applicationDirPath() + "/";
    float pourcentage = (float(score)/nombrequestions*1.00)*100;
  if(gamemode==0){
    if(pourcentage<20){
        if(lang=="Eng"){
            ui->label_score_food->setText("Relegated!");
            QPixmap map(base+"img/icon/scoring/scoring_mondial/too_bad.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));

            ui->label_scoring->setText("Your scoring : "+QString::number(pourcentage)+"%");
        }else{
            ui->label_score_food->setText("اقصاء");
            QPixmap map(base + "img/icon/scoring/scoring_mondial/too_bad.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));
            ui->label_scoring->setText("نتيجتك : %"+QString::number(pourcentage));
        }


    }else if(pourcentage>=20&&pourcentage<30){
        if(lang=="Eng"){
            ui->label_score_food->setText("Group Stage Exit");
            QPixmap map(base+"img/icon/scoring/scoring_mondial/poor.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));

            ui->label_scoring->setText("Your scoring : "+QString::number(pourcentage)+"%");
        }else{
            ui->label_score_food->setText("خروج من دور المجموعات");
            QPixmap map(base + "img/icon/scoring/scoring_mondial/poor.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));
            ui->label_scoring->setText("نتيجتك : %"+QString::number(pourcentage));
        }


    }else if(pourcentage>=30&&pourcentage<40){
        if(lang=="Eng"){
            ui->label_score_food->setText("Need More Training");
            QPixmap map(base+"img/icon/scoring/scoring_mondial/improvment.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));

            ui->label_scoring->setText("Your scoring : "+QString::number(pourcentage)+"%");
        }else{
            ui->label_score_food->setText("تحتاج لمزيد من التدريب");
            QPixmap map(base + "img/icon/scoring/scoring_mondial/improvment.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));
            ui->label_scoring->setText("نتيجتك : %"+QString::number(pourcentage));
        }

    }else if(pourcentage>=40&&pourcentage<50){
        if(lang=="Eng"){
            ui->label_score_food->setText("Mid-Table Performance");
            QPixmap map(base+"img/icon/scoring/scoring_mondial/notbad.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));
            ui->label_scoring->setText("Your scoring : "+QString::number(pourcentage)+"%");
        }else{
            ui->label_score_food->setText("أداء متوسط");
            QPixmap map(base + "img/icon/scoring/scoring_mondial/notbad.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));
            ui->label_scoring->setText("نتيجتك : %"+QString::number(pourcentage));
        }

    }else if(pourcentage>=50&&pourcentage<60){
        if(lang=="Eng"){
            ui->label_score_food->setText("Average Squad Player");
            QPixmap map(base+"img/icon/scoring/scoring_mondial/average.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));

            ui->label_scoring->setText("Your scoring : "+QString::number(pourcentage)+"%");
        }else{
            ui->label_score_food->setText("لاعب احتياطي جيد");
            QPixmap map(base + "img/icon/scoring/scoring_mondial/average.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));
            ui->label_scoring->setText("نتيجتك : %"+QString::number(pourcentage));

        }

    }else if(pourcentage>=60&&pourcentage<70){
        if(lang=="Eng"){
            ui->label_score_food->setText("Solid Defender");
            QPixmap map(base+"img/icon/scoring/scoring_mondial/notbad.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));

            ui->label_scoring->setText("Your scoring : "+QString::number(pourcentage)+"%");
        }else{
            ui->label_score_food->setText("مدافع صلب");
            QPixmap map(base+"img/icon/scoring/scoring_mondial/notbad.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));
            ui->label_scoring->setText("نتيجتك : %"+QString::number(pourcentage));
        }

    }else if(pourcentage>=70&&pourcentage<80){
        if(lang=="Eng"){
            ui->label_score_food->setText("Star Striker");
            QPixmap map(base+"img/icon/scoring/scoring_mondial/very_good.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));

            ui->label_scoring->setText("Your scoring : "+QString::number(pourcentage)+"%");
        }else{
            ui->label_score_food->setText("مهاجم نجم");
            QPixmap map(base + "img/icon/scoring/scoring_mondial/very_good.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));
            ui->label_scoring->setText("نتيجتك : %"+QString::number(pourcentage));
        }

    }else if(pourcentage>=80&&pourcentage<90){
        if(lang=="Eng"){
            ui->label_score_food->setText("Golden Boot Race");
            QPixmap map("img/icon/scoring/scoring_mondial/to_close.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));

            ui->label_scoring->setText("Your scoring : "+QString::number(pourcentage)+"%");
        }else{
            ui->label_score_food->setText("منافس على الحذاء الذهبي");
            QPixmap map(base + "img/icon/scoring/scoring_mondial/to_close.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));
            ui->label_scoring->setText("نتيجتك : %"+QString::number(pourcentage));
        }

    }else if(pourcentage>=90&&pourcentage<100){
        if(lang=="Eng"){
            ui->label_score_food->setText("World Class Player!");
            QPixmap map(base+"img/icon/scoring/scoring_mondial/very_good.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));

            ui->label_scoring->setText("Your scoring : "+QString::number(pourcentage)+"%");
        }else{
            ui->label_score_food->setText("لاعب عالمي!");
            QPixmap map(base + "img/icon/scoring/scoring_mondial/very_good.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));
            ui->label_scoring->setText("نتيجتك : %"+QString::number(pourcentage));
        }

    }else{
        if(lang=="Eng"){
            ui->label_score_food->setText("World Cup Champion!");
            QPixmap map(base+"img/icon/scoring/scoring_mondial/practice.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));

            ui->label_scoring->setText("Your scoring : "+QString::number(pourcentage)+"%");
        }else{
            ui->label_score_food->setText("بطل كأس العالم!");
            QPixmap map(base + "img/icon/scoring/scoring_mondial/practice.png");
            QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->label_image_score->setPixmap(QPixmap(resize));
            ui->label_scoring->setText("نتيجتك : %"+QString::number(pourcentage));
        }

    }}else{
        if(score<=25){
            if(lang=="Eng"){
                ui->label_score_food->setText("Group Stage Exit!");
                QPixmap map(base +"img/icon/scoring/scoring_mondial/scoring_mondial_chalenge/Group_Stage_Exit.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));

                ui->label_scoring->setText(tr("Your score : ")+QString::number(score));
            }else{
                ui->label_score_food->setText("خروج من دور المجموعات!");
                QPixmap map(base +"img/icon/scoring/scoring_mondial/scoring_mondial_chalenge/Group_Stage_Exit.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(resize);

                ui->label_scoring->setText("نتيجتك : "+QString::number(score));
            }
        }else if(score<=100){
            if(lang=="Eng"){
                ui->label_score_food->setText("Solid Run!");
                QPixmap map(base +"img/icon/scoring/scoring_mondial/scoring_mondial_chalenge/Solid_Run.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));

                ui->label_scoring->setText(tr("Your scoring : ")+QString::number(score));
            }else{
                ui->label_score_food->setText("أداء جيد!");
                QPixmap map(base +"img/icon/scoring/scoring_mondial/scoring_mondial_chalenge/Solid_Run.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(resize);

                ui->label_scoring->setText("نتيجتك : "+QString::number(score));
            }
        }else if(score<=250){
            if(lang=="Eng"){
                ui->label_score_food->setText("Quarter-Finalist!");
                QPixmap map(base +"img/icon/scoring/scoring_mondial/scoring_mondial_chalenge/Quarter_Finalist.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));

                ui->label_scoring->setText(tr("Your scoring : ")+QString::number(score));
            }else{
                ui->label_score_food->setText("وصلت لربع النهائي!");
                QPixmap map(base +"img/icon/scoring/scoring_mondial/scoring_mondial_chalenge/Quarter_Finalist.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(resize);

                ui->label_scoring->setText("نتيجتك : "+QString::number(score));
            }
        }else if(score<500){
            if(lang=="Eng"){
                ui->label_score_food->setText("Almost a Champion!");
                QPixmap map(base +"img/icon/scoring/scoring_mondial/scoring_mondial_chalenge/Almost_a_Champion.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));

                ui->label_scoring->setText(tr("Your scoring : ")+QString::number(score));
            }else{
                ui->label_score_food->setText("قريب جداً من اللقب!");
                QPixmap map(base +"img/icon/scoring/scoring_mondial/scoring_mondial_chalenge/Almost_a_Champion.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(resize);

                ui->label_scoring->setText("نتيجتك : "+QString::number(score));
            }
        }else{
            if(lang=="Eng"){
                ui->label_score_food->setText("World Champion!");
                QPixmap map(base +"img/icon/scoring/scoring_mondial/scoring_mondial_chalenge/World_Champion.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText(tr("Your scoring : ")+QString::number(score));

                //QMediaPlayer *player = new QMediaPlayer;
                //QAudioOutput *audioOutput = new QAudioOutput;

                //player->setAudioOutput(audioOutput);
                player->setSource(QUrl::fromLocalFile(base+"soundes/world_champion.mp3"));
                audioOutput->setVolume(0.5);
                player->play();
            }else{
                ui->label_score_food->setText("بطل العالم!");
                 QPixmap map(base +"img/icon/scoring/scoring_mondial/scoring_mondial_chalenge/World_Champion.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(resize);
                //QMediaPlayer *player = new QMediaPlayer;
                //QAudioOutput *audioOutput = new QAudioOutput;

                ui->label_scoring->setText("نتيجتك : "+QString::number(score));
                //player->setAudioOutput(audioOutput);
                player->setSource(QUrl::fromLocalFile(base+"soundes/world_champion.mp3"));
                audioOutput->setVolume(0.5);
                player->play();
            }
        }
    }
}



void world_cup::on_pushButton_play_again_clicked()
{
    close();
    timer->stop();
    if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->stop();
    }
    emit backToMain();
    qi=0;
    score=0;
}

void world_cup::setLevel(int value,int t)
{
    nombrequestions=value;
    timecount = t;
    time_left = t;
}

void world_cup::setlang(QString langag)
{
    lang = langag;
    loadQuestionsFromJson();
    if(lang=="Eng"){
        ui->label_point->setText("   Point : "+QString::number(score));
    }else{
        ui->label_point->setText("      النقاط : "+QString::number(score));
    }
    if(lang=="Eng"){
        ui->label_question_number->setText(" Question "+QString::number(qi+1)+" :");
    }else{
        ui->label_question_number->setText("    السؤال"+QString::number(qi+1)+" :");
    }
    time_bool_mondiale=true;
    loadQuestion();

    timefonction();

}
//time fonction
void world_cup::timefonction(){
    if(timecount>=0){
        ui->label_time->setText(QString::number(timecount));

        if(timecount==0){
            click_timer.setSource(QUrl::fromLocalFile(
                QCoreApplication::applicationDirPath() + "/soundes/Timer_end.wav"));
            click_timer.setVolume(0.2);
            click_timer.play();

            QTimer::singleShot(3000, this, [this]() {
                click_timer.stop();
            });
            if(isclicked_reveal==false){
                ui->pushButton_reveal->setStyleSheet("#pushButton_reveal{image: url(img/icon/ic/mondial_icon/button/show_red.png)0 0 0 0 scretch  scretch; border-radius:18px;}");
                revealClickCount = 0;
                ui->pushButton_reveal->setEnabled(false);
                ui->hiding->hide();
            }
            ui->pushButton_time->setEnabled(false);
            ui->pushButton_reveal->setEnabled(false);
            ui->pushButton_suppr->setEnabled(false);
        }
        timecount--;
    }
    else{
        int i=0;
        timer->stop();
        ui->label_time->setText("Time over");
        QString correct = questions[qi].correctanswer ;

        /*click_timer.setSource(QUrl("soundes/Timer_end.wav"));
         click_timer.setVolume(0.2);
         click_timer.play();

             QTimer::singleShot(3000, this, [this]() {
                     click_timer.stop();
             });*/



        ui->pushButton_next->show();
        ui->pushButton_next->setEnabled(true);


        if(correct==ui->pushButton_option1->text()){
            ui->pushButton_option1->setStyleSheet("border-image: url(img/icon/ic/mondial_icon/button/backgr_button_correct.png) 0 0 0 0 scretch scretch;font: 900 15pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");

        }
        else if(correct==ui->pushButton_option2->text()){
            ui->pushButton_option2->setStyleSheet("border-image: url(img/icon/ic/mondial_icon/button/backgr_button_correct.png) 0 0 0 0 scretch scretch;font: 900 15pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");
        }else if(correct==ui->pushButton_option3->text()){
            ui->pushButton_option3->setStyleSheet("border-image: url(img/icon/ic/mondial_icon/button/backgr_button_correct.png) 0 0 0 0 scretch scretch;font: 900 15pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");
        }else{
            ui->pushButton_option4->setStyleSheet("border-image: url(img/icon/ic/mondial_icon/button/backgr_button_correct.png) 0 0 0 0 scretch scretch;font: 900 15pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");
        }
        ui->pushButton_option1->setEnabled(false);
        ui->pushButton_option2->setEnabled(false);
        ui->pushButton_option3->setEnabled(false);
        ui->pushButton_option4->setEnabled(false);
        if(gamemode==1){
            qi=100000;
        }
    }

}
void world_cup::game(int challenge){
    gamemode = challenge;
}

//database score
void world_cup::setCurrentUser(const QString &user)
{
    currentUser = user;
}
void world_cup::updateScoreInDatabase(int score)
{
    qDebug() << "Current user:" << currentUser;
    qDebug() << "Score to add:" << score;
    if(currentUser.isEmpty())
        return;
    if(currentUser.isEmpty())
        return;

    QSqlQuery query;
    query.prepare("UPDATE users SET score = score + :score WHERE name = :name");
    query.bindValue(":score", score);
    query.bindValue(":name", currentUser);

    if(!query.exec()){
        qDebug() << "Score update failed:" << query.lastError();
    }else{
        QSettings settings("MyApp", "LoginApp");
        int currentScore = settings.value("currentScore", 0).toInt();
        currentScore += score;
        settings.setValue("currentScore", currentScore);
    }
}

void world_cup::on_pushButton_suppr_clicked()
{
    QString correct = questions[qi].correctanswer;

    if(check_5050){
        if(correct!=ui->pushButton_option1->text()&&correct!=ui->pushButton_option2->text()){ui->pushButton_option1->setText("");ui->pushButton_option2->setText("");ui->pushButton_option1->setEnabled(false);ui->pushButton_option2->setEnabled(false);}
        else if(correct!=ui->pushButton_option1->text()&&correct!=ui->pushButton_option3->text()){ui->pushButton_option1->setText("");ui->pushButton_option3->setText("");ui->pushButton_option1->setEnabled(false);ui->pushButton_option3->setEnabled(false);}
        else if(correct!=ui->pushButton_option1->text()&&correct!=ui->pushButton_option4->text()){ui->pushButton_option1->setText("");ui->pushButton_option4->setText("");ui->pushButton_option1->setEnabled(false);ui->pushButton_option4->setEnabled(false);}
        else if(correct!=ui->pushButton_option2->text()&&correct!=ui->pushButton_option1->text()){ui->pushButton_option2->setText("");ui->pushButton_option1->setText("");ui->pushButton_option2->setEnabled(false);ui->pushButton_option1->setEnabled(false);}
        else if(correct!=ui->pushButton_option2->text()&&correct!=ui->pushButton_option3->text()){ui->pushButton_option2->setText("");ui->pushButton_option3->setText("");ui->pushButton_option2->setEnabled(false);ui->pushButton_option3->setEnabled(false);}
        else if(correct!=ui->pushButton_option2->text()&&correct!=ui->pushButton_option4->text()){ui->pushButton_option2->setText("");ui->pushButton_option4->setText("");ui->pushButton_option2->setEnabled(false);ui->pushButton_option4->setEnabled(false);}
        else if(correct!=ui->pushButton_option3->text()&&correct!=ui->pushButton_option1->text()){ui->pushButton_option3->setText("");ui->pushButton_option1->setText("");ui->pushButton_option3->setEnabled(false);ui->pushButton_option1->setEnabled(false);}
        else if(correct!=ui->pushButton_option3->text()&&correct!=ui->pushButton_option2->text()){ui->pushButton_option3->setText("");ui->pushButton_option2->setText("");ui->pushButton_option3->setEnabled(false);ui->pushButton_option2->setEnabled(false);}
        else if(correct!=ui->pushButton_option3->text()&&correct!=ui->pushButton_option4->text()){ui->pushButton_option3->setText("");ui->pushButton_option4->setText("");ui->pushButton_option3->setEnabled(false);ui->pushButton_option4->setEnabled(false);}
        else if(correct!=ui->pushButton_option4->text()&&correct!=ui->pushButton_option1->text()){ui->pushButton_option4->setText("");ui->pushButton_option1->setText("");ui->pushButton_option4->setEnabled(false);ui->pushButton_option1->setEnabled(false);}
        else if(correct!=ui->pushButton_option4->text()&&correct!=ui->pushButton_option2->text()){ui->pushButton_option4->setText("");ui->pushButton_option2->setText("");ui->pushButton_option4->setEnabled(false);ui->pushButton_option2->setEnabled(false);}
        else if(correct!=ui->pushButton_option4->text()&&correct!=ui->pushButton_option3->text()){ui->pushButton_option4->setText("");ui->pushButton_option3->setText("");ui->pushButton_option4->setEnabled(false);ui->pushButton_option3->setEnabled(false);}
    }
    check_5050=false;
    ui->pushButton_suppr->setEnabled(false);
    ui->pushButton_suppr->setStyleSheet("#pushButton_suppr{ image: url(img/icon/ic/mondial_icon/button/5050_rouge.png)0 0 0 0 scretch  scretch;border-radius:18px;}");
}

void world_cup::setsoundes(bool b){
    soundes = b;
}

void world_cup::on_pushButton_reveal_clicked()
{
    ui->pushButton_reveal->setFocusPolicy(Qt::StrongFocus);
    ui->pushButton_suppr->setEnabled(false);
    ui->pushButton_time->setEnabled(false);
    isclicked_reveal=false;
    ui->hiding->show();
    if(lang=="Eng"){
        ui->hiding->setText("Keep pressing space or keep pressing the reveal icon");
    }else{
        ui->hiding->setText("واصل الضغط على مفتاح المسافة أو استمر في النقر على أيقونة الكشف");
    }
    if(!check_reveal) return;
    revealStarted = true;
    ui->pushButton_suppr->setEnabled(false);
    revealClickCount++;
    int pct = (revealClickCount * 100) / REVEAL_CLICKS_NEEDED;


    ui->pushButton_reveal->setStyleSheet(QString(
                                             "font: bold 11pt 'Segoe UI';"
                                             "color: rgb(0,0,0);"
                                             "border-radius: 18px;"
                                             "min-width: 80px; min-height: 40px;"
                                             "background: qlineargradient("
                                             "  x1:0, y1:0, x2:1, y2:0,"
                                             "  stop:0 rgba(255,165,0,220),"
                                             "  stop:%1 rgba(255,165,0,220),"
                                             "  stop:%2 rgba(200,200,200,100),"
                                             "  stop:1 rgba(200,200,200,100)"
                                             ");"
                                             "border: 2px solid orange;"
                                             ).arg(pct / 100.0, 0, 'f', 3)
                                             .arg(qMin(pct / 100.0 + 0.001, 1.0), 0, 'f', 3));


    ui->pushButton_reveal->setText(
        QString("%1 / %2").arg(revealClickCount).arg(REVEAL_CLICKS_NEEDED)
        );
    if(timecount<=0){
        check_reveal = false;
    }
    if(revealClickCount >= REVEAL_CLICKS_NEEDED)
    {
        check_reveal = false;
        revealClickCount = 0;
        ui->pushButton_reveal->setEnabled(false);

        // Highlight the correct answer in green
        QString correct = questions[qi].correctanswer;

        if(correct == ui->pushButton_option1->text())
            ui->pushButton_option1->setStyleSheet( "#pushButton_option1{font: 900 15pt Segoe UI;border-image: url(img/icon/ic/mondial_icon/button/backgr_button_hover.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}");
        else if(correct == ui->pushButton_option2->text())
            ui->pushButton_option2->setStyleSheet( "#pushButton_option2{font: 900 15pt Segoe UI;border-image: url(img/icon/ic/mondial_icon/button/backgr_button_hover.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}");
        else if(correct == ui->pushButton_option3->text())
            ui->pushButton_option3->setStyleSheet( "#pushButton_option3{font: 900 15pt Segoe UI;border-image: url(img/icon/ic/mondial_icon/button/backgr_button_hover.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}");
        else
            ui->pushButton_option4->setStyleSheet( "#pushButton_option4{font: 900 15pt Segoe UI;border-image: url(img/icon/ic/mondial_icon/button/backgr_button_hover.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}");

        ui->hiding->hide();
        ui->pushButton_reveal->setStyleSheet("#pushButton_reveal{image: url(img/icon/ic/mondial_icon/button/show_red.png)0 0 0 0 scretch  scretch; border-radius:18px;}");
        ui->pushButton_suppr->setEnabled(true);
    }
}

void world_cup::on_pushButton_time_clicked()
{
    timecount=timecount+15;
    ui->pushButton_time->setEnabled(false);
    check_time=false;
    ui->pushButton_time->setStyleSheet("#pushButton_time{image: url(img/icon/ic/mondial_icon/button/time_red.png)0 0 0 0 scretch  scretch; border-radius:18px;}");
}

