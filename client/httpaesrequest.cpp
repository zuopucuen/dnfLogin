#include "httpaesrequest.h"
#include "aes_cbc.h"
#include "util.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QStringList>
#include <QCryptographicHash>

HttpAesRequest::HttpAesRequest(QNetworkAccessManager *parent) : QNetworkAccessManager(parent)
{
    request = new QNetworkRequest();

    request->setUrl(QUrl("http://103.37.162.118/dnflogin/dnf.php"));
    request->setRawHeader("Content-Type","application/x-www-form-urlencoded");

}

HttpAesRequest::~HttpAesRequest()
{

}

void HttpAesRequest::sendPOST(QByteArray postData)
{
    AES_CBC aes;
    QByteArray postMd5;

    postMd5 = QCryptographicHash::hash (
                          postData,
                          QCryptographicHash::Md5).toHex();

    postData.append("&");
    postData.append(postMd5);

    postData = aes.encrypt(postData);

    this->post(*request, postData);
}


