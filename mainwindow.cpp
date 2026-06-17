#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"first_game.h"
#include <QPropertyAnimation>
#include <QEvent>
#include<QString>
#include<QPixmap>
#include<QSoundEffect>
#include "food_game.h"
#include <QTranslator>
#include<QRandomGenerator>
#include <QDebug>
#include <QUrl>
#include <QMediaPlayer>
#include <QAudioOutput>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include<QFile>
#include <QSettings>
#include <QResizeEvent>
#include <QMessageBox>

#include <QFileDialog>
#include <QBuffer>
#include <QSqlQuery>
#include<QPainter>
#include <QPainterPath>
bool s=true;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initCreditsUI();
    //base de donnes

    connectDatabase();
    createTable();

    QSettings settingsaccount("MyApp", "LoginApp");

    QString savedUser = settingsaccount.value("currentUser").toString();
    int savedScore = settingsaccount.value("currentScore").toInt();

    if(!savedUser.isEmpty())
    {
        ui->Name->setText(savedUser);
        ui->scoreLabel->setText(QString::number(savedScore));
        ui->stackedWidget->setCurrentIndex(0);
    }else{
        ui->stackedWidget->setCurrentIndex(13);
    }


    ui->pushButton_Exit->installEventFilter(this);
    l = "Eng";

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);

    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.5);
    loadQuestionsFromJson_audio();

    playRandomSound();
    ui->horizontalSlider->setRange(0, 100);
    QSettings settings("Mygame", "Myquizgame");

    //l = settings.value("language", "Eng").toString();
    l = settings.value("language", "Eng").toString();


    if(l == "Eng")
    {
        ui->comboBox->setCurrentText("English");
    }
    else
    {
        ui->comboBox->setCurrentText("Arabic");
    }

    on_pushButton_start_4_clicked();  // applique les textes
    s = settings.value("anashedEnabled", true).toBool();
    int saved_volume = settings.value("musicvolume",50).toInt();
    audioOutput->setVolume(saved_volume/100.0f);
    ui->horizontalSlider->setValue(saved_volume);
    if(!s)
    {
        player->stop();

        ui->pushButton_3->setStyleSheet("#pushButton_3{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_15->setStyleSheet("#pushButton_15{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_16->setStyleSheet("#pushButton_16{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_4->setStyleSheet("#pushButton_4{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_17->setStyleSheet("#pushButton_17{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton->setStyleSheet("#pushButton{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_14->setStyleSheet("#pushButton_14{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_2->setStyleSheet("#pushButton_2{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_20->setStyleSheet("#pushButton_20{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_22->setStyleSheet("#pushButton_22{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_24->setStyleSheet("#pushButton_24{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_25->setStyleSheet("#pushButton_25{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
    }
    /*connect(player, &QMediaPlayer::errorOccurred, this, [](QMediaPlayer::Error error, const QString &errorString){
        qDebug() << "MEDIA ERROR:" << error << errorString;
    });*/

    //check box
    QSettings setting_soundes("VotreSociete", "NomDeVotreApp");

    // Charge l'état sauvegardé (true = activé par défaut si aucune sauvegarde n'existe)
    soundes = setting_soundes.value("Sound/Enabled", true).toBool();
    ui->checkBox->setChecked(soundes);
    connect(player, &QMediaPlayer::mediaStatusChanged,
            this, &MainWindow::handleMediaStatusChanged);

    connect(ui->pushButton, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_click);
    connect(ui->pushButton_15, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_click);
    connect(ui->pushButton_16, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_click);
    connect(ui->pushButton_17, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_click);
    connect(ui->pushButton_3, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_click);
    connect(ui->pushButton_4, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_click);
    connect(ui->pushButton_14, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_click);
    connect(ui->pushButton_2, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_click);
    connect(ui->pushButton_20, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_click);
    connect(ui->pushButton_22, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_click);
    connect(ui->pushButton_24, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_click);
    connect(ui->pushButton_25, &QPushButton::clicked,
            this, &MainWindow::on_pushButton_click);


    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::change_volume);
    connect(ui->checkBox, &QCheckBox::checkStateChanged, this, &MainWindow::on_checkBox_checkStateChanged);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_about_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_Exit_clicked()
{
    QApplication::quit();
}


void MainWindow::on_pushButton_start_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_option_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_start_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_start_3_clicked()
{
    hide();

    first = new first_game();
    first->setCurrentUser(ui->Name->text());

    first->setWindowIcon(QIcon("img/icon/quiz.png"));
    first->setWindowTitle("Flag game");
    first->setLevel(10,30);
    first->game(0);
    first->setsoundes(soundes);
    first->setlang(l);
    connect(first, &first_game::backToMain,this, &MainWindow::show);
    first->show();
    first->setFixedSize(first->size());
}


void MainWindow::on_pushButton_start_long_play_clicked()
{
    hide();

    first = new first_game();
    first->setCurrentUser(ui->Name->text());
    first->game(0);
    first->setsoundes(soundes);
    first->setWindowIcon(QIcon("img/icon/quiz.png"));
    first->setWindowTitle("Flag game");
    first->setLevel(50,30);
    first->setlang(l);
    connect(first, &first_game::backToMain,this, &MainWindow::show);
    first->show();
    first->setFixedSize(first->size());
}


void MainWindow::on_pushButton_start_long_play_2_clicked()
{

    hide();

    first = new first_game();
    first->setCurrentUser(ui->Name->text());
    first->game(0);
    first->setsoundes(soundes);
    first->setWindowIcon(QIcon("img/icon/quiz.png"));
    first->setWindowTitle("Flag game");


    if(ui->textEdit_question->toPlainText().toInt()>192&&!ui->textEdit_question->toPlainText().isEmpty()){
        if(ui->textEdit_timer_2->toPlainText().isEmpty()){
            first->setLevel(192,30);
        }else{
            first->setLevel(192,ui->textEdit_timer->toPlainText().toInt());
        }
    }else{
        if(ui->textEdit_question->toPlainText().isEmpty()&&ui->textEdit_timer->toPlainText().isEmpty()){
            first->setLevel(10,30);
        }else if(ui->textEdit_question->toPlainText().isEmpty()&&!ui->textEdit_timer->toPlainText().isEmpty()){
            first->setLevel(10,ui->textEdit_timer->toPlainText().toInt());
        }else if(!ui->textEdit_question->toPlainText().isEmpty()&&ui->textEdit_timer->toPlainText().isEmpty()){
            first->setLevel(ui->textEdit_question->toPlainText().toInt(),30);
        }else{
            first->setLevel(ui->textEdit_question->toPlainText().toInt(),ui->textEdit_timer->toPlainText().toInt());
        }
    }

   first->setlang(l);

    connect(first, &first_game::backToMain,this, &MainWindow::show);
    first->show();
    first->setFixedSize(first->size());
}


void MainWindow::on_pushButton_start_4_clicked()
{
    QString language = ui->comboBox->currentText();
    if(language=="English"){ l = "Eng";
        ui->pushButton_start->setText("Start");
        ui->pushButton_option->setText("Option");
        ui->pushButton_about->setText("About");
        ui->pushButton_Exit->setText("Exit");
        ui->pushButton_start_2->setText("Flag game");
        ui->pushButton_start_4->setText("Ok");
        ui->pushButton_start_3->setText("Quick Game");
        ui->pushButton_start_long_play->setText("Long Play");
        ui->pushButton_start_long_play_2->setText("Custom Play");
        ui->label_5->setText("Nombre of question");
        ui->pushButton_start_picureid_morocco->setText("Morocco");
        ui->pushButton_start_picureid_world->setText("World");
        ui->pushButton_start_picture_morocco_quick_game->setText("Quick Game");
        ui->pushButton_start_picture_morocco_long_play->setText("Long Play");
        ui->pushButton_start_picture_custom_quick_game->setText("Custom Play");
        ui->label_16->setText("Nombre of questions");
        ui->label_22->setText("Timer(en S)");
        ui->pushButton_son->setText("Son");
        ui->pushButton_language->setText("Language");
        ui->pushButton_start_food->setText("QUIZ FOOD");
        ui->pushButton_start_id->setText("PicureID");

        ui->pushButton_start_food_quick_game->setText("Quick Game");
        ui->pushButton_start_food_long_play_3->setText("Long Play");
        ui->pushButton_start_food_long_play_4->setText("Custom Play");
        ui->pushButton_start_mondial->setText("Mondial Quiz");
        ui->pushButton_start_cup_quick_game->setText("Quick Game");
        ui->pushButton_start_cup_long_play->setText("Long Play");
        ui->pushButton_start_cup_long_play_7->setText("Custom Play");

        ui->pushButton_start_picture_long_play_m->setText("Long Play");
        ui->pushButton_start_picture_world_quick_game_m->setText("Quick Game");
        ui->pushButton_start_picture_custom_m->setText("Custom Play");
        ui->label_58->setText("Nombre of questions");
        ui->label_52->setText("Timer(en S)");

        ui->pushButton_start_picture_long_play_1->setText("Long Play");
        ui->pushButton_start_picture_world_quick_game->setText("Quick Game");
        ui->pushButton_start_picture_custom->setText("Custom Play");
        ui->label_41->setText("Nombre of questions");
        ui->label_42->setText("Timer(en S)");

        ui->label_8->setText("Nombre of questions");
        ui->label_11->setText("Timer(en S)");
        ui->label_20->setText("Nombre of questions");
        ui->label_21->setText("Timer(en S)");

        ui->pushButton_start_challenge->setText("Challenge");
        ui->pushButton_start_food_challenge->setText("Challenge");
        ui->pushButton_start_cup_challenge->setText("Challenge");
        ui->label_6->setText("Timer(en S)");
        ui->pushButton_start_picture_challenge->setText("Challenge");
        ui->pushButton_start_picture_challenge_2->setText("Challenge");

        ui->label_10->setText("username");
        ui->label_19->setText("Password");
        ui->label_28->setText("Sign in to your account");
        ui->loginButton->setText("Log in");
        ui->createButton->setText("Sign up");
        ui->label_27->setText("New here?");
        ui->nameEdit->setPlaceholderText("Enter your username");
        ui->passwordEdit->setPlaceholderText("enter your password");
        ui->label_30->setText("Current  Score");
        ui->logout->setText("Logout");
        ui->label_31->setText("Soundes effect");
        ui->label_4->setText("Setting");
        initCreditsUI();

    }
    else{l = "Arab";
        ui->pushButton_start->setText("لعب");
        ui->pushButton_option->setText("الاعدادات");
        ui->pushButton_about->setText("حول");
        ui->pushButton_Exit->setText("الخروج");
        ui->pushButton_start_2->setText("لعبة العواصم");
        ui->pushButton_start_4->setText("تأكيد");
        ui->pushButton_start_3->setText("اللعب سريع");
        ui->pushButton_start_long_play->setText("اللعب الطويل");
        ui->pushButton_start_long_play_2->setText("تخصيص");
        ui->label_5->setText("عدد الأسئلة");
        ui->pushButton_start_mondial->setText("تحدي المونديال");

        ui->pushButton_start_cup_quick_game->setText("اللعب سريع");
        ui->pushButton_start_cup_long_play->setText("اللعب الطويل");
        ui->pushButton_start_cup_long_play_7->setText("تخصيص");

        ui->pushButton_start_food_quick_game->setText("اللعب سريع");
        ui->pushButton_start_food_long_play_3->setText("اللعب الطويل");
        ui->pushButton_start_food_long_play_4->setText("تخصيص");


        ui->pushButton_start_picureid_morocco->setText("المغرب");
        ui->pushButton_start_picureid_world->setText("العالم");
        ui->pushButton_start_picture_morocco_quick_game->setText("لعبة سريعة");
        ui->pushButton_start_picture_morocco_long_play->setText("لعب طويل");
        ui->pushButton_start_picture_custom_quick_game->setText("لعب مخصص");
        ui->label_16->setText("عدد الأسئلة");
        ui->label_22->setText("المؤقت (بالثواني)");
        ui->pushButton_son->setText("الصوت");
        ui->pushButton_language->setText("اللغة");
        ui->pushButton_start_food->setText("اختبار الأطعمة");
        ui->pushButton_start_id->setText("تحدي الصور");

        ui->pushButton_start_picture_long_play_m->setText(tr("لعب طويل"));
        ui->pushButton_start_picture_world_quick_game_m->setText(tr("لعبة سريعة"));
        ui->pushButton_start_picture_custom_m->setText(tr("لعب مخصص"));
        ui->label_58->setText(tr("عدد الأسئلة"));
        ui->label_52->setText(tr("المؤقت (بالثواني)"));

        ui->pushButton_start_picture_long_play_1->setText(tr("لعب طويل"));
        ui->pushButton_start_picture_world_quick_game->setText(tr("لعبة سريعة"));
        ui->pushButton_start_picture_custom->setText(tr("لعب مخصص"));
        ui->label_41->setText(tr("عدد الأسئلة"));
        ui->label_42->setText(tr("المؤقت (بالثواني)"));

        ui->label_8->setText("عدد الأسئلة");
        ui->label_11->setText("المؤقت (بالثواني)");
        ui->label_20->setText("عدد الأسئلة");
        ui->label_21->setText("المؤقت (بالثواني)");

        ui->pushButton_start_challenge->setText("تحدي");
        ui->pushButton_start_food_challenge->setText("تحدي");
        ui->pushButton_start_cup_challenge->setText("تحدي");
        ui->label_6->setText("المؤقت (بالثواني)");
        ui->pushButton_start_picture_challenge->setText("تحدي");
        ui->pushButton_start_picture_challenge_2->setText("تحدي");

        ui->label_10->setText("اسم المستخدم");
        ui->label_19->setText("كلمة المرور");
        ui->label_28->setText("سجّل الدخول إلى حسابك");
        ui->loginButton->setText("تسجيل الدخول");
        ui->createButton->setText("إنشاء حساب");
        ui->label_27->setText("جديد هنا؟");
        ui->nameEdit->setPlaceholderText("أدخل اسم المستخدم");
        ui->passwordEdit->setPlaceholderText("أدخل كلمة المرور");
        ui->label_30->setText("النتيجة الحالية");
        ui->logout->setText("تسجيل الخروج");
        ui->label_31->setText("تأثير الصوت:");
        ui->label_4->setText("الاعدادات");
        initCreditsUI();
    }

    QSettings settings("Mygame", "Myquizgame");
    settings.setValue("language", l);
    /*qApp->removeTranslator(&translator);

    if(language == "English") {
        l = "Eng";
        // On charge le fichier compilé .qm
        if(translator.load("app_en", ":/Translation")) {
            qApp->installTranslator(&translator);
            qApp->setLayoutDirection(Qt::LeftToRight);
        }
    } else {
        l = "Arab";
        if(translator.load("app_ar", ":/Translation")) {
            qApp->installTranslator(&translator);
            qApp->setLayoutDirection(Qt::RightToLeft);
        }
    }

    // TRÈS IMPORTANT : Cette ligne applique les changements à l'interface
    ui->retranslateUi(this);*/
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->pushButton_Exit)
    {
        if (event->type() == QEvent::Enter)
        {
            ui->label_icon_princ->setStyleSheet( "image: url(img/icon/quiz_icon_angry.png);");
            ui->stackedWidget->setStyleSheet( "#stackedWidget{border-image: url(img/icon/ic/backgr_main_hover.png) 0 0 0 0 scretch scretch;}");
            clickSound.setSource(QUrl::fromLocalFile("soundes/Exit.wav"));
            clickSound.setVolume(0.5);
            clickSound.play();
        }
        else if (event->type() == QEvent::Leave)
        {
            ui->label_icon_princ->setStyleSheet( "image: url(img/icon/quiz.png);");
            ui->stackedWidget->setStyleSheet( "#stackedWidget{border-image: url(img/icon/ic/backgr_main.png) 0 0 0 0 scretch scretch;}");
            clickSound.stop();
        }
    }
    return QWidget::eventFilter(obj, event);
}


void MainWindow::on_pushButton_start_food_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_start_food_quick_game_clicked()
{
    hide();

    second = new food_game();
    second->setCurrentUser(ui->Name->text());
    second->game(0);
    second->setsoundes(soundes);
    second->setWindowIcon(QIcon("img/icon/quiz_food.png"));
    second->setWindowTitle("Food game");
    second->setLevel_food(10,30);
    second->setlang_food(l);
    connect(second, &food_game::backToMain,this, &MainWindow::show);
    second->show();
    second->setFixedSize(second->size());
}


void MainWindow::on_pushButton_start_food_long_play_3_clicked()
{
    hide();

    second = new food_game();
    second->setCurrentUser(ui->Name->text());
    second->game(0);
    second->setsoundes(soundes);
    second->setWindowIcon(QIcon("img/icon/quiz_food.png"));
    second->setWindowTitle("Food game");
    second->setLevel_food(50,30);
    second->setlang_food(l);
    connect(second, &food_game::backToMain,this, &MainWindow::show);
    second->show();
    second->setFixedSize(second->size());
}


void MainWindow::on_pushButton_start_food_long_play_4_clicked()
{
    hide();

    second = new food_game();
    second->setCurrentUser(ui->Name->text());
    second->game(0);
    second->setsoundes(soundes);
    second->setWindowIcon(QIcon("img/icon/quiz_food.png"));
    second->setWindowTitle("Food game");



    if(ui->textEdit_question_2->toPlainText().toInt()>116&&!ui->textEdit_question_2->toPlainText().isEmpty()){
        if(ui->textEdit_timer_2->toPlainText().isEmpty()){
            second->setLevel_food(116,30);
        }else{
            second->setLevel_food(116,ui->textEdit_timer_2->toPlainText().toInt());
        }
    }else{
        if(ui->textEdit_question_2->toPlainText().isEmpty()&&ui->textEdit_timer_2->toPlainText().isEmpty()){
            second->setLevel_food(10,30);
        }else if(ui->textEdit_question_2->toPlainText().isEmpty()&&!ui->textEdit_timer_2->toPlainText().isEmpty()){
            second->setLevel_food(10,ui->textEdit_timer_2->toPlainText().toInt());
        }else if(!ui->textEdit_question_2->toPlainText().isEmpty()&&ui->textEdit_timer_2->toPlainText().isEmpty()){
            second->setLevel_food(ui->textEdit_question_2->toPlainText().toInt(),30);
        }else if(ui->textEdit_question_2->toPlainText().toInt()<=116){
            second->setLevel_food(ui->textEdit_question_2->toPlainText().toInt(),ui->textEdit_timer_2->toPlainText().toInt());
        }
    }

    second->setlang_food(l);

    connect(second, &food_game::backToMain,this, &MainWindow::show);
    second->show();
    second->setFixedSize(second->size());
}


void MainWindow::on_pushButton_start_mondial_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_start_cup_quick_game_clicked()
{
    hide();

    third = new world_cup();
    third->setCurrentUser(ui->Name->text());
    third->game(0);
    third->setsoundes(soundes);
    third->setWindowIcon(QIcon("img/icon/ic/mondial_icon/icon_mondial.png"));
    third->setWindowTitle("Mondial game");
    third->setLevel(10,30);
    third->setlang(l);
    connect(third, &world_cup::backToMain,this, &MainWindow::show);
    third->show();
    third->setFixedSize(third->size());
}


void MainWindow::on_pushButton_start_cup_long_play_clicked()
{
    hide();

    third = new world_cup();
    third->setWindowIcon(QIcon("img/icon/ic/mondial_icon/icon_mondial.png"));
    third->game(0);
    third->setsoundes(soundes);
    third->setWindowIcon(QIcon("img/icon/quiz_food.png"));
    third->setWindowTitle("Mondial game");
    third->setLevel(50,30);
    third->setlang(l);
    connect(third, &world_cup::backToMain,this, &MainWindow::show);
    third->show();
    third->setFixedSize(third->size());
}


void MainWindow::on_pushButton_start_cup_long_play_7_clicked()
{
    hide();

    third = new world_cup();
    third->setCurrentUser(ui->Name->text());
    third->game(0);
    third->setsoundes(soundes);
    third->setWindowIcon(QIcon("img/icon/ic/mondial_icon/icon_mondial.png"));
    third->setWindowTitle("Mondial game");

    if(ui->textEdit_question_4->toPlainText().toInt()>400&&!ui->textEdit_question_4->toPlainText().isEmpty()){
        if(ui->textEdit_timer_4->toPlainText().isEmpty()){
            third->setLevel(400,30);
        }else{
            third->setLevel(400,ui->textEdit_timer_4->toPlainText().toInt());
        }
    }else{
        if(ui->textEdit_question_4->toPlainText().isEmpty()&&ui->textEdit_timer_4->toPlainText().isEmpty()){
            third->setLevel(10,30);
        }else if(ui->textEdit_question_4->toPlainText().isEmpty()&&!ui->textEdit_timer_4->toPlainText().isEmpty()){
            third->setLevel(10,ui->textEdit_timer_4->toPlainText().toInt());
        }else if(!ui->textEdit_question_4->toPlainText().isEmpty()&&ui->textEdit_timer_4->toPlainText().isEmpty()){
            third->setLevel(ui->textEdit_question_4->toPlainText().toInt(),30);
        }else{
            third->setLevel(ui->textEdit_question_4->toPlainText().toInt(),ui->textEdit_timer_4->toPlainText().toInt());
        }
    }


    third->setlang(l);
    connect(third, &world_cup::backToMain,this, &MainWindow::show);
    third->show();
    third->setFixedSize(third->size());
}


void MainWindow::on_pushButton_start_id_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_start_picureid_world_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}


void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_pushButton_start_picureid_morocco_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
}


void MainWindow::on_pushButton_start_picture_world_quick_game_clicked()
{
    hide();

    quatro = new picture_world();
    quatro->setCurrentUser(ui->Name->text());
    quatro->game(0);
    quatro->setsoundes(soundes);
    quatro->setWindowIcon(QIcon("img/icon/quiz_food.png"));
    quatro->setWindowTitle("Picture World game");
    quatro->setLevel(10,30);
    quatro->setlangw(l);
    connect(quatro, &picture_world::backToMain,this, &MainWindow::show);
    quatro->show();
    quatro->setFixedSize(quatro->size());
}


void MainWindow::loadQuestionsFromJson_audio()
{
    // Ouvrir le fichier JSON
    QFile file("Json/audio/audio.json");  // Chemin vers votre fichier JSON

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Erreur: Impossible d'ouvrir le fichier JSON";
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (doc.isNull())
    {
        qDebug() << "Erreur: JSON invalide";
        return;
    }

    QJsonArray array = doc.array();

    // Parcourir le tableau JSON
    for (const auto& value : array)
    {
        QJsonObject obj = value.toObject();

        Sound sound;
        sound.source = obj["onshod"].toString();

        sounds.append(sound);
        qDebug() << "Son chargé:" << sound.source;
    }

    // Mélanger aléatoirement
    std::shuffle(sounds.begin(), sounds.end(), *QRandomGenerator::global());

    qDebug() << "Nombre de sons chargés:" << sounds.size();
}

void MainWindow::playRandomSound()
{
    /*if (sounds.isEmpty())
    {
        qDebug() << "Aucun son chargé";
        return;
    }

    int randomIndex = QRandomGenerator::global()->bounded(sounds.size());
    Sound selectedSound = sounds[randomIndex];

    qDebug() << "Lecture du son:" << selectedSound.source;

    int saved_volume = QSettings("Mygame", "Myquizgame").value("musicvolume", 50).toInt();
    player->setSource(QUrl(selectedSound.source));
    audioOutput->setVolume(saved_volume/100.0f);
    player->play();*/

    /*QSettings settings("Mygame", "Myquizgame");
    s = settings.value("anashedEnabled", true).toBool();
    int saved_volume = settings.value("musicvolume",50).toInt();*/
    if (sounds.isEmpty())
    {
        qDebug() << "Aucun son chargé";
        return;
    }

    if (currentSoundIndex >= sounds.size())
    {
        std::shuffle(sounds.begin(), sounds.end(), *QRandomGenerator::global());
        currentSoundIndex = 0;
    }

    Sound selectedSound = sounds[currentSoundIndex];
    currentSoundIndex++;

    qDebug() << "Lecture du son:" << selectedSound.source;
    int saved_volume = QSettings("Mygame", "Myquizgame").value("musicvolume", 50).toInt();
    player->setSource(QUrl(selectedSound.source));
    audioOutput->setVolume(saved_volume / 100.0f);
    player->play();

    QFileInfo fileInfo(selectedSound.source);
    QString cleanName = fileInfo.baseName();
    ui->label_an->setText(cleanName);

}


void MainWindow::handleMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
    {
        playRandomSound();
    }
}
void MainWindow::on_pushButton_click()
{
    if(s){ui->pushButton_3->setStyleSheet("#pushButton_3{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");s=false;player->stop();
        ui->pushButton_15->setStyleSheet("#pushButton_15{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_16->setStyleSheet("#pushButton_16{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_4->setStyleSheet("#pushButton_4{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_17->setStyleSheet("#pushButton_17{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton->setStyleSheet("#pushButton{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_14->setStyleSheet("#pushButton_14{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_2->setStyleSheet("#pushButton_2{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_20->setStyleSheet("#pushButton_20{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_22->setStyleSheet("#pushButton_22{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_24->setStyleSheet("#pushButton_24{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");
        ui->pushButton_25->setStyleSheet("#pushButton_25{image: url(img/audio_icon/volume_mute.png);border-radius:20px;}");}

    else{ui->pushButton_3->setStyleSheet("#pushButton_3{image: url(img/audio_icon/volume.png);border-radius:20px;}");s=true;playRandomSound();player->play();
        ui->pushButton_15->setStyleSheet("#pushButton_15{image: url(img/audio_icon/volume.png);border-radius:20px;}");
        ui->pushButton_16->setStyleSheet("#pushButton_16{image: url(img/audio_icon/volume.png);border-radius:20px;}");
        ui->pushButton_4->setStyleSheet("#pushButton_4{image: url(img/audio_icon/volume.png);border-radius:20px;}");
        ui->pushButton_17->setStyleSheet("#pushButton_17{image: url(img/audio_icon/volume.png);border-radius:20px;}");
        ui->pushButton->setStyleSheet("#pushButton{image: url(img/audio_icon/volume.png);border-radius:20px;}");
        ui->pushButton_14->setStyleSheet("#pushButton_14{image: url(img/audio_icon/volume.png);border-radius:20px;}");
        ui->pushButton_2->setStyleSheet("#pushButton_2{image: url(img/audio_icon/volume.png);border-radius:20px;}");
        ui->pushButton_20->setStyleSheet("#pushButton_20{image: url(img/audio_icon/volume.png);border-radius:20px;}");
        ui->pushButton_22->setStyleSheet("#pushButton_22{image: url(img/audio_icon/volume.png);border-radius:20px;}");
        ui->pushButton_24->setStyleSheet("#pushButton_24{image: url(img/audio_icon/volume.png);border-radius:20px;}");
        ui->pushButton_25->setStyleSheet("#pushButton_25{image: url(img/audio_icon/volume.png);border-radius:20px;}");
    }
    QSettings settings("Mygame", "Myquizgame");
    settings.setValue("anashedEnabled", s);
}

void MainWindow::on_pushButton_start_picture_custom_clicked()
{
    hide();

    quatro = new picture_world();
    quatro->setCurrentUser(ui->Name->text());
    quatro->game(0);
    quatro->setsoundes(soundes);
    quatro->setlangw(l);
    quatro->setWindowIcon(QIcon("img/icon/quiz_food.png"));
    quatro->setWindowTitle("Picture World game");

    if(ui->textEdit_question_8->toPlainText().toInt()>195&&!ui->textEdit_question_8->toPlainText().isEmpty()){
        if(ui->textEdit_timer_8->toPlainText().isEmpty()){
            quatro->setLevel(195,30);
        }else{
            quatro->setLevel(195,ui->textEdit_timer_8->toPlainText().toInt());
        }
    }else{
        if(ui->textEdit_question_8->toPlainText().isEmpty()&&ui->textEdit_timer_8->toPlainText().isEmpty()){
            quatro->setLevel(10,30);
        }else if(ui->textEdit_question_8->toPlainText().isEmpty()&&!ui->textEdit_timer_8->toPlainText().isEmpty()){
            quatro->setLevel(10,ui->textEdit_timer_8->toPlainText().toInt());
        }else if(!ui->textEdit_question_8->toPlainText().isEmpty()&&ui->textEdit_timer_8->toPlainText().isEmpty()){
            quatro->setLevel(ui->textEdit_question_8->toPlainText().toInt(),30);
        }else{
            quatro->setLevel(ui->textEdit_question_8->toPlainText().toInt(),ui->textEdit_timer_8->toPlainText().toInt());
        }
    }

    connect(quatro, &picture_world::backToMain,this, &MainWindow::show);
    quatro->show();
    quatro->setFixedSize(quatro->size());
}


void MainWindow::on_pushButton_start_picture_long_play_1_clicked()
{
    hide();

    quatro = new picture_world();
    quatro->setCurrentUser(ui->Name->text());
    quatro->game(0);
    quatro->setsoundes(soundes);
    quatro->setWindowIcon(QIcon("img/icon/quiz_food.png"));
    quatro->setWindowTitle("Picture World game");
    quatro->setLevel(50,30);
    quatro->setlangw(l);
    connect(quatro, &picture_world::backToMain,this, &MainWindow::show);
    quatro->show();
    quatro->setFixedSize(quatro->size());
}


void MainWindow::on_pushButton_language_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_pushButton_start_picture_world_quick_game_m_clicked()
{
    hide();
    QString base = QCoreApplication::applicationDirPath() + "/";
    cinqo = new picture_m();
    cinqo->setCurrentUser(ui->Name->text());
    cinqo->game(0);
    cinqo->setsoundes(soundes);
    cinqo->setWindowIcon(QIcon(base+"img/icon/ic/picture_world_icon/icon_morocco.png"));
    cinqo->setWindowTitle("Picture World morocco");
    cinqo->setLevel(10,30);
    cinqo->setlangw(l);
    connect(cinqo, &picture_m::backToMain,this, &MainWindow::show);
    cinqo->show();
    cinqo->setFixedSize(cinqo->size());
}


void MainWindow::on_pushButton_start_picture_long_play_m_clicked()
{
    hide();
    QString base = QCoreApplication::applicationDirPath() + "/";
    cinqo = new picture_m();
    cinqo->setCurrentUser(ui->Name->text());
    cinqo->game(0);
    cinqo->setsoundes(soundes);
    cinqo->setWindowIcon(QIcon(base+"img/icon/ic/picture_world_icon/icon_morocco.png"));
    cinqo->setWindowTitle("Picture World morocco");
    cinqo->setLevel(50,30);
    cinqo->setlangw(l);
    connect(cinqo, &picture_m::backToMain,this, &MainWindow::show);
    cinqo->show();
    cinqo->setFixedSize(cinqo->size());
}


void MainWindow::on_pushButton_start_picture_custom_m_clicked()
{
    hide();
    QString base = QCoreApplication::applicationDirPath() + "/";
    cinqo = new picture_m();
    cinqo->setCurrentUser(ui->Name->text());
    cinqo->game(0);
    cinqo->setsoundes(soundes);
    cinqo->setlangw(l);
    cinqo->setWindowIcon(QIcon(base+"img/icon/ic/picture_world_icon/icon_morocco.png"));
    cinqo->setWindowTitle("Picture World morocco");


    if(ui->textEdit_question_m_3->toPlainText().toInt()>241&&!ui->textEdit_question_m_3->toPlainText().isEmpty()){
        if(ui->textEdit_timer_m_4->toPlainText().isEmpty()){
            cinqo->setLevel(240,30);
        }else{
            cinqo->setLevel(240,ui->textEdit_timer_m_4->toPlainText().toInt());
        }
    }else{
        if(ui->textEdit_question_m_3->toPlainText().isEmpty()&&ui->textEdit_timer_m_4->toPlainText().isEmpty()){
            cinqo->setLevel(10,30);
        }else if(ui->textEdit_question_m_3->toPlainText().isEmpty()&&!ui->textEdit_timer_m_4->toPlainText().isEmpty()){
            cinqo->setLevel(10,ui->textEdit_timer_m_4->toPlainText().toInt());
        }else if(!ui->textEdit_question_m_3->toPlainText().isEmpty()&&ui->textEdit_timer_m_4->toPlainText().isEmpty()){
            cinqo->setLevel(ui->textEdit_question_m_3->toPlainText().toInt(),30);
        }else{
            cinqo->setLevel(ui->textEdit_question_m_3->toPlainText().toInt(),ui->textEdit_timer_m_4->toPlainText().toInt());
        }
    }


    connect(cinqo, &picture_m::backToMain,this, &MainWindow::show);
    cinqo->show();
    cinqo->setFixedSize(cinqo->size());
}


void MainWindow::change_volume(int value)
{
    float volume = value / 100.0f;
    audioOutput->setVolume(volume);

    QSettings settings("Mygame", "Myquizgame");
    settings.setValue("musicvolume", value);
}


void MainWindow::on_pushButton_21_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}


void MainWindow::on_pushButton_son_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);
}


void MainWindow::on_pushButton_start_challenge_clicked()
{
    hide();

    first = new first_game();
    first->setCurrentUser(ui->Name->text());
    first->setsoundes(soundes);
    first->setWindowIcon(QIcon("img/icon/quiz.png"));
    first->setWindowTitle("Flag game challenge");
    first->setLevel(20,30);
    first->game(1);
    first->setlang(l);
    connect(first, &first_game::backToMain,this, &MainWindow::show);
    first->show();
    first->setFixedSize(first->size());
}


void MainWindow::on_pushButton_start_cup_challenge_clicked()
{
    hide();

    third = new world_cup();
    third->setCurrentUser(ui->Name->text());
    third->game(1);
    third->setsoundes(soundes);
    third->setWindowIcon(QIcon("img/icon/ic/mondial_icon/icon_mondial.png"));
    third->setWindowTitle("Mondial game challenge");
    third->setLevel(20,30);
    third->setlang(l);
    connect(third, &world_cup::backToMain,this, &MainWindow::show);
    third->show();
    third->setFixedSize(third->size());
}


void MainWindow::on_pushButton_start_food_challenge_clicked()
{
    hide();

    second = new food_game();
    second->setCurrentUser(ui->Name->text());
    second->game(1);
    second->setsoundes(soundes);
    second->setWindowIcon(QIcon("img/icon/quiz_food.png"));
    second->setWindowTitle("Food game challenge");
    second->setLevel_food(20,30);
    second->setlang_food(l);
    connect(second, &food_game::backToMain,this, &MainWindow::show);
    second->show();
    second->setFixedSize(second->size());
}


void MainWindow::on_pushButton_start_picture_challenge_clicked()
{
    hide();

    quatro = new picture_world();
    quatro->setCurrentUser(ui->Name->text());
    quatro->game(1);
    quatro->setsoundes(soundes);
    quatro->setWindowIcon(QIcon("img/icon/quiz_food.png"));
    quatro->setWindowTitle("Picture World game challenge");
    quatro->setLevel(20,30);
    quatro->setlangw(l);
    connect(quatro, &picture_world::backToMain,this, &MainWindow::show);
    quatro->show();
    quatro->setFixedSize(quatro->size());
}


void MainWindow::on_pushButton_start_picture_challenge_2_clicked()
{
    hide();
    QString base = QCoreApplication::applicationDirPath() + "/";
    cinqo = new picture_m();
    cinqo->setCurrentUser(ui->Name->text());
    cinqo->game(1);
    cinqo->setsoundes(soundes);
    cinqo->setWindowIcon(QIcon(base+"img/icon/ic/picture_world_icon/icon_morocco.png"));
    cinqo->setWindowTitle("Picture World morocco challenge");
    cinqo->setLevel(20,30);
    cinqo->setlangw(l);
    connect(cinqo, &picture_m::backToMain,this, &MainWindow::show);
    cinqo->show();
    cinqo->setFixedSize(cinqo->size());
}


//database
void MainWindow::connectDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(appDataPath);

    QString dbPath = appDataPath + "/users.db";
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Database not connected!");
    }
}

void MainWindow::createTable()
{
    /*QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name TEXT UNIQUE,"
               "password TEXT,"
               "score INTEGER DEFAULT 0)");*/
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name TEXT UNIQUE,"
               "password TEXT,"
               "score INTEGER DEFAULT 0,"
               "photo BLOB)");
    query.exec("ALTER TABLE users ADD COLUMN photo BLOB");
}

void MainWindow::on_createButton_clicked()
{
    QString name = ui->nameEdit->text();
    QString password = ui->passwordEdit->text();

    if(name.isEmpty() || password.isEmpty()){
        if(l=="Eng"){
            QMessageBox::warning(this,"Warning","Fill all fields");
        }else{
            QMessageBox::warning(this, "تحذير", "الرجاء ملء جميع الخانات");
        }
        return;
    }
    if(name=="ILYASS BENHADI"&&password=="21/06/2005"){
        player->stop();
        ui->stackedWidget->setStyleSheet( "#stackedWidget{border-image: url(img/icon/ic/backgr_main_hover.png) 0 0 0 0 scretch scretch;}");
        QString base = QCoreApplication::applicationDirPath() + "/";
        player->setSource(QUrl::fromLocalFile(base+"soundes/you_are_not_him.mp3"));
        audioOutput->setVolume(0.5);
        player->play();
        if(l=="Eng"){
            QMessageBox::warning(this, "Warning", "You are not him");
        }else{
            QMessageBox::warning(this, "تحذير", "الرجاء إدخال 6 أحرف على الأقل في كلمة المرور");
        }

        QTimer::singleShot(9500, this, [=]() {
            qApp->quit();
        });
        return;
    }
    if(name.length()<3){
        if(l=="Eng"){
            QMessageBox::warning(this, "Warning", "enter at least 3 characters in username");
        }else{
            QMessageBox::warning(this, "تحذير", "الرجاء إدخال 3 أحرف على الأقل في الاسم");
        }

        return;
    }
    if(password.length()<6){
        if(l=="Eng"){
            QMessageBox::warning(this, "Warning", "enter at least 6 characters in password");
        }else{
            QMessageBox::warning(this, "تحذير", "الرجاء إدخال 6 أحرف على الأقل في كلمة المرور");
        }

        return;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO users (name,password) VALUES (:name,:password)");
    query.bindValue(":name", name);
    query.bindValue(":password", password);

    if(query.exec()){
        //QMessageBox::information(this,"Success","Account created");
        ui->Name->setText(name);
        ui->scoreLabel->setText(QString::number(0));
        QSettings settings("MyApp", "LoginApp");
        settings.setValue("currentUser", name);
        ui->stackedWidget->setCurrentIndex(0);
    }else{
        if(l=="Eng"){
            QMessageBox::warning(this,"Error","User already exist");
        }else{
            QMessageBox::warning(this, "خطأ", "المستخدم موجود بالفعل");
        }

    }
}

void MainWindow::on_loginButton_clicked()
{
    QString name = ui->nameEdit->text();
    QString password = ui->passwordEdit->text();

    QSqlQuery query;
    query.prepare("SELECT name, score FROM users WHERE name=:name AND password=:password");
    query.bindValue(":name", name);
    query.bindValue(":password", password);

    if(query.exec() && query.next()){
        //QMessageBox::information(this,"Login","Login successful");
        QString dbName = query.value("name").toString();
        int score = query.value("score").toInt();
        ui->Name->setText(dbName);
        ui->scoreLabel->setText(QString::number(score));
        QSettings settingsaccount("MyApp", "LoginApp");
        settingsaccount.setValue("currentUser", dbName);
        settingsaccount.setValue("currentScore", score);
        ui->stackedWidget->setCurrentIndex(0);
        loadUserPhoto();

    }else{
        if(l=="Eng"){
            QMessageBox::warning(this,"Login","Wrong name or password");
        }else{
            QMessageBox::warning(this, "تسجيل الدخول", "اسم المستخدم أو كلمة المرور غير صحيحة");
        }

    }
}

void MainWindow::on_logout_clicked()
{
    QSettings settingsaccount("MyApp", "LoginApp");
    settingsaccount.remove("currentUser");settingsaccount.remove("currentScore");
    ui->stackedWidget->setCurrentIndex(13);
}


void MainWindow::on_pushButton_start_5_clicked()
{
    QSettings settingsaccount("MyApp", "LoginApp");
    int savedScore = settingsaccount.value("currentScore").toInt();
    ui->scoreLabel->setText(QString::number(savedScore));
    ui->stackedWidget->setCurrentIndex(14);
    loadUserPhoto();
}


void MainWindow::on_pushButton_23_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_checkBox_checkStateChanged(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::Checked) {
        soundes = true;
    } else {
        soundes = false;
    }

    //soundes = (arg1 == Qt::Checked);

    // Sauvegarde dans QSettings
    QSettings setting_soundes("VotreSociete", "NomDeVotreApp");
    setting_soundes.setValue("Sound/Enabled", soundes);
}


void MainWindow::initCreditsUI() {
    ui->creditsLabel->setOpenExternalLinks(true); // Permet de rendre les liens cliquables
    ui->creditsLabel->setWordWrap(true);          // Permet au texte de passer à la ligne automatiquement
    if(l=="Eng"){
        QString creditsText = "<h1 style='margin-bottom: 0px;'>CRÉDITS</h1>"
                              "<p style='font-size: 11pt; color: #555; margin-top: 5px;'>Version 1.0</p>"

                              "<p style='font-size: 12pt;'><b>GAME DEVELOPMENT :</b>"
                              "- ILYASS BENHADI"

                              "<p style='font-size: 12pt;'><b>Content & Assets:</b><br/>"
                              "- Questions Research: ILYASS BENHADI<br/>"
                              "- UI/UX Design: ILYASS BENHADI<br/>"
                              "- Icons Creation: Banana AI<br/>"
                              "- Anasheed: Osama Al-Waiz<br/>"
                              "- Graphics: Application Thematic Icons<br/>"
                              "-IDIA: ILYASS BENHADI</p><br/>"

                              "<p style='font-size: 11pt; color: #777;'>"
                              "Propulsé par le framework <a href='https://www.qt.io/' style='color: #41cd52; font-weight: bold; text-decoration: none;'>Qt</a></p>";
        ui->creditsLabel->setText(creditsText);
    }else{
        QString creditsText = "<div dir='rtl'>" // Aligne la lecture de droite à gauche
                              "<h1 style='margin-bottom: 0px;'>حقوق العمل</h1>"
                              "<p style='font-size: 11pt; color: #555; margin-top: 5px;'>الإصدار 1.0</p>"

                              "<p style='font-size: 12pt;'><b>تطوير البرمجيات:</b><br/>"
                              "- إلياس بنهادي</p>"

                              "<p style='font-size: 12pt;'><b>المحتوى والمؤثرات:</b><br/>"
                              "- البحث عن الأسئلة: إلياس بنهادي<br/>"
                              "- تصميم واجهة المستخدم (UI/UX): إلياس بنهادي<br/>"
                              "- إنشاء الأيقونات: بنانا آي (Banana AI)<br/>"
                              "- الأناشيد: أسامة الوعظ<br/>"
                              "- الرسوميات: الأيقونات الموضوعية للتطبيق<br/>"
                              "- الفكرة والرؤية (Idea): إلياس بنهادي</p>"

                              "<br/>"

                              "<p style='font-size: 11pt; color: #777;'>"
                              "مشغل بواسطة إطار العمل <a href='https://www.qt.io/' style='color: #41cd52; font-weight: bold; text-decoration: none;'>Qt</a></p>"
                              "</div>";
      ui->creditsLabel->setText(creditsText);
    }

}


void MainWindow::on_uploadImg_clicked()
{
    QString currentUser = ui->Name->text();
    if (currentUser.isEmpty()) return;

    QString filePath = QFileDialog::getOpenFileName(
        this,
        l == "Eng" ? "Choose Profile Picture" : "اختر صورة الملف الشخصي",
        "",
        "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
        );

    if (filePath.isEmpty()) return;

    // Read the image file into bytes
    QFile imgFile(filePath);
    if (!imgFile.open(QIODevice::ReadOnly)) return;
    QByteArray imgData = imgFile.readAll();
    imgFile.close();

    // Scale the image to a reasonable size (e.g. 200×200) before saving
    QPixmap pixmap(filePath);
    pixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QByteArray scaledData;
    QBuffer buffer(&scaledData);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");

    // Save to database
    QSqlQuery query;
    query.prepare("UPDATE users SET photo = :photo WHERE name = :name");
    query.bindValue(":photo", scaledData);
    query.bindValue(":name", currentUser);

    if (query.exec()) {
        int size = 100;
        QPixmap src = pixmap.scaled(size, size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        int x = (src.width() - size) / 2;
        int y = (src.height() - size) / 2;
        src = src.copy(x, y, size, size);
        QPixmap rounded(size, size);
        rounded.fill(Qt::transparent);
        QPainter painter(&rounded);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        QPainterPath path;
        path.addEllipse(0, 0, size, size);
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, src);
        painter.end();
        ui->label_24->setPixmap(rounded);
        ui->label_24->setStyleSheet("#label_24{border-radius: 100px;}");
    } else {
        QMessageBox::warning(this, "Error", "Failed to save image.");
    }
}

void MainWindow::loadUserPhoto()
{
    QString currentUser = ui->Name->text();
    if (currentUser.isEmpty()) return;

    QSqlQuery query;
    query.prepare("SELECT photo FROM users WHERE name = :name");
    query.bindValue(":name", currentUser);

    if (query.exec() && query.next()) {
        QByteArray imgData = query.value("photo").toByteArray();
        if (!imgData.isEmpty()) {
            QPixmap pixmap;
            pixmap.loadFromData(imgData);

            int size = 100;
            QPixmap src = pixmap.scaled(size, size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
            int x = (src.width() - size) / 2;
            int y = (src.height() - size) / 2;
            src = src.copy(x, y, size, size);
            QPixmap rounded(size, size);
            rounded.fill(Qt::transparent);
            QPainter painter(&rounded);
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
            QPainterPath path;
            path.addEllipse(0, 0, size, size);
            painter.setClipPath(path);
            painter.drawPixmap(0, 0, src);
            painter.end();
            ui->label_24->setPixmap(rounded);
            ui->label_24->setStyleSheet("#label_24{border-radius: 100px;}");
        }
    }
}

void MainWindow::on_pushButton_pause_clicked()
{
    ui->pushButton_25->clicked(true);
}


void MainWindow::on_pushButton_next_clicked()
{
    ui->pushButton_25->clicked(true);ui->pushButton_25->clicked(false);
}

