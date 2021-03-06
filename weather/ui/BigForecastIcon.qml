import QtQuick 2.0
import WeatherWindowSettings 1.0
import FontSizes 1.0
import CommonSettings 1.0

Item {
    id: current
    property string topText: "20*"
    property string bottomText: "Mostly cloudy"
    property string weatherIcon: "01d"
    property real smallSide: (current.width < current.height ? current.width : current.height)

    Text {
        text: current.topText
        font.pointSize: FontSizes.largeFontSize
        color: CommonSettings.fontColor
        font.family: CommonSettings.themeFont
        anchors {
            top: current.top
            left: current.left
            topMargin: 5
            leftMargin: 5
        }
    }

    WeatherIcon {
        weatherIcon: current.weatherIcon
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -15
        width: current.smallSide
        height: current.smallSide
    }

    Text {
        text: current.bottomText
        font.pointSize: FontSizes.mediumFontSize
        font.family: CommonSettings.themeFont
        wrapMode: Text.WordWrap
        width: parent.width
        color: CommonSettings.fontColor

        horizontalAlignment: Text.AlignRight
        anchors {
            bottom: current.bottom
            right: current.right
            rightMargin: 5
        }
    }
}
