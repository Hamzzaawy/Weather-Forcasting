#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <downloader.h>
#include <QTimer>


class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);
    ~Backend();



signals:
    void updateQML();

public slots:
     QString getTempOulunsalo();
     QString getTempSatama();
     QString getTempLentoasema();
     QString getWindOulunsalo();
     QString getWindSatama();
     QString getWindLentoasema();
     QString getAirPressureOulunsalo();
     QString getAirPressureSatama();
     QString getAirPressureLentoasema();
     QString getHighestTemp();
     QString getStrongestWind();
     QString getLowestAirPressure();
    void forwardSignal();




private:
    QTimer *timer;
    Downloader * Oulunsalo_Downloader;
    Downloader * Satama_Downloader;
    Downloader * Lentoasema_Downloader;
    float max (float a, float b, float c);
    float min (float a, float b, float c);

};

#endif // BACKEND_H
