#include "aichat.h"
#include "ui_aichat.h"


static const QString GROQ_API_KEY = "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";
AIchat::AIchat(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AIchat)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(ui->sendButton,
            &QPushButton::clicked,
            this,
            &AIchat::sendMessage);

    ui->chatBox->setReadOnly(true);
    ui->chatBox->setTextInteractionFlags(Qt::TextSelectableByMouse);

    // System prompt: tells the AI what app it's in and how to behave
    QJsonObject systemMsg;
    systemMsg["role"] = "system";
    systemMsg["content"] =
        "You are the built-in AI assistant inside a desktop application called "
        "'Quiz Game' built with Qt/C++. You help the user with questions about "
        "general topics, and if asked about the app itself, explain that it's a "
        "quiz/chat application they're using right now. Be concise and friendly,this app is build by ILYASS BENHADI"
        "the app contain more that +1000questions and we have different categorie flag game/mondial game/food game/world quiz/morocco quiz"
        "the app contain 23 poem to listen you can switch between them."
        "and the app contain arabic/english"
        "every category contain quick game(10 questions)/ long game (50 questions)/challenge game(20 questions) that have difficulty increase easy medium hard very hard and if you win you have a bonus in the final /custom game to chose numbers of questions and temps questions";
    conversationHistory.append(systemMsg);
}

AIchat::~AIchat()
{
    delete ui;
}
///AI chat
void AIchat::sendMessage()
{
    QString message = ui->messageEdit->text().trimmed();
    if (message.isEmpty())
        return;


    QString userHtml =
        "<table width='100%' cellspacing='0' cellpadding='0'><tr>"
        "  <td></td>"
        "  <td align='right'>"
        "    <table cellpadding='10' cellspacing='0' style='background-color:#B7E4C7; border-radius:10px;'>"
        "      <tr><td>"
        "        <b>You</b><br/>"
        + message.toHtmlEscaped().replace("\n", "<br/>") +
        "      </td></tr>"
        "    </table>"
        "  </td>"
        "</tr></table>"
        "<br/>";
    ui->chatBox->append(userHtml);
    ui->messageEdit->clear();

    QNetworkRequest request(QUrl("https://api.groq.com/openai/v1/chat/completions"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + GROQ_API_KEY).toUtf8());

    QJsonObject userMsg;
    userMsg["role"] = "user";
    userMsg["content"] = message;
    conversationHistory.append(userMsg);

    QJsonObject body;
    body["model"] = "llama-3.1-8b-instant";
    body["messages"] = conversationHistory;

    QNetworkReply *reply = manager->post(request, QJsonDocument(body).toJson());

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();

        if (reply->error() != QNetworkReply::NoError) {
            QString errorHtml =
                "<div style='margin-bottom: 14px; text-align: center;'>"
                "  <div style='display: inline-block; background-color: #FBE0E0; "
                "              color: #B00020; border-radius: 10px; padding: 8px 14px; "
                "              font-family: sans-serif; font-size: 12px;'>"
                "    Error: " + reply->errorString().toHtmlEscaped() +
                "  </div>"
                "</div>";
            ui->chatBox->append(errorHtml);
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray choices = doc.object().value("choices").toArray();
        if (choices.isEmpty()) return;

        QString answer = choices[0].toObject()
                             .value("message").toObject()
                             .value("content").toString();


        QJsonObject aiMsg;
        aiMsg["role"] = "assistant";
        aiMsg["content"] = answer;
        conversationHistory.append(aiMsg);

        QString aiHtml =
            "<table width='100%' cellspacing='0' cellpadding='0'><tr>"
            "  <td align='left'>"
            "    <table cellpadding='10' cellspacing='0' style='background-color:#E8E8E8; border-radius:10px;'>"
            "      <tr><td>"
            "        <b>AI</b><br/>"
            + answer.toHtmlEscaped().replace("\n", "<br/>") +
            "      </td></tr>"
            "    </table>"
            "  </td>"
            "  <td></td>"
            "</tr></table>"
            "<br/>";
        ui->chatBox->append(aiHtml);
    });
}
