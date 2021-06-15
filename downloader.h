#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>
#include <QXmlStreamReader>
#include <QString>
#include <QStringRef>
#include <QTime>
#include <QDate>




class Downloader : public QObject
{
    Q_OBJECT
public:

    explicit Downloader(QString  stationx, QObject *parent = 0);
    float Temperature,WindSpeed,AirPressure;
    ~Downloader();


signals:
    void DataReady();



public slots:
    void getData();
    void onResult(QNetworkReply *reply);

private:
    QNetworkAccessManager manager;
    QString station;
    QString getTimeDate();
    QNetworkAccessManager *hamzawy;
//    inline bool isItemElement(const QXmlStreamReader& xmlIterator);
//    inline bool isStartElementOfFirst(const QXmlStreamReader& xmlIterator);
//    QXmlStreamReader reader;
};


#endif // DOWNLOADER_H



