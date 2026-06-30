/********************************************************************************
** Form generated from reading UI file 'first_game.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRST_GAME_H
#define UI_FIRST_GAME_H

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

class Ui_first_game
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *pushButton_8;
    QLabel *label_flag;
    QLabel *label_question;
    QPushButton *pushButton_next;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_option1;
    QPushButton *pushButton_option3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_option2;
    QPushButton *pushButton_option4;
    QLabel *label_time;
    QLabel *label_point;
    QLabel *label_question_number;
    QPushButton *pushButton_suppr;
    QPushButton *pushButton_reveal;
    QLabel *hiding;
    QPushButton *pushButton_time;
    QLabel *label;
    QPushButton *pushButton_AI;
    QWidget *page_result;
    QLabel *label_score;
    QLabel *label_image_score;
    QLabel *label_scoring;
    QPushButton *pushButton_play_again;

    void setupUi(QWidget *first_game)
    {
        if (first_game->objectName().isEmpty())
            first_game->setObjectName("first_game");
        first_game->resize(492, 498);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(first_game->sizePolicy().hasHeightForWidth());
        first_game->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(first_game);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(first_game);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        stackedWidget->setMinimumSize(QSize(0, 0));
        stackedWidget->setMaximumSize(QSize(16777215, 16777215));
        stackedWidget->setStyleSheet(QString::fromUtf8("#stackedWidget {\n"
"   width:100%;height:100%;\n"
"	border-image: url(img/icon/background_image_flag.png) 0 0 0 0 stretch stretch ;\n"
"}\n"
""));
        stackedWidget->setFrameShape(QFrame::Shape::NoFrame);
        stackedWidget->setFrameShadow(QFrame::Shadow::Plain);
        stackedWidget->setLineWidth(0);
        page = new QWidget();
        page->setObjectName("page");
        pushButton_8 = new QPushButton(page);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(-10, 0, 61, 51));
        pushButton_8->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_8->setStyleSheet(QString::fromUtf8("image: url(img/icon/ic/backiconic.png);\n"
"border-radius:10px;"));
        label_flag = new QLabel(page);
        label_flag->setObjectName("label_flag");
        label_flag->setGeometry(QRect(120, 110, 261, 141));
        sizePolicy1.setHeightForWidth(label_flag->sizePolicy().hasHeightForWidth());
        label_flag->setSizePolicy(sizePolicy1);
        label_flag->setStyleSheet(QString::fromUtf8("width:100px;height:200px;"));
        label_flag->setTextFormat(Qt::TextFormat::PlainText);
        label_flag->setScaledContents(true);
        label_question = new QLabel(page);
        label_question->setObjectName("label_question");
        label_question->setGeometry(QRect(-10, 30, 541, 81));
        sizePolicy1.setHeightForWidth(label_question->sizePolicy().hasHeightForWidth());
        label_question->setSizePolicy(sizePolicy1);
        label_question->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        label_question->setStyleSheet(QString::fromUtf8("font: 700 18pt \"Segoe UI\";\n"
"border-image: url(img/icon/ic/backgr_question.png) 0 0 0 0 stretch stretch;\n"
"color: black;\n"
"padding-left: 80px;\n"
"padding-right: 80px; "));
        label_question->setWordWrap(true);
        pushButton_next = new QPushButton(page);
        pushButton_next->setObjectName("pushButton_next");
        pushButton_next->setGeometry(QRect(450, 440, 41, 61));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_next->sizePolicy().hasHeightForWidth());
        pushButton_next->setSizePolicy(sizePolicy2);
        pushButton_next->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_next->setStyleSheet(QString::fromUtf8("image: url(img/icon/ic/next.png);\n"
"image: url(img/icon/ic/icon_next.png);\n"
"border-radius:30px;"));
        layoutWidget = new QWidget(page);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 280, 471, 191));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 0, -1, 0);
        pushButton_option1 = new QPushButton(layoutWidget);
        pushButton_option1->setObjectName("pushButton_option1");
        sizePolicy1.setHeightForWidth(pushButton_option1->sizePolicy().hasHeightForWidth());
        pushButton_option1->setSizePolicy(sizePolicy1);
        pushButton_option1->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_option1->setStyleSheet(QString::fromUtf8("#pushButton_option1{\n"
"   font: 900 15pt \"Segoe UI\";\n"
"  border-image: url(img/icon/ic/backgr_button.png) 0 0 0 0 scretch scretch;\n"
"  min-width: 20px;\n"
"  min-height: 20px;\n"
"  color: rgb(0, 0, 0);\n"
"  border-radius:18px;\n"
"}\n"
"#pushButton_option1:hover{\n"
"\n"
"  border-image: url(img/icon/ic/hoverbutton.png) 0 0 0 0 scretch scretch;\n"
"	\n"
"}\n"
"\n"
""));

        verticalLayout_2->addWidget(pushButton_option1);

        pushButton_option3 = new QPushButton(layoutWidget);
        pushButton_option3->setObjectName("pushButton_option3");
        sizePolicy1.setHeightForWidth(pushButton_option3->sizePolicy().hasHeightForWidth());
        pushButton_option3->setSizePolicy(sizePolicy1);
        pushButton_option3->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_option3->setStyleSheet(QString::fromUtf8("#pushButton_option3{\n"
"   font: 900 15pt \"Segoe UI\";\n"
"  border-image: url(img/icon/ic/backgr_button.png) 0 0 0 0 scretch scretch;\n"
"  min-width: 20px;\n"
"  min-height: 20px;\n"
"  color: rgb(0, 0, 0);\n"
"  border-radius:18px;\n"
"}\n"
"#pushButton_option3:hover{\n"
"\n"
"  border-image: url(img/icon/ic/hoverbutton.png) 0 0 0 0 scretch scretch;\n"
"	\n"
"}\n"
""));

        verticalLayout_2->addWidget(pushButton_option3);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(-1, 0, -1, 0);
        pushButton_option2 = new QPushButton(layoutWidget);
        pushButton_option2->setObjectName("pushButton_option2");
        sizePolicy1.setHeightForWidth(pushButton_option2->sizePolicy().hasHeightForWidth());
        pushButton_option2->setSizePolicy(sizePolicy1);
        pushButton_option2->setMinimumSize(QSize(20, 20));
        pushButton_option2->setMaximumSize(QSize(16777191, 16777185));
        pushButton_option2->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_option2->setStyleSheet(QString::fromUtf8("#pushButton_option2{\n"
"   font: 900 15pt \"Segoe UI\";\n"
"  border-image: url(img/icon/ic/backgr_button.png) 0 0 0 0 scretch scretch;\n"
"  min-width: 20px;\n"
"  min-height: 20px;\n"
"  color: rgb(0, 0, 0);\n"
"  border-radius:18px;\n"
"}\n"
"#pushButton_option2:hover{\n"
"\n"
"  border-image: url(img/icon/ic/hoverbutton.png) 0 0 0 0 scretch scretch;\n"
"	\n"
"}\n"
""));

        verticalLayout_4->addWidget(pushButton_option2);

        pushButton_option4 = new QPushButton(layoutWidget);
        pushButton_option4->setObjectName("pushButton_option4");
        sizePolicy1.setHeightForWidth(pushButton_option4->sizePolicy().hasHeightForWidth());
        pushButton_option4->setSizePolicy(sizePolicy1);
        pushButton_option4->setMinimumSize(QSize(20, 20));
        pushButton_option4->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_option4->setStyleSheet(QString::fromUtf8("#pushButton_option4{\n"
"   font: 900 15pt \"Segoe UI\";\n"
"  border-image: url(img/icon/ic/backgr_button.png) 0 0 0 0 scretch scretch;\n"
"  min-width: 20px;\n"
"  min-height: 20px;\n"
"  color: rgb(0, 0, 0);\n"
"  border-radius:18px;\n"
"}\n"
"#pushButton_option4:hover{\n"
"\n"
"  border-image: url(img/icon/ic/hoverbutton.png) 0 0 0 0 scretch scretch;\n"
"	\n"
"}"));

        verticalLayout_4->addWidget(pushButton_option4);


        horizontalLayout->addLayout(verticalLayout_4);

        label_time = new QLabel(page);
        label_time->setObjectName("label_time");
        label_time->setGeometry(QRect(20, 460, 61, 31));
        label_time->setStyleSheet(QString::fromUtf8("background-color:black;\n"
"font: 11pt \"Segoe UI\";\n"
"font: 700 9pt \"Segoe UI\";\n"
"border-image: url(img/icon/time/time_background.PNG);\n"
"color:white;\n"
"\n"
""));
        label_point = new QLabel(page);
        label_point->setObjectName("label_point");
        label_point->setGeometry(QRect(190, 470, 111, 21));
        label_point->setStyleSheet(QString::fromUtf8("font: 700 italic 11pt \"Segoe UI\";\n"
"border-image: url(img/icon/ic/backgr_point.png);\n"
"color:black;"));
        label_question_number = new QLabel(page);
        label_question_number->setObjectName("label_question_number");
        label_question_number->setGeometry(QRect(190, 10, 131, 31));
        label_question_number->setStyleSheet(QString::fromUtf8("font: 700 italic 11pt \"Segoe UI\";\n"
"border-image: url(img/icon/ic/backgr_point.png);\n"
"color:black;\n"
""));
        pushButton_suppr = new QPushButton(page);
        pushButton_suppr->setObjectName("pushButton_suppr");
        pushButton_suppr->setGeometry(QRect(320, 0, 61, 51));
        sizePolicy1.setHeightForWidth(pushButton_suppr->sizePolicy().hasHeightForWidth());
        pushButton_suppr->setSizePolicy(sizePolicy1);
        pushButton_suppr->setMinimumSize(QSize(20, 20));
        pushButton_suppr->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_suppr->setStyleSheet(QString::fromUtf8("#pushButton_suppr{\n"
"  image: url(img/icon/ic/5050.png)0 0 0 0 scretch  scretch;\n"
"  border-radius:18px;\n"
"}\n"
"#pushButton_suppr:hover{\n"
"image: url(img/icon/ic/5050_hover.png)0 0 0 0 scretch  scretch;\n"
"}"));
        pushButton_reveal = new QPushButton(page);
        pushButton_reveal->setObjectName("pushButton_reveal");
        pushButton_reveal->setGeometry(QRect(380, 0, 61, 51));
        sizePolicy1.setHeightForWidth(pushButton_reveal->sizePolicy().hasHeightForWidth());
        pushButton_reveal->setSizePolicy(sizePolicy1);
        pushButton_reveal->setMinimumSize(QSize(20, 20));
        pushButton_reveal->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_reveal->setStyleSheet(QString::fromUtf8("#pushButton_reveal{\n"
"  image: url(img/icon/ic/show.png)0 0 0 0 scretch  scretch;\n"
"  border-radius:18px;\n"
"}\n"
"#pushButton_reveal:hover{\n"
"image: url(img/icon/ic/show_hover.png)0 0 0 0 scretch  scretch;\n"
"}"));
        hiding = new QLabel(page);
        hiding->setObjectName("hiding");
        hiding->setGeometry(QRect(10, 240, 471, 61));
        hiding->setStyleSheet(QString::fromUtf8("#hiding{\n"
"	font: 700 12pt \"Segoe UI\";\n"
" background-color: rgb(255, 255, 255);\n"
"color:black;\n"
"}\n"
""));
        pushButton_time = new QPushButton(page);
        pushButton_time->setObjectName("pushButton_time");
        pushButton_time->setGeometry(QRect(110, 0, 61, 51));
        sizePolicy1.setHeightForWidth(pushButton_time->sizePolicy().hasHeightForWidth());
        pushButton_time->setSizePolicy(sizePolicy1);
        pushButton_time->setMinimumSize(QSize(20, 20));
        pushButton_time->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_time->setStyleSheet(QString::fromUtf8("#pushButton_time{\n"
"  image: url(img/icon/ic/time.png)0 0 0 0 scretch  scretch;\n"
"  border-radius:18px;\n"
"}\n"
"#pushButton_time:hover{\n"
"image: url(img/icon/ic/time_hover.png)0 0 0 0 scretch  scretch;\n"
"}"));
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(127, 18, 31, 16));
        label->setStyleSheet(QString::fromUtf8("font: 900 9pt \"Segoe UI\";\n"
"color:black;"));
        pushButton_AI = new QPushButton(page);
        pushButton_AI->setObjectName("pushButton_AI");
        pushButton_AI->setGeometry(QRect(50, 0, 61, 51));
        sizePolicy1.setHeightForWidth(pushButton_AI->sizePolicy().hasHeightForWidth());
        pushButton_AI->setSizePolicy(sizePolicy1);
        pushButton_AI->setMinimumSize(QSize(20, 20));
        pushButton_AI->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_AI->setStyleSheet(QString::fromUtf8("#pushButton_AI{\n"
"  image: url(img/icon/AI_h.png)0 0 0 0 scretch  scretch;\n"
"  border-radius:18px;\n"
"}\n"
""));
        stackedWidget->addWidget(page);
        page_result = new QWidget();
        page_result->setObjectName("page_result");
        label_score = new QLabel(page_result);
        label_score->setObjectName("label_score");
        label_score->setGeometry(QRect(50, 300, 421, 71));
        label_score->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Source Code Pro\";\n"
"/*border-image: url(img/icon/ic/score_stat.png) 0 0 0 0 scretch scretch;*/\n"
"border-image: url(img/icon/ic/score_stat.png) 0 0 0 0 scretch scretch;\n"
"/*padding-left: 50px;*/\n"
"padding-right: 60px; \n"
"color:white;\n"
"\n"
""));
        label_image_score = new QLabel(page_result);
        label_image_score->setObjectName("label_image_score");
        label_image_score->setGeometry(QRect(120, 70, 291, 251));
        label_image_score->setStyleSheet(QString::fromUtf8(""));
        label_scoring = new QLabel(page_result);
        label_scoring->setObjectName("label_scoring");
        label_scoring->setGeometry(QRect(0, 10, 511, 71));
        label_scoring->setStyleSheet(QString::fromUtf8("font: 700 18pt \"Segoe UI\";\n"
"border-image: url(img/icon/ic/backgr_question.png) 0 0 0 0 stretch stretch;\n"
"color: black;\n"
"padding-left: 80px;\n"
"padding-right: 80px; "));
        pushButton_play_again = new QPushButton(page_result);
        pushButton_play_again->setObjectName("pushButton_play_again");
        pushButton_play_again->setGeometry(QRect(100, 310, 291, 261));
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_play_again->sizePolicy().hasHeightForWidth());
        pushButton_play_again->setSizePolicy(sizePolicy3);
        pushButton_play_again->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton_play_again->setStyleSheet(QString::fromUtf8("border-image: url(img/icon/ic/refresh.png) 0 0 0 0 scretch scretch;\n"
"min-width: 20px;\n"
"min-height: 20px;\n"
""));
        stackedWidget->addWidget(page_result);
        pushButton_play_again->raise();
        label_score->raise();
        label_image_score->raise();
        label_scoring->raise();

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);


        retranslateUi(first_game);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(first_game);
    } // setupUi

    void retranslateUi(QWidget *first_game)
    {
        first_game->setWindowTitle(QCoreApplication::translate("first_game", "Form", nullptr));
        pushButton_8->setText(QString());
        label_flag->setText(QString());
        label_question->setText(QCoreApplication::translate("first_game", "                          TextLabel", nullptr));
        pushButton_next->setText(QString());
        pushButton_option1->setText(QString());
        pushButton_option3->setText(QString());
        pushButton_option2->setText(QString());
        pushButton_option4->setText(QString());
        label_time->setText(QCoreApplication::translate("first_game", "TextLabel", nullptr));
        label_point->setText(QCoreApplication::translate("first_game", "TextLabel", nullptr));
        label_question_number->setText(QCoreApplication::translate("first_game", "TextLabel", nullptr));
        pushButton_suppr->setText(QString());
        pushButton_reveal->setText(QString());
        hiding->setText(QCoreApplication::translate("first_game", "TextLabel", nullptr));
        pushButton_time->setText(QString());
        label->setText(QCoreApplication::translate("first_game", "+15", nullptr));
        pushButton_AI->setText(QString());
        label_score->setText(QCoreApplication::translate("first_game", "Too Bad!!", nullptr));
        label_image_score->setText(QString());
        label_scoring->setText(QCoreApplication::translate("first_game", "TextLabel", nullptr));
        pushButton_play_again->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class first_game: public Ui_first_game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRST_GAME_H
