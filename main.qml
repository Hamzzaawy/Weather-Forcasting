import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    id: window
    width: 720
    height: 720
    visible: true
    color: "#5fe453"
    title: qsTr("QT Assignment")

    //    Backend{
    //        id: backend
    //    }

    // this part is resposable of updating the values of the qml items on the signal coming from the c++ part which is reigered once the data
    // is retrived and the xml data is parsed.
    Connections{
        target: backend
        onUpdateQML:{
            tOulun.text             = qsTr(backend.getTempOulunsalo())
            tSatama.text            = qsTr(backend.getTempSatama())
            tLentoasema.text        = qsTr(backend.getTempLentoasema())
            wOulun.text             = qsTr(backend.getWindOulunsalo())
            wSatama.text            = qsTr(backend.getWindSatama())
            wLentoasema.text        = qsTr(backend.getWindLentoasema())
            pOulun.text             = qsTr(backend.getAirPressureOulunsalo())
            pSatama.text            = qsTr(backend.getAirPressureSatama())
            pLentoasema.text        = qsTr(backend.getAirPressureSatama())
            highestTemp.text        = qsTr(backend.getHighestTemp())
            strongestWind.text      = qsTr(backend.getStrongestWind())
            lowestAirPressure.text  = qsTr(backend.getLowestAirPressure())

        }
        

    }
    ScrollView{
        anchors.fill: parent
        ColumnLayout{
            anchors.fill: parent
            spacing: 20
            Item{
                height: 37
                width:window.width
                Text {
                    id: text1
                    anchors.centerIn: parent
                    text: qsTr("Welcome To Oulu Qt-Forcasting System")
                    font.pixelSize: 24
                }

            }

            Item{
                id: item1
                height: window.height * 0.2
                width:window.width
                RowLayout {
                    height:window.height*0.25
                    anchors.centerIn: parent
                    spacing:40
                    Rectangle {
                        id: rectangle1
                        width: 150
                        height: 158
                        color: "#fffbfb"
                        Column{
                            anchors.topMargin: 25
                            anchors.fill: parent
                            spacing: 20

                            Text {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("Weather Stations")
                                font.pixelSize: 12

                            }

                            Text {
                                id: text2
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("Oulunsalo Pellonpää")
                                font.pixelSize: 12
                            }

                            Text {
                                id: text3
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("Vihreäsaari satama")
                                font.pixelSize: 12
                            }

                            Text {
                                id: text4
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("lentoasema")
                                font.pixelSize: 12
                            }
                        }


                    }



                    Rectangle {
                        id: rectangle2
                        width: 104
                        height: 158
                        color: "#fffbfb"

                        Column{
                            anchors.topMargin: 25
                            anchors.fill: parent
                            spacing: 20
                            Text {
                                id: text6
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("Temperature")
                                font.pixelSize: 12
                            }
                            Text {
                                id: tOulun
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr(backend.getTempOulunsalo())
                                font.pixelSize: 12
                            }
                            Text {
                                id: tSatama
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr(backend.getTempSatama())
                                font.pixelSize: 12
                            }
                            Text {
                                id: tLentoasema
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr(backend.getTempLentoasema())
                                font.pixelSize: 12
                            }

                        }

                    }

                    Rectangle {
                        id: rectangle3
                        width: 104
                        height: 158
                        color: "#fffbfb"

                        Column{
                            anchors.topMargin: 25
                            anchors.fill: parent
                            spacing: 20
                            Text {
                                id: text8
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("Wind Speed")
                                font.pixelSize: 12
                            }
                            Text {
                                id: wOulun
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("Text")
                                font.pixelSize: 12
                            }
                            Text {
                                id: wSatama
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("Text")
                                font.pixelSize: 12
                            }

                            Text {
                                id: wLentoasema
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("Text")
                                font.pixelSize: 12
                            }

                        }

                    }

                    Rectangle {
                        id: rectangle4
                        width: 104
                        height: 158
                        color: "#fffbfb"

                        Column{
                            anchors.topMargin: 25
                            anchors.fill: parent
                            spacing: 20
                            Text {
                                id: text9
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("Air Pressure")
                                font.pixelSize: 12
                            }
                            Text {
                                id: pOulun
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("Text")
                                font.pixelSize: 12
                            }
                            Text {
                                id: pSatama
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("Text")
                                font.pixelSize: 12
                            }
                            Text {
                                id: pLentoasema
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("Text")
                                font.pixelSize: 12
                            }

                        }

                    }
                }
            }
            Item {
                width: window.width
                height: window.height * 0.2

                RowLayout{
                    height:window.height*0.25
                    id: rowLayout
                    spacing: 20
                    anchors.centerIn: parent


                    Rectangle {
                        id: rectangle5
                        width: 183
                        height: 82
                        color: "#ffffff"
                        Column{
                            anchors.topMargin: 25
                            anchors.fill: parent
                            spacing: 20
                            Text {
                                id: text5
                                text: qsTr("Highest Temp")
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.pixelSize: 12
                            }
                            Text {
                                id: highestTemp
                                text: qsTr("Text")
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.pixelSize: 12
                            }
                        }
                    }

                    Rectangle {
                        id: rectangle6
                        width: 183
                        height: 82
                        color: "#ffffff"
                        Column{
                            anchors.topMargin: 25
                            anchors.fill: parent
                            spacing: 20
                            Text {
                                id: text7
                                text: qsTr("Strongest Wind")
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.pixelSize: 12
                            }
                            Text {
                                id: strongestWind
                                text: qsTr("Text")
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.pixelSize: 12
                            }

                        }



                    }

                    Rectangle {
                        id: rectangle7
                        height: 82
                        width:183
                        color: "#ffffff"
                        Column{
                            anchors.topMargin: 25
                            anchors.fill: parent
                            spacing: 20
                            Text {
                                id: text10
                                text: qsTr("Lowerst AirPressure")
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.pixelSize: 12
                            }
                            Text {
                                id: lowestAirPressure
                                text: qsTr("Text")
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.pixelSize: 12
                            }
                        }

                    }

                }

            }
            }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.33}
}
##^##*/
