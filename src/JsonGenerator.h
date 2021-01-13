/*
 * Copyright (c) 2020-2021 Alex Spataru <https://github.com/alex-spataru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef JSON_GENERATOR_H
#define JSON_GENERATOR_H

#include <QFile>
#include <QObject>
#include <QSettings>
#include <QQmlEngine>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

class JsonGenerator : public QObject
{
    // clang-format off
    Q_OBJECT
    Q_PROPERTY(QString jsonMapFilename
               READ jsonMapFilename
               NOTIFY jsonFileMapChanged)
    Q_PROPERTY(QString jsonMapFilepath
               READ jsonMapFilepath
               NOTIFY jsonFileMapChanged)
    Q_PROPERTY(OperationMode operationMode
               READ operationMode
               WRITE setOperationMode
               NOTIFY operationModeChanged)
    // clang-format on

signals:
    void packetReceived();
    void jsonFileMapChanged();
    void operationModeChanged();

public:
    enum OperationMode
    {
        kManual = 0x00,
        kAutomatic = 0x01,
    };
    Q_ENUMS(OperationMode)

public:
    static JsonGenerator *getInstance();

    QString jsonMapData() const;
    QJsonDocument document() const;
    QString jsonMapFilename() const;
    QString jsonMapFilepath() const;
    OperationMode operationMode() const;

public slots:
    void loadJsonMap();
    void setOperationMode(const OperationMode mode);
    void loadJsonMap(const QString &path, const bool silent = false);

private:
    JsonGenerator();

public slots:
    void readSettings();
    void writeSettings(const QString &path);
    void setJsonDocument(const QJsonDocument &document);

private slots:
    void reset();
    void readData(const QByteArray &data);

private:
    QFile m_jsonMap;
    QSettings m_settings;
    QString m_jsonMapData;
    int m_dataFormatErrors;
    OperationMode m_opMode;
    QJsonDocument m_document;
};

#endif