/* Copyright (c) 2010, Antonie Jovanoski
 *
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contact e-mail: Antonie Jovanoski <minimoog77_at_gmail.com>
 */

#include <QNetworkRequest>
#include <QNetworkReply>
#include "qtweetlistdeletemember.h"
#include "qtweetlist.h"

QTweetListDeleteMember::QTweetListDeleteMember(QObject *parent) :
    QTweetNetBase(parent)
{
}

QTweetListDeleteMember::QTweetListDeleteMember(OAuthTwitter *oauthTwitter, QObject *parent) :
        QTweetNetBase(oauthTwitter, parent)
{
}

/*!
    \param user User id (owner of the list
    \param list List id
    \param member User id of the list member to remove
 */
void QTweetListDeleteMember::remove(qint64 user, qint64 list, qint64 member)
{
    Q_ASSERT(oauthTwitter() != 0);

    QUrl url(QString("http://api.twitter.com/1/%1/%2/members.json").arg(user).arg(list));

    url.addQueryItem("id", QString::number(member));

    QNetworkRequest req(url);

    QByteArray oauthHeader = oauthTwitter()->generateAuthorizationHeader(url, OAuth::DELETE);
    req.setRawHeader(AUTH_HEADER, oauthHeader);

    QNetworkReply *reply = oauthTwitter()->networkAccessManager()->deleteResource(req);
    connect(reply, SIGNAL(finished()), this, SLOT(reply()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error()));
}

void QTweetListDeleteMember::parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg)
{
    if (ok) {
        QTweetList list = variantMapToTweetList(json.toMap());

        emit parsedList(list);
    } else {
        qDebug() << "QTweetListDeleteMember parser error: " << errorMsg;
    }
}

void QTweetListDeleteMember::error()
{
    // ### TODO:
}
