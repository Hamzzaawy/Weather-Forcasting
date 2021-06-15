#include "downloader.h"
#include "backend.h"


Downloader::Downloader(QString stationx, QObject *parent) : QObject(parent), station(stationx)
{

    // Initialize manager ...
//    manager =  QNetworkAccessManager();

   // ... and connect the signal to the handler
    connect(&manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);

}

Downloader::~Downloader()
{
//    delete manager;
}


// this private function acquires the date and time using QTime and QData and adjust them to fit the 5 hours gab of readings in the open API servers as mentioned in the
// attached report
QString Downloader::getTimeDate()
{
    // reading the current time and data
    QDate cd = QDate::currentDate();
    QTime time = QTime::currentTime();
    int Hours = time.hour();
    // handling the issue of using the application in the first 5 hours of the day where when we subtract these 5 hours we move to a different day and
    // possibly a differen month. so we handle this point by taking care of which month we are in
    // this point don't handle the switching between years.
    if (Hours < 5)
    {
        int years = cd.year(),
            month = cd.month(),
            day   = cd.day();
        if (day==1)
        {
            if((month == 1) || (month == 2) || (month == 4) || (month == 6) || (month == 8) || (month == 9) || (month == 11))
            {
                day = 31;
            }
            else if(month == 3)
            {
                day = 28;
            }
            else
            {
                day = 30;
            }
            month--;
            cd.setDate(years, month, day);
        }

    }
    QString T = "T", zero = "0";
    QString H = QString::number(Hours-5);
    QString temp = ":00:00Z";
    if (Hours < 10)
    {
        QString ct = zero + T + H +temp;
    }
    else
    {
        QString ct = T + H +temp;
    }

    // concatinating the time part to suit the form required by the api
    QString ct = T + H +temp;

    // concatinating the time and data in a single return value that would be passed later to the api
    return (cd.toString(Qt::ISODate) + ct);

}

// this slot is triggered once the 60 seconds timeout signal is triggered and it makes an http request to the server to fetch the data as an xml file

void Downloader::getData()
{

    hamzawy = new QNetworkAccessManager();
    connect(hamzawy, &QNetworkAccessManager::finished, this, &Downloader::onResult);
    QString Time = getTimeDate();


    QString BaseUrl{"http://opendata.fmi.fi/wfs?service=WFS&version=2.0.0&request=getFeature&storedquery_id="};
    QString API{"fmi::observations::weather::timevaluepair"};

    QString StartTime = {"starttime="};
    QString EndTime = {"endtime="};
    QString Concatenate{"&"};
    QString QueryStation1 = BaseUrl + API + Concatenate + station + Concatenate + StartTime + Time + Concatenate + EndTime + Time ;

    QUrl url(QueryStation1);
    QNetworkRequest request;
    request.setUrl(url);
    manager.get(request);
}


// this slot is triggered by the onfinish signal from the network acess manger that notify this slot that the data is feteched and ready to be proccessed


inline bool isStartElementOfFirst(const QXmlStreamReader& xmlIterator) {
    return xmlIterator.isStartElement() && xmlIterator.name() == QString("MeasurementTVP");
}
inline bool isItemElement(const QXmlStreamReader& xmlIterator) {
    return xmlIterator.name() == QString("value") ;
}


void Downloader::onResult(QNetworkReply *reply)
{


    QXmlStreamReader xmlIterator(reply->readAll());
    QVector<QString> output;


    for(; !xmlIterator.atEnd(); xmlIterator.readNext()) {
        if(isStartElementOfFirst(xmlIterator)) {
            while(xmlIterator.readNextStartElement()) {
                if(isItemElement(xmlIterator))
                    output.append(xmlIterator.readElementText());
                else
                    xmlIterator.skipCurrentElement();
            }
        }
    }

    Temperature = output[0].toFloat();
    WindSpeed = output[1].toFloat();
    AirPressure = output[9].toFloat();
    emit DataReady();
}

