#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
#include <QString>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

class HttpAesRequest : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit HttpAesRequest(QNetworkAccessManager *parent = 0);
    ~HttpAesRequest();

    void sendPOST(QByteArray postData);

private:
    QNetworkRequest *request;
};
#endif // HTTPREQUEST_H
