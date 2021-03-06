#include "CurrentWeatherParser.hpp"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>

CurrentWeatherParser::CurrentWeatherParser(QObject *parent) :
    QObject(parent)
{
}

WeatherDataCollection CurrentWeatherParser::parse(const QByteArray& data)
{
    auto json = QJsonDocument::fromJson(data);

    return {parseJsonObject(json.object())};
}

WeatherApiData CurrentWeatherParser::parseJsonObject(const QJsonObject& data)
{
    WeatherApiData weather;
    auto weatherInfo = data["weather"].toArray().first().toObject();

    QDateTime date = QDateTime::fromMSecsSinceEpoch(toMSSinceEpoch(data["dt"]));

    weather.dayOfTheWeek = date.date().toString(QStringLiteral("ddd"));
    weather.condition = weatherInfo["main"].toString();
    weather.description = weatherInfo["description"].toString();
    weather.weatherIcon = weatherInfo["icon"].toString();

    weather.temperature = static_cast<int>(data["main"]["temp"].toDouble());
    weather.temperatureMin = static_cast<int>(data["main"]["temp_min"].toDouble());
    weather.temperatureMax = static_cast<int>(data["main"]["temp_max"].toDouble());

    weather.pressure = data["main"]["pressure"].toInt();
    weather.humidity = data["main"]["humidity"].toInt();

    return weather;
}

qint64 CurrentWeatherParser::toMSSinceEpoch(QJsonValue&& value) const
{
    return static_cast<qint64>(value.toDouble() * 1000);
}
