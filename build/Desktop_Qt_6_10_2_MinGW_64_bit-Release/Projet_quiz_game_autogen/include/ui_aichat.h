/********************************************************************************
** Form generated from reading UI file 'aichat.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AICHAT_H
#define UI_AICHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AIchat
{
public:
    QLineEdit *messageEdit;
    QTextEdit *chatBox;
    QPushButton *screenshotButton;
    QPushButton *sendButton;

    void setupUi(QWidget *AIchat)
    {
        if (AIchat->objectName().isEmpty())
            AIchat->setObjectName("AIchat");
        AIchat->resize(400, 398);
        messageEdit = new QLineEdit(AIchat);
        messageEdit->setObjectName("messageEdit");
        messageEdit->setGeometry(QRect(10, 350, 381, 41));
        messageEdit->setStyleSheet(QString::fromUtf8("QLineEdit#messageEdit {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #dcdcdc;\n"
"    border-radius: 20px; /* Makes it pill-shaped and modern */\n"
"    padding: 8px 16px;padding-left:50px;padding-right:60px;\n"
"    font-family: \"Segoe UI\", Arial, sans-serif;\n"
"    font-size: 13px;\n"
"    color: #333333;\n"
"}\n"
"QLineEdit#messageEdit:focus {\n"
"    border: 1px solid #0078d4; /* Highlights blue when typing */\n"
"}"));
        chatBox = new QTextEdit(AIchat);
        chatBox->setObjectName("chatBox");
        chatBox->setGeometry(QRect(10, 10, 381, 331));
        chatBox->setStyleSheet(QString::fromUtf8("QTextBrowser, QTextEdit#chatBox {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #e0e0e0;\n"
"    border-radius: 8px;\n"
"    padding: 12px;\n"
"    font-family: \"Segoe UI\", Arial, sans-serif;\n"
"    font-size: 13px;\n"
"    color: #333333;\n"
"}\n"
"\n"
"\n"
"QScrollBar:vertical {\n"
"       background: transparent;\n"
"       width: 10px;\n"
"      margin: 4px 0px 4px 0px;\n"
"    }\n"
"    QScrollBar::handle:vertical {\n"
"       background: #C4C4C4;\n"
"       border-radius: 5px;\n"
"       min-height: 30px;\n"
"    }\n"
"    QScrollBar::handle:vertical:hover {\n"
"      background: #A0A0A0;\n"
"    }\n"
"    QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"       height: 0px;\n"
"    }\n"
"    QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
"       background: none;\n"
"    }"));
        screenshotButton = new QPushButton(AIchat);
        screenshotButton->setObjectName("screenshotButton");
        screenshotButton->setGeometry(QRect(10, 350, 51, 41));
        screenshotButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        screenshotButton->setStyleSheet(QString::fromUtf8("QPushButton#screenshotButton {\n"
"    background-color: rgba(15, 95, 105,0.88);\n"
"    border-radius: 20px; \n"
"    image:url(\"img/icon/camera1.png\");\n"
"    border:none;\n"
"}\n"
""));
        sendButton = new QPushButton(AIchat);
        sendButton->setObjectName("sendButton");
        sendButton->setGeometry(QRect(330, 350, 61, 41));
        sendButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        sendButton->setStyleSheet(QString::fromUtf8("QPushButton#sendButton {\n"
"    background-color: #0078d4; \n"
"    background-color: rgba(15, 95, 105,0.88);\n"
"    image:url(\"img/icon/send.png\");\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 20px; \n"
"    padding: 8px 20px;\n"
"    font-family: \"Segoe UI\", Arial, sans-serif;\n"
"    font-weight: bold;\n"
"    font-size: 10px;\n"
"}\n"
"QPushButton#sendButton:hover {\n"
"    background-color: #106ebe; \n"
"}\n"
"\n"
"QPushButton#sendButton:pressed {\n"
"    background-color: #005a9e;\n"
"}"));

        retranslateUi(AIchat);

        QMetaObject::connectSlotsByName(AIchat);
    } // setupUi

    void retranslateUi(QWidget *AIchat)
    {
        AIchat->setWindowTitle(QCoreApplication::translate("AIchat", "Form", nullptr));
        messageEdit->setPlaceholderText(QCoreApplication::translate("AIchat", "Type a message ...", nullptr));
        screenshotButton->setText(QString());
        sendButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AIchat: public Ui_AIchat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AICHAT_H
