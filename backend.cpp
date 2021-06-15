#include "backend.h"
#include <QDebug>

Backend::Backend(QObject *parent) : QObject(parent)
{
    // creating a timer that we will use it's timeout signal to trigger the fetching of the data
    timer = new QTimer(this);

    // saving the ID of each station in a serperate value in order to pass it to each object we create for each station.
    QString Oulunsalo_ID{"fmisid=101799"}; // Oulu Oulunsalo Pellonpää
    QString Satama_ID{"fmisid=101794"}; // Oulu Vihreäsaari satama
    QString lentoasema_ID{"fmisid=101786"}; // Oulu lentoasema

    // create three objects of the Downloader class in order to allow its object to make an http requst using the api and the parmeter of each station seperatly.
    Oulunsalo_Downloader = new Downloader(Oulunsalo_ID);
    Satama_Downloader = new Downloader(Satama_ID);
    Lentoasema_Downloader = new Downloader(lentoasema_ID);

    // connect the timeout signal of the timer to each station's object slot that make the http request.
    connect(timer, SIGNAL(timeout()), Oulunsalo_Downloader, SLOT(getData()));
    connect(timer, SIGNAL(timeout()), Satama_Downloader, SLOT(getData()));
    connect(timer, SIGNAL(timeout()), Lentoasema_Downloader, SLOT(getData()));

    // connect the signal of data data ready that means that the data is featched, parsed and stored in each object varibales to the forward signal slot that is used to
    // signal the qml to update its values throug the updatQML signal.
    connect(Oulunsalo_Downloader, SIGNAL(DataReady()), this,SLOT(forwardSignal()) );

    timer->start(2000);
//    timer->start(60000);


}

// in this destructor we delete the objects created in the heap in order to prevent memory leakages
// i though about handling it better by making a sinlge object that have all the data of the three stations but at the end i think this way in better in making the
Backend::~Backend(){
    delete Oulunsalo_Downloader;
    delete Satama_Downloader;
    delete Lentoasema_Downloader;


}

// making getters slots that gets the values from each object private variables.
QString Backend::getTempOulunsalo()
{
    QString test;

    return test.setNum(Oulunsalo_Downloader->Temperature);
}

QString Backend::getTempSatama()
{
    QString test;
    return test.setNum(Satama_Downloader->Temperature);
}

QString Backend::getTempLentoasema()
{
    QString test;
    return test.setNum(Lentoasema_Downloader->Temperature);
}

QString Backend::getWindOulunsalo()
{
    QString test;
    return test.setNum(Oulunsalo_Downloader->WindSpeed);

}

QString Backend::getWindSatama()
{
    QString test;
    return test.setNum(Satama_Downloader->WindSpeed);
}

QString Backend::getWindLentoasema()
{
    QString test;
    return test.setNum(Lentoasema_Downloader->WindSpeed);

}

QString Backend::getAirPressureOulunsalo()
{
    QString test;
    return test.setNum(Oulunsalo_Downloader->AirPressure);
}

QString Backend::getAirPressureSatama()
{
    QString test;
    return test.setNum(Satama_Downloader->AirPressure);

}

QString Backend::getAirPressureLentoasema()
{
    QString test;
    return test.setNum(Lentoasema_Downloader->AirPressure);
}


// calculate which station has the strongest windspeed and return back the name of the station to the qml to display in its items
QString Backend::getStrongestWind()
{
    QString output;
    float Max = max(Oulunsalo_Downloader->WindSpeed, Satama_Downloader->WindSpeed, Lentoasema_Downloader->WindSpeed);
    if (Max == Oulunsalo_Downloader->WindSpeed)
    {
        return "Oulunsalo Pellonpää";
    }
    else if (Max == Satama_Downloader->WindSpeed)
    {
        return "Vihreäsaari satama";
    }
    else
    {
        return "lentoasema";
    }


}

QString Backend::getLowestAirPressure()
{
    float Max = max(Oulunsalo_Downloader->AirPressure, Satama_Downloader->AirPressure, Lentoasema_Downloader->AirPressure);
    if (Max == Oulunsalo_Downloader->AirPressure)
    {
        return "Oulunsalo Pellonpää";
    }
    else if (Max == Satama_Downloader->AirPressure)
    {
        return "Vihreäsaari satama";
    }
    else
    {
        return "lentoasema";
    }

}

QString Backend::getHighestTemp()
{
    float Max = max(Oulunsalo_Downloader->Temperature, Satama_Downloader->Temperature, Lentoasema_Downloader->Temperature);
    if (Max == Oulunsalo_Downloader->Temperature)
    {
        return "Oulunsalo Pellonpää";
    }
    else if (Max == Satama_Downloader->Temperature)
    {
        return "Vihreäsaari satama";
    }
    else
    {
        return "lentoasema";
    }

}

// slot that used to signal the qml with the updataQML signal.
void Backend::forwardSignal()
{
    emit updateQML();
}


// functions that clculate the max and min between three values.
float Backend::max(float a, float b, float c)
{
    float max=0;
    if (a>b)
    {
        max = a;
        if (c > a)
        {
            max = c;
        }
    }
    else
    {
        max = b;
        if(c>b)
        {
            max = c;
        }
    }
    return max;
}


float Backend::min(float a, float b, float c)
{
    float min=0;
    if (a<b)
    {
        min = a;
        if (c < a)
        {
            min = c;
        }
    }
    else
    {
        min = b;
        if(c < b)
        {
            min = c;
        }
    }
    return min;
}
