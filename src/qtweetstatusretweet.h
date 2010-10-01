/* Copyright (c) 2010, Antonie Jovanoski
 *
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *
 * Contact e-mail: Antonie Jovanoski <minimoog77_at_gmail.com>
 */

#ifndef QTWEETSTATUSRETWEET_H
#define QTWEETSTATUSRETWEET_H

#include "qtweetnetbase.h"

/*!
    Class for retweeting tweet
 */
class QTWEETLIBSHARED_EXPORT QTweetStatusRetweet : public QTweetNetBase
{
    Q_OBJECT
public:
    QTweetStatusRetweet(QObject *parent = 0);
    QTweetStatusRetweet(OAuthTwitter *oauthTwitter, QObject *parent = 0);
    void retweet(qint64 id,
                 bool trimUser = false,
                 bool includeEntities = false);

signals:
    void postedRetweet(const QTweetStatus& status);

protected slots:
    void parsingJsonFinished(const QVariant &json, bool ok, const QString &errorMsg);

private:
    void error();
};

#endif // QTWEETSTATUSRETWEET_H
