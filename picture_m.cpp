#include "picture_m.h"
#include "ui_picture_m.h"
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include<QRandomGenerator>
#include<algorithm>
#include<QTimer>
#include<QTime>
#include<QFile>
#include <QSqlQuery>
#include <QSqlError>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QShortcut>
bool time_bool_m =false ;
picture_m::picture_m(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::picture_m)
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
    connect(timer, &QTimer::timeout,this, &picture_m::timefonction);
    timer->start(1000);
}

picture_m::~picture_m()
{
    delete ui;
}

void picture_m::on_pushButton_8_clicked()
{
    check_5050=true;
    ui->pushButton_suppr->setEnabled(true);
    timer->stop();
    player->stop();
    close();
    emit backToMain();
    qi=0;
    timecount=15;
    score=0;
}

void picture_m::loadQuestionsFromJsonw()
{
    questions.clear();
    QString base = QCoreApplication::applicationDirPath() + "/";
    QFile file;
    if(gamemode==1){
        if(lang=="Eng"){
            file.setFileName(base +"Json/question_picture/question_picture_morocco/questions_picture_m.json");
        }else{
            file.setFileName(base +"Json/question_picture/question_picture_morocco/questions_picture_m_arabe.json");
        }
    }else{
        if(lang=="Eng"){
            file.setFileName(base +"Json/question_picture/question_picture_morocco/questions_picture_m_progress.json");
        }else{
            file.setFileName(base +"Json/question_picture/question_picture_morocco/questions_picture_m_arabe_progress.json");
        }
    }

    /*if(!file.open(QIODevice::ReadOnly))
        return;

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    for(auto value : array)
    {
        QJsonObject obj = value.toObject();

        Question_world q;
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

    questions.clear(); // Clear the main list

    if(gamemode == 1) {
        // ==========================================
        // LONG PLAY (PROGRESSIVE) - EXACTLY 20 Qs
        // ==========================================
        QList<Question_morocco> easy, medium, hard, extreme;

        // Step A: Read JSON and put questions into 4 separate "boxes"
        for(auto value : array) {
            QJsonObject obj = value.toObject();
            Question_morocco q;
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
            Question_morocco q;
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
void picture_m::loadQuestion()
{
    if(qi > questions.size())
        return;

    time_bool_m=true;
    timefonction();
    Question_morocco q = questions[qi];
    ui->label_question->setText(q.questiontext);
    QPixmap pixmap(q.imagepath);
    QPixmap resize = pixmap.scaled(ui->label_flag->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);

    ui->label_flag->setPixmap(QPixmap(resize));

    ui->pushButton_option1->setText(q.options[0]);
    ui->pushButton_option2->setText(q.options[1]);
    ui->pushButton_option3->setText(q.options[2]);
    ui->pushButton_option4->setText(q.options[3]);


}
void picture_m::on_pushButton_option1_clicked()
{
    checkanswer(ui->pushButton_option1);
}


void picture_m::on_pushButton_option2_clicked()
{
    checkanswer(ui->pushButton_option2);
}


void picture_m::on_pushButton_option3_clicked()
{
    checkanswer(ui->pushButton_option3);
}


void picture_m::on_pushButton_option4_clicked()
{
    checkanswer(ui->pushButton_option4);
}
void picture_m::checkanswer(QPushButton *button)
{
    QString correct = questions[qi].correctanswer ;
    if(button->text()==correct){
        //clicks.setSource(QUrl("soundes/correct.wav"));
        if(soundes){
            clicks.setSource(QUrl::fromLocalFile("soundes/correct.wav"));
            clicks.setVolume(0.1);
            clicks.play();
        }
        if(check_reveal==false){
            if(ui->pushButton_reveal->isEnabled() == false){
                ui->pushButton_reveal->setStyleSheet("#pushButton_reveal{image: url(img/icon/ic/picture_world_icon/buttons/show_red.png)0 0 0 0 scretch  scretch; border-radius:18px;}");
                ui->pushButton_reveal->setEnabled(false);
            }
        }

        button->setStyleSheet("border-image: url(img/icon/ic/picture_world_icon/buttons/button_green.png) 0 0 0 0 scretch scretch;font: 900 15pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px; min-width: 20px;min-height: 20px;");
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
        button->setStyleSheet("border-image: url(img/icon/ic/picture_world_icon/buttons/button_wrong.png) 0 0 0 0 scretch scretch;font: 900 15pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;");
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
            ui->pushButton_option1->setStyleSheet("border-image: url(img/icon/ic/picture_world_icon/buttons/button_green.png) 0 0 0 0 scretch scretch;font: 900 15pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");
        }
        else if(correct==ui->pushButton_option2->text()){
            ui->pushButton_option2->setStyleSheet("border-image: url(img/icon/ic/picture_world_icon/buttons/button_green.png) 0 0 0 0 scretch scretch;font: 900 15pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");
        }else if(correct==ui->pushButton_option3->text()){
            ui->pushButton_option3->setStyleSheet("border-image: url(img/icon/ic/picture_world_icon/buttons/button_green.png) 0 0 0 0 scretch scretch;font: 900 15pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");
        }else{
            ui->pushButton_option4->setStyleSheet("border-image: url(img/icon/ic/picture_world_icon/buttons/button_green.png) 0 0 0 0 scretch scretch;font: 900 15pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");
        }
        if(gamemode==1){
            qi=100000;
        }
    }
    ui->pushButton_next->show();
    ui->pushButton_next->setEnabled(true);
}

void picture_m::on_pushButton_next_clicked()
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
    ui->pushButton_option1->setStyleSheet("#pushButton_option1{font: 900 15pt Segoe UI;border-image: url(img/icon/ic/picture_world_icon/buttons/backgr_button.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}#pushButton_option1:hover{border-image: url(img/icon/ic/picture_world_icon/buttons/button_hover.png) 0 0 0 0 scretch scretch;}");
    ui->pushButton_option2->setStyleSheet("#pushButton_option2{font: 900 15pt Segoe UI;border-image: url(img/icon/ic/picture_world_icon/buttons/backgr_button.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}#pushButton_option2:hover{border-image: url(img/icon/ic/picture_world_icon/buttons/button_hover.png) 0 0 0 0 scretch scretch;}");
    ui->pushButton_option3->setStyleSheet("#pushButton_option3{font: 900 15pt Segoe UI;border-image: url(img/icon/ic/picture_world_icon/buttons/backgr_button.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}#pushButton_option3:hover{border-image: url(img/icon/ic/picture_world_icon/buttons/button_hover.png) 0 0 0 0 scretch scretch;}");
    ui->pushButton_option4->setStyleSheet("#pushButton_option4{font: 900 15pt Segoe UI;border-image: url(img/icon/ic/picture_world_icon/buttons/backgr_button.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}#pushButton_option4:hover{border-image: url(img/icon/ic/picture_world_icon/buttons/button_hover.png) 0 0 0 0 scretch scretch;}");

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
        ui->pushButton_reveal->setStyleSheet("#pushButton_reveal{image: url(img/icon/ic/picture_world_icon/buttons/show_red.png)0 0 0 0 scretch  scretch; border-radius:18px;}");
        revealClickCount = 0;
        ui->pushButton_reveal->setEnabled(false);
        ui->hiding->hide();
    }
    if(isclicked_reveal==true){
        ui->pushButton_reveal->setEnabled(true);
    }
}

void picture_m::scoring_result(int score)
{
    QString base = QCoreApplication::applicationDirPath() + "/";
    float pourcentage = (float(score)/nombrequestions*1.00)*100;
    if(gamemode==0){
        if(pourcentage < 20) {
            if(lang == "Eng") {
                ui->label_score_food->setText("Lost Tourist!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Lost_Tourist.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("Your scoring : " + QString::number(pourcentage) + "%");
            } else {
                ui->label_score_food->setText("سائح تائه!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Lost_Tourist.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("نتيجتك : %" + QString::number(pourcentage));
            }

        } else if(pourcentage >= 20 && pourcentage < 30) {
            if(lang == "Eng") {
                ui->label_score_food->setText("Mint Tea Beginner");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Mint_Tea_Beginner.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("Your scoring : " + QString::number(pourcentage) + "%");
            } else {
                ui->label_score_food->setText("مبتدئ في أتاي");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Mint_Tea_Beginner.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("نتيجتك : %" + QString::number(pourcentage));
            }

        } else if(pourcentage >= 30 && pourcentage < 40) {
            if(lang == "Eng") {
                ui->label_score_food->setText("Medina Explorer");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Medina_Explorer.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("Your scoring : " + QString::number(pourcentage) + "%");
            } else {
                ui->label_score_food->setText("مستكشف المدينة القديمة");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Medina_Explorer.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("نتيجتك : %" + QString::number(pourcentage));
            }

        } else if(pourcentage >= 40 && pourcentage < 50) {
            if(lang == "Eng") {
                ui->label_score_food->setText("Souk Bargainer");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Souk_Bargainer.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("Your scoring : " + QString::number(pourcentage) + "%");
            } else {
                ui->label_score_food->setText("مفاوض الأسواق");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Souk_Bargainer.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("نتيجتك : %" + QString::number(pourcentage));
            }

        } else if(pourcentage >= 50 && pourcentage < 60) {
            if(lang == "Eng") {
                ui->label_score_food->setText("Atlas Trekker");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Atlas_Trekker.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("Your scoring : " + QString::number(pourcentage) + "%");
            } else {
                ui->label_score_food->setText("رحالة جبال الأطلس");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Atlas_Trekker.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("نتيجتك : %" + QString::number(pourcentage));
            }

        } else if(pourcentage >= 60 && pourcentage < 70) {
            if(lang == "Eng") {
                ui->label_score_food->setText("Culture Rif Enthusiast");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Culture_Rif_Enthusiast.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("Your scoring : " + QString::number(pourcentage) + "%");
            } else {
                ui->label_score_food->setText("عاشق الثقافة الريفية");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Culture_Rif_Enthusiast.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("نتيجتك : %" + QString::number(pourcentage));
            }

        } else if(pourcentage >= 70 && pourcentage < 80) {
            if(lang == "Eng") {
                ui->label_score_food->setText("Maghreb Expert");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Maghreb_Expert.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("Your scoring : " + QString::number(pourcentage) + "%");
            } else {
                ui->label_score_food->setText("خبير مغاربي");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Maghreb_Expert.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("نتيجتك : %" + QString::number(pourcentage));
            }

        } else if(pourcentage >= 80 && pourcentage < 90) {
            if(lang == "Eng") {
                ui->label_score_food->setText("Desert Guide Level");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Desert_Guide_Level.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("Your scoring : " + QString::number(pourcentage) + "%");
            } else {
                ui->label_score_food->setText("بمستوى مرشد صحراوي");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Desert_Guide_Level.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("نتيجتك : %" + QString::number(pourcentage));
            }

        } else if(pourcentage >= 90 && pourcentage < 100) {
            if(lang == "Eng") {
                ui->label_score_food->setText("True Moroccan!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/True_Moroccan.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("Your scoring : " + QString::number(pourcentage) + "%");
            } else {
                ui->label_score_food->setText("مغربي قح!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/True_Moroccan.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("نتيجتك : %" + QString::number(pourcentage));
            }

        } else {
            if(lang == "Eng") {
                ui->label_score_food->setText("Legend of the Kingdom!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Legend_of_the_Kingdom.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("Your scoring : " + QString::number(pourcentage) + "%");
            } else {
                ui->label_score_food->setText("أسطورة المملكة!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/Legend_of_the_Kingdom.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(QPixmap(resize));
                ui->label_scoring->setText("نتيجتك : %" + QString::number(pourcentage));
            }
        }}else {
        if (score <= 25) {
            if (lang == "Eng") {
                ui->label_score_food->setText("Street Guest!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/scoring_picturem_progresse/Street_Guest.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(resize);
                ui->label_scoring->setText(tr("Your score : ") + QString::number(score));
            } else {
                ui->label_score_food->setText("ضيف الزقاق!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/scoring_picturem_progresse/Street_Guest.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(resize);
                ui->label_scoring->setText("نتيجتك : " + QString::number(score));
            }
        } else if (score <= 100) {
            if (lang == "Eng") {
                ui->label_score_food->setText("Caravan Guard!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/scoring_picturem_progresse/Caravan_Guard.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(resize);
                ui->label_scoring->setText(tr("Your scoring : ") + QString::number(score));
            } else {
                ui->label_score_food->setText("حارس القافلة!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/scoring_picturem_progresse/Caravan_Guard.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(resize);
                ui->label_scoring->setText("نتيجتك : " + QString::number(score));
            }
        } else if (score <= 250) {
            if (lang == "Eng") {
                ui->label_score_food->setText("Master Artisan!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/scoring_picturem_progresse/Master_Artisan.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(resize);
                ui->label_scoring->setText(tr("Your scoring : ") + QString::number(score));
            } else {
                ui->label_score_food->setText("معلم حرفي!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/scoring_picturem_progresse/Master_Artisan.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(resize);
                ui->label_scoring->setText("نتيجتك : " + QString::number(score));
            }
        } else if (score <= 500) {
            if (lang == "Eng") {
                ui->label_score_food->setText("Grand Vizier!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/scoring_picturem_progresse/Grand_Vizier.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(resize);
                ui->label_scoring->setText(tr("Your scoring : ") + QString::number(score));
            } else {
                ui->label_score_food->setText("الصدر الأعظم!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/scoring_picturem_progresse/Grand_Vizier.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(resize);
                ui->label_scoring->setText("نتيجتك : " + QString::number(score));
            }
        } else {
            if (lang == "Eng") {
                ui->label_score_food->setText("Lion of the Atlas!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/scoring_picturem_progresse/Lion_of_the_Atlas.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(resize);
                ui->label_scoring->setText(tr("Your scoring : ") + QString::number(score));

                player->setAudioOutput(audioOutput);
                player->setSource(QUrl::fromLocalFile(base+"soundes/amazight.mp3"));
                audioOutput->setVolume(0.5);
                player->play();
            } else {
                ui->label_score_food->setText("أسد الأطلس!");
                QPixmap map(base + "img/icon/scoring/scoring_picturem/scoring_picturem_progresse/Lion_of_the_Atlas.png");
                QPixmap resize = map.scaled(ui->label_image_score->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->label_image_score->setPixmap(resize);
                ui->label_scoring->setText("نتيجتك : " + QString::number(score));

                player->setAudioOutput(audioOutput);
                player->setSource(QUrl::fromLocalFile(base+"soundes/amazight.mp3"));
                audioOutput->setVolume(0.5);
                player->play();
            }
        }
    }
}



void picture_m::on_pushButton_play_again_clicked()
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

void picture_m::setLevel(int value,int t)
{
    nombrequestions=value;
    timecount = t;
    time_left = t;
}

void picture_m::setlangw(QString langag)
{
    lang = langag;
    loadQuestionsFromJsonw();
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
    time_bool_m=true;
    loadQuestion();

    timefonction();

}
//time fonction
void picture_m::timefonction(){
    if(timecount>=0){
        ui->label_time->setText(QString::number(timecount));

        if(timecount==0){
            //click_timer.setSource(QUrl("soundes/Timer_end.wav"));
            click_timer.setSource(QUrl::fromLocalFile(
                QCoreApplication::applicationDirPath() + "/soundes/Timer_end.wav"));
            click_timer.setVolume(0.2);
            click_timer.play();

            QTimer::singleShot(3000, this, [this]() {
                click_timer.stop();
            });
            if(isclicked_reveal==false){
                ui->pushButton_reveal->setStyleSheet("#pushButton_reveal{image: url(img/icon/ic/picture_world_icon/buttons/show_red.png)0 0 0 0 scretch  scretch; border-radius:18px;}");
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
            ui->pushButton_option1->setStyleSheet("border-image: url(img/icon/ic/picture_world_icon/buttons/button_green.png) 0 0 0 0 scretch scretch;font: 900 15pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");

        }
        else if(correct==ui->pushButton_option2->text()){
            ui->pushButton_option2->setStyleSheet("border-image: url(img/icon/ic/picture_world_icon/buttons/button_green.png) 0 0 0 0 scretch scretch;font: 900 15pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");
        }else if(correct==ui->pushButton_option3->text()){
            ui->pushButton_option3->setStyleSheet("border-image: url(img/icon/ic/picture_world_icon/buttons/button_green.png) 0 0 0 0 scretch scretch;font: 900 15pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");
        }else{
            ui->pushButton_option4->setStyleSheet("border-image: url(img/icon/ic/picture_world_icon/buttons/button_green.png) 0 0 0 0 scretch scretch;font: 900 15pt Segoe UI;color: rgb(0, 0, 0);border-radius:18px;min-width: 20px;min-height: 20px;");
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
void picture_m::game(int challenge){
    gamemode = challenge;
}

//database score
void picture_m::setCurrentUser(const QString &user)
{
    currentUser = user;
}
void picture_m::updateScoreInDatabase(int score)
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

void picture_m::on_pushButton_suppr_clicked()
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
    ui->pushButton_suppr->setStyleSheet("#pushButton_suppr{ image: url(img/icon/ic/picture_world_icon/buttons/5050_rouge.png)0 0 0 0 scretch  scretch;border-radius:18px;}");
}

void picture_m::setsoundes(bool b){
    soundes = b;
}


void picture_m::on_pushButton_reveal_clicked()
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
            ui->pushButton_option1->setStyleSheet( "#pushButton_option1{font: 900 15pt Segoe UI;border-image: url(img/icon/ic/picture_world_icon/buttons/button_hover.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}");
        else if(correct == ui->pushButton_option2->text())
            ui->pushButton_option2->setStyleSheet( "#pushButton_option2{font: 900 15pt Segoe UI;border-image: url(img/icon/ic/picture_world_icon/buttons/button_hover.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}");
        else if(correct == ui->pushButton_option3->text())
            ui->pushButton_option3->setStyleSheet( "#pushButton_option3{font: 900 15pt Segoe UI;border-image: url(img/icon/ic/picture_world_icon/buttons/button_hover.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}");
        else
            ui->pushButton_option4->setStyleSheet( "#pushButton_option4{font: 900 15pt Segoe UI;border-image: url(img/icon/ic/picture_world_icon/buttons/button_hover.png) 0 0 0 0 scretch scretch;min-width: 20px;min-height: 20px;color: rgb(0, 0, 0);border-radius:18px;}");

        ui->hiding->hide();
        ui->pushButton_reveal->setStyleSheet("#pushButton_reveal{image: url(img/icon/ic/picture_world_icon/buttons/show_red.png)0 0 0 0 scretch  scretch; border-radius:18px;}");
        ui->pushButton_suppr->setEnabled(true);
    }
}


void picture_m::on_pushButton_time_clicked()
{
    timecount=timecount+15;
    ui->pushButton_time->setEnabled(false);
    check_time=false;
    ui->pushButton_time->setStyleSheet("#pushButton_time{image: url(img/icon/ic/picture_world_icon/buttons/time_red.png)0 0 0 0 scretch  scretch; border-radius:18px;}");
}

