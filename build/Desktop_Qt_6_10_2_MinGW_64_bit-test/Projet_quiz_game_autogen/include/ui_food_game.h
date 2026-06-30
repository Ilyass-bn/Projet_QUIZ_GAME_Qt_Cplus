/********************************************************************************
** Form generated from reading UI file 'food_game.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOOD_GAME_H
#define UI_FOOD_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_food_game
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page_2;
    QPushButton *pushButton_8;
    QLabel *label_flag;
    QLabel *label_question;
    QPushButton *pushButton_next;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_option1;
    QPushButton *pushButton_option3;
    QVBoxLayout *verticalLayout_5;
    QPushButton *pushButton_option2;
    QPushButton *pushButton_option4;
    QLabel *label_time;
    QLabel *label_flag_2;
    QLabel *label_point;
    QLabel *label_question_number;
    QPushButton *pushButton_suppr;
    QPushButton *pushButton_reveal;
    QLabel *hiding;
    QPushButton *pushButton_time;
    QPushButton *pushButton_AI;
    QWidget *page_result_2;
    QLabel *label_score_food;
    QLabel *label_image_score;
    QLabel *label_scoring;
    QPushButton *pushButton_play_again;

    void setupUi(QWidget *food_game)
    {
        if (food_game->objectName().isEmpty())
            food_game->setObjectName("food_game");
        food_game->resize(506, 500);
        gridLayout = new QGridLayout(food_game);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(food_game);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setMinimumSize(QSize(0, 0));
        stackedWidget->setMaximumSize(QSize(16777215, 16777215));
        stackedWidget->setStyleSheet(QString::fromUtf8("#stackedWidget {\n"
"    border-image: url(img/icon/backgr_food.png)0 0 0 0 stretch stretch ;\n"
"    width:100%;height:100%;\n"
"	\n"
"}\n"
""));
        stackedWidget->setFrameShape(QFrame::Shape::NoFrame);
        stackedWidget->setFrameShadow(QFrame::Shadow::Plain);
        stackedWidget->setLineWidth(0);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        pushButton_8 = new QPushButton(page_2);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(0, 0, 51, 51));
        pushButton_8->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_8->setStyleSheet(QString::fromUtf8("image: url(img/icon/ic/food_icon/back_food.png);\n"
"border-radius:10px;"));
        label_flag = new QLabel(page_2);
        label_flag->setObjectName("label_flag");
        label_flag->setGeometry(QRect(110, 110, 301, 181));
        sizePolicy.setHeightForWidth(label_flag->sizePolicy().hasHeightForWidth());
        label_flag->setSizePolicy(sizePolicy);
        label_flag->setStyleSheet(QString::fromUtf8("border-image: url(img/icon/ic/food_icon/backgr_image.png);\n"
"border-radius:30px;\n"
"width:100px;height:200px;"));
        label_flag->setTextFormat(Qt::TextFormat::PlainText);
        label_flag->setScaledContents(true);
        label_question = new QLabel(page_2);
        label_question->setObjectName("label_question");
        label_question->setGeometry(QRect(-20, 20, 541, 111));
        sizePolicy.setHeightForWidth(label_question->sizePolicy().hasHeightForWidth());
        label_question->setSizePolicy(sizePolicy);
        label_question->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        label_question->setStyleSheet(QString::fromUtf8("\n"
"#label_question{\n"
"font: 700 15pt \"Segoe UI\";\n"
"border-image: url(img/icon/ic/food_icon/backgr_question.png) 0 0 0 0 stretch stretch;\n"
"color: black;\n"
"padding-left:120px;\n"
"padding-right:80px;\n"
"}\n"
""));
        label_question->setWordWrap(true);
        pushButton_next = new QPushButton(page_2);
        pushButton_next->setObjectName("pushButton_next");
        pushButton_next->setGeometry(QRect(450, 450, 41, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_next->sizePolicy().hasHeightForWidth());
        pushButton_next->setSizePolicy(sizePolicy1);
        pushButton_next->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_next->setStyleSheet(QString::fromUtf8("image: url(img/icon/ic/food_icon/button_next_food.png);\n"
"border-radius:30px;"));
        layoutWidget_2 = new QWidget(page_2);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(40, 310, 441, 141));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(-1, 0, -1, 0);
        pushButton_option1 = new QPushButton(layoutWidget_2);
        pushButton_option1->setObjectName("pushButton_option1");
        sizePolicy.setHeightForWidth(pushButton_option1->sizePolicy().hasHeightForWidth());
        pushButton_option1->setSizePolicy(sizePolicy);
        pushButton_option1->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_option1->setStyleSheet(QString::fromUtf8("#pushButton_option1{\n"
"   font: 900 15pt \"Segoe UI\";\n"
"  border-image: url(img/icon/ic/food_icon/backgr_button.png) 0 0 0 0 scretch  scretch;\n"
"  min-width: 20px;\n"
"  min-height: 20px;\n"
"  color: rgb(0, 0, 0);\n"
"  border-radius:18px;\n"
"}\n"
"#pushButton_option1:hover{\n"
"\n"
"    border-image:url(img/icon/ic/food_icon/backgr_button1_hover.png) 0 0 0 0 scretch scretch;\n"
"	\n"
"}\n"
"\n"
""));

        verticalLayout_3->addWidget(pushButton_option1);

        pushButton_option3 = new QPushButton(layoutWidget_2);
        pushButton_option3->setObjectName("pushButton_option3");
        sizePolicy.setHeightForWidth(pushButton_option3->sizePolicy().hasHeightForWidth());
        pushButton_option3->setSizePolicy(sizePolicy);
        pushButton_option3->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_option3->setStyleSheet(QString::fromUtf8("#pushButton_option3{\n"
"   font: 900 15pt \"Segoe UI\";\n"
"  border-image: url(img/icon/ic/food_icon/backgr_button.png) 0 0 0 0 scretch  scretch;\n"
"  min-width: 20px;\n"
"  min-height: 20px;\n"
"  color: rgb(0, 0, 0);\n"
"  border-radius:18px;\n"
"}\n"
"#pushButton_option3:hover{\n"
"\n"
"border-image:url(img/icon/ic/food_icon/backgr_button1_hover.png) 0 0 0 0 scretch scretch;\n"
"	\n"
"}\n"
""));

        verticalLayout_3->addWidget(pushButton_option3);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(-1, 0, -1, 0);
        pushButton_option2 = new QPushButton(layoutWidget_2);
        pushButton_option2->setObjectName("pushButton_option2");
        sizePolicy.setHeightForWidth(pushButton_option2->sizePolicy().hasHeightForWidth());
        pushButton_option2->setSizePolicy(sizePolicy);
        pushButton_option2->setMinimumSize(QSize(20, 20));
        pushButton_option2->setMaximumSize(QSize(16777191, 16777185));
        pushButton_option2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_option2->setStyleSheet(QString::fromUtf8("#pushButton_option2{\n"
"  font: 900 15pt \"Segoe UI\";\n"
"  border-image: url(img/icon/ic/food_icon/backgr_button.png) 0 0 0 0 scretch  scretch;\n"
"  min-width: 20px;\n"
"  min-height: 20px;\n"
"  color: rgb(0, 0, 0);\n"
"  border-radius:18px;\n"
"}\n"
"#pushButton_option2:hover{\n"
"\n"
"  border-image:url(img/icon/ic/food_icon/backgr_button1_hover.png) 0 0 0 0 scretch scretch;\n"
" \n"
"}\n"
""));

        verticalLayout_5->addWidget(pushButton_option2);

        pushButton_option4 = new QPushButton(layoutWidget_2);
        pushButton_option4->setObjectName("pushButton_option4");
        sizePolicy.setHeightForWidth(pushButton_option4->sizePolicy().hasHeightForWidth());
        pushButton_option4->setSizePolicy(sizePolicy);
        pushButton_option4->setMinimumSize(QSize(20, 20));
        pushButton_option4->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_option4->setStyleSheet(QString::fromUtf8("#pushButton_option4{\n"
"   font: 900 15pt \"Segoe UI\";\n"
"  border-image: url(img/icon/ic/food_icon/backgr_button.png) 0 0 0 0 scretch  scretch;\n"
"  min-width: 20px;\n"
"  min-height: 20px;\n"
"  color: rgb(0, 0, 0);\n"
"  border-radius:18px;\n"
"}\n"
"#pushButton_option4:hover{\n"
"\n"
"border-image:url(img/icon/ic/food_icon/backgr_button1_hover.png) 0 0 0 0 scretch scretch;\n"
"	\n"
"}"));

        verticalLayout_5->addWidget(pushButton_option4);


        horizontalLayout_2->addLayout(verticalLayout_5);

        label_time = new QLabel(page_2);
        label_time->setObjectName("label_time");
        label_time->setGeometry(QRect(20, 460, 61, 31));
        label_time->setStyleSheet(QString::fromUtf8("background-color:black;\n"
"color:black;\n"
"font: 11pt \"Segoe UI\";\n"
"font: 700 9pt \"Segoe UI\";\n"
"\n"
"background-image: url(img/icon/ic/food_icon/backgr_question1.png);\n"
"\n"
"\n"
""));
        label_flag_2 = new QLabel(page_2);
        label_flag_2->setObjectName("label_flag_2");
        label_flag_2->setGeometry(QRect(100, 100, 321, 201));
        sizePolicy.setHeightForWidth(label_flag_2->sizePolicy().hasHeightForWidth());
        label_flag_2->setSizePolicy(sizePolicy);
        label_flag_2->setStyleSheet(QString::fromUtf8("border-image: url(:/ic/img/icon/ic/food_icon/backgr_image.png);\n"
"width:100px;height:200px;"));
        label_flag_2->setTextFormat(Qt::TextFormat::PlainText);
        label_flag_2->setScaledContents(true);
        label_point = new QLabel(page_2);
        label_point->setObjectName("label_point");
        label_point->setGeometry(QRect(220, 460, 91, 31));
        label_point->setStyleSheet(QString::fromUtf8("#label_point{\n"
"color:black;\n"
"\n"
"background-color:black;\n"
"font: 700 13pt \"Segoe UI\";\n"
"\n"
"background-image: url(img/icon/ic/food_icon/backgr_question1.png);\n"
"\n"
"}\n"
"\n"
""));
        label_question_number = new QLabel(page_2);
        label_question_number->setObjectName("label_question_number");
        label_question_number->setGeometry(QRect(210, 10, 111, 31));
        label_question_number->setStyleSheet(QString::fromUtf8("background-color:black;\n"
"background-image: url(img/icon/ic/food_icon/backgr_question1.png);\n"
"\n"
"font: 700 13pt \"Segoe UI\";\n"
"color:black;\n"
"\n"
"\n"
""));
        pushButton_suppr = new QPushButton(page_2);
        pushButton_suppr->setObjectName("pushButton_suppr");
        pushButton_suppr->setGeometry(QRect(330, 0, 61, 51));
        sizePolicy.setHeightForWidth(pushButton_suppr->sizePolicy().hasHeightForWidth());
        pushButton_suppr->setSizePolicy(sizePolicy);
        pushButton_suppr->setMinimumSize(QSize(20, 20));
        pushButton_suppr->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_suppr->setStyleSheet(QString::fromUtf8("#pushButton_suppr{\n"
"  image: url(img/icon/ic/food_icon/5050.png)0 0 0 0 scretch  scretch;\n"
"  border-radius:18px;\n"
"}\n"
"#pushButton_suppr:hover{\n"
"image: url(img/icon/ic/food_icon/5050_hover.png)0 0 0 0 scretch  scretch;\n"
"}"));
        pushButton_reveal = new QPushButton(page_2);
        pushButton_reveal->setObjectName("pushButton_reveal");
        pushButton_reveal->setGeometry(QRect(383, 0, 61, 51));
        sizePolicy.setHeightForWidth(pushButton_reveal->sizePolicy().hasHeightForWidth());
        pushButton_reveal->setSizePolicy(sizePolicy);
        pushButton_reveal->setMinimumSize(QSize(20, 20));
        pushButton_reveal->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_reveal->setStyleSheet(QString::fromUtf8("#pushButton_reveal{\n"
"  image: url(img/icon/ic/food_icon/show.png)0 0 0 0 scretch  scretch;\n"
"  border-radius:18px;\n"
"}\n"
"#pushButton_reveal:hover{\n"
"image: url(img/icon/ic/food_icon/show_hover.png)0 0 0 0 scretch  scretch;\n"
"}"));
        hiding = new QLabel(page_2);
        hiding->setObjectName("hiding");
        hiding->setGeometry(QRect(10, 250, 471, 61));
        hiding->setStyleSheet(QString::fromUtf8("#hiding{\n"
"	font: 700 12pt \"Segoe UI\";\n"
" background-color: rgb(255, 255, 255);\n"
"color:black;\n"
"}\n"
""));
        pushButton_time = new QPushButton(page_2);
        pushButton_time->setObjectName("pushButton_time");
        pushButton_time->setGeometry(QRect(130, 2, 61, 51));
        sizePolicy.setHeightForWidth(pushButton_time->sizePolicy().hasHeightForWidth());
        pushButton_time->setSizePolicy(sizePolicy);
        pushButton_time->setMinimumSize(QSize(20, 20));
        pushButton_time->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_time->setStyleSheet(QString::fromUtf8("#pushButton_time{\n"
"  image: url(img/icon/ic/food_icon/time.png)0 0 0 0 scretch  scretch;\n"
"  border-radius:18px;\n"
"}\n"
"#pushButton_time:hover{\n"
"image: url(img/icon/ic/food_icon/time_hover.png)0 0 0 0 scretch  scretch;\n"
"}"));
        pushButton_AI = new QPushButton(page_2);
        pushButton_AI->setObjectName("pushButton_AI");
        pushButton_AI->setGeometry(QRect(50, 0, 61, 51));
        sizePolicy.setHeightForWidth(pushButton_AI->sizePolicy().hasHeightForWidth());
        pushButton_AI->setSizePolicy(sizePolicy);
        pushButton_AI->setMinimumSize(QSize(20, 20));
        pushButton_AI->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_AI->setStyleSheet(QString::fromUtf8("#pushButton_AI{\n"
"  image: url(img/icon/AI.png)0 0 0 0 scretch  scretch;\n"
"  border-radius:18px;\n"
"}\n"
""));
        stackedWidget->addWidget(page_2);
        label_question->raise();
        label_flag_2->raise();
        pushButton_8->raise();
        label_flag->raise();
        pushButton_next->raise();
        layoutWidget_2->raise();
        label_time->raise();
        label_point->raise();
        label_question_number->raise();
        pushButton_suppr->raise();
        pushButton_reveal->raise();
        hiding->raise();
        pushButton_time->raise();
        pushButton_AI->raise();
        page_result_2 = new QWidget();
        page_result_2->setObjectName("page_result_2");
        label_score_food = new QLabel(page_result_2);
        label_score_food->setObjectName("label_score_food");
        label_score_food->setGeometry(QRect(40, 300, 441, 71));
        label_score_food->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Source Code Pro\";\n"
"border-image: url(img/icon/ic/score_stat.png) 0 0 0 0 scretch scretch;\n"
"border-image: url(img/icon/ic/food_icon/backgr_question1.png) 0 0 0 0 scretch scretch;\n"
"/*padding-left: 20px;*/\n"
"padding-right: 60px; \n"
"color:white;\n"
"color:black;"));
        label_image_score = new QLabel(page_result_2);
        label_image_score->setObjectName("label_image_score");
        label_image_score->setGeometry(QRect(140, 60, 301, 271));
        label_image_score->setStyleSheet(QString::fromUtf8("width:100px;height:200px;"));
        label_scoring = new QLabel(page_result_2);
        label_scoring->setObjectName("label_scoring");
        label_scoring->setGeometry(QRect(30, 10, 451, 51));
        label_scoring->setStyleSheet(QString::fromUtf8("font: 700 18pt \"Segoe UI\";\n"
"border-image: url(img/icon/ic/food_icon/backgr_question1.png) 0 0 0 0 scretch scretch;\n"
"color: black;\n"
"padding-left: 80px;\n"
"padding-right: 80px; "));
        pushButton_play_again = new QPushButton(page_result_2);
        pushButton_play_again->setObjectName("pushButton_play_again");
        pushButton_play_again->setGeometry(QRect(120, 370, 251, 141));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_play_again->sizePolicy().hasHeightForWidth());
        pushButton_play_again->setSizePolicy(sizePolicy2);
        pushButton_play_again->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_play_again->setStyleSheet(QString::fromUtf8("#pushButton_play_again{\n"
"image: url(img/icon/ic/food_icon/mainwindown_food.png) ;\n"
"min-width: 20px;\n"
"min-height: 20px;\n"
"border-radius:20px;\n"
"}\n"
"\n"
"#pushButton_play_again:hover{\n"
"	image: url(img/icon/ic/food_icon/mainwindown_food_hover.png);\n"
"min-width: 20px;\n"
"min-height: 20px;\n"
"border-radius:20px;\n"
"}\n"
"\n"
""));
        stackedWidget->addWidget(page_result_2);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);


        retranslateUi(food_game);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(food_game);
    } // setupUi

    void retranslateUi(QWidget *food_game)
    {
        food_game->setWindowTitle(QCoreApplication::translate("food_game", "Form", nullptr));
        pushButton_8->setText(QString());
        label_flag->setText(QString());
        label_question->setText(QCoreApplication::translate("food_game", "                          TextLabel", nullptr));
        pushButton_next->setText(QString());
        pushButton_option1->setText(QString());
        pushButton_option3->setText(QString());
        pushButton_option2->setText(QString());
        pushButton_option4->setText(QString());
        label_time->setText(QCoreApplication::translate("food_game", "TextLabel", nullptr));
        label_flag_2->setText(QString());
        label_point->setText(QCoreApplication::translate("food_game", "TextLabel", nullptr));
        label_question_number->setText(QCoreApplication::translate("food_game", "TextLabel", nullptr));
        pushButton_suppr->setText(QString());
        pushButton_reveal->setText(QString());
        hiding->setText(QCoreApplication::translate("food_game", "TextLabel", nullptr));
        pushButton_time->setText(QString());
        pushButton_AI->setText(QString());
        label_score_food->setText(QCoreApplication::translate("food_game", "Too Bad!!", nullptr));
        label_image_score->setText(QString());
        label_scoring->setText(QCoreApplication::translate("food_game", "TextLabel", nullptr));
        pushButton_play_again->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class food_game: public Ui_food_game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOOD_GAME_H
