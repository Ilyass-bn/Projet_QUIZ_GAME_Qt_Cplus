#ifndef AICHAT_H
#define AICHAT_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QScreen>
#include <QGuiApplication>
#include <QBuffer>
#include <QFileDialog>
namespace Ui {
class AIchat;
}

class AIchat : public QWidget
{
    Q_OBJECT

public:
    explicit AIchat(QWidget *parent = nullptr);
    ~AIchat();
private slots:
    void sendMessage();
    void sendScreenshot();
private:
    Ui::AIchat *ui;
    QNetworkAccessManager *manager;
    QJsonArray conversationHistory;
};

#endif // AICHAT_H
