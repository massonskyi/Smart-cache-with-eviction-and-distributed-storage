//
// Created by massonskyi on 23.10.24.
//

#ifndef CACHE_GUI_HPP
#define CACHE_GUI_HPP
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class CacheGUI : public QMainWindow {
    Q_OBJECT

public:
    CacheGUI(QWidget *parent = nullptr) : QMainWindow(parent) {
        auto *layout = new QVBoxLayout();
        auto *keyInput = new QLineEdit(this);
        auto *valueInput = new QLineEdit(this);
        auto *addButton = new QPushButton("Add to Cache", this);
        auto *output = new QTextEdit(this);

        layout->addWidget(keyInput);
        layout->addWidget(valueInput);
        layout->addWidget(addButton);
        layout->addWidget(output);

        connect(addButton, &QPushButton::clicked, this, [=]() {
            QString key = keyInput->text();
            QString value = valueInput->text();
            addToCache(key, value);
        });

        auto *centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);
    }

    private slots:
        void addToCache(const QString &key, const QString &value) {
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QNetworkRequest request(QUrl("http://localhost:8080")); // ваш API
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject json;
        json["key"] = key;
        json["value"] = value;

        manager->post(request, QJsonDocument(json).toJson());
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CacheGUI window;
    window.show();
    return app.exec();
}

#include "main.moc"

#endif //CACHE_GUI_HPP
