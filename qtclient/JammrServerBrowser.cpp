/*
    Copyright (C) 2012 Stefan Hajnoczi <stefanha@gmail.com>

    Wahjam is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Wahjam is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Wahjam; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "JammrServerBrowser.h"

JammrServerBrowser::JammrServerBrowser(QNetworkAccessManager *manager, QWidget *parent)
  : ServerBrowser(manager, parent)
{
  setHeaderLabels(QStringList() << "Topic" << "Tempo" << "Slots" << "Users");
}

QNetworkReply *JammrServerBrowser::sendNetworkRequest(const QUrl &apiUrl)
{
  QUrl livejamsUrl(apiUrl);
  livejamsUrl.setPath(apiUrl.path() + "livejams/");

  QNetworkRequest request(livejamsUrl);
  request.setRawHeader("Referer", livejamsUrl.toString(QUrl::RemoveUserInfo).toLatin1().data());

  return netManager->get(request);
}

void JammrServerBrowser::selectBestItem()
{
  QTreeWidgetItem *item = NULL;

  // Select first jam with at least one user, otherwise select the last jam
  for (int i = 0; i < topLevelItemCount(); i++) {
    item = topLevelItem(i);

    QString users = item->text(3);
    if (!users.isEmpty()) {
      break;
    }
  }

  if (item) {
    setCurrentItem(item);
  }
}

void JammrServerBrowser::parseServerList(QTextStream *stream)
{
  QJsonParseError err;
  QJsonDocument doc(QJsonDocument::fromJson(stream->device()->readAll(), &err));

  if (doc.isNull()) {
    qCritical("Server list JSON parse error: %s",
              err.errorString().toLatin1().constData());
    return;
  }

  /* The JSON looks like this:
   *
   * [
   *   {
   *     'server': 'host:port',
   *     'users': ['bob', 'joe'],
   *     'topic': 'Hello world!',
   *     'bpm': 120,
   *     'bpi': 16,
   *     'is_public': true,
   *     'numusers': 2,
   *     'maxusers': 6
   *   },
   *   ...
   * ]
   */

  foreach (QJsonValue jam, doc.array()) {
    QJsonObject obj(jam.toObject());
    QString server = obj.value("server").toString();
    if (server.isEmpty()) {
      continue; // skip invalid element
    }

    QString topic = obj.value("topic").toString();
    double bpm = obj.value("bpm").toDouble();
    double bpi = obj.value("bpi").toDouble();
    double numUsers = obj.value("numusers").toDouble();
    double maxUsers = obj.value("maxusers").toDouble();

    QStringList users;
    foreach (QJsonValue user, obj.value("users").toArray()) {
      users << user.toString();
    }

    QTreeWidgetItem *item = new QTreeWidgetItem(this);
    item->setData(0, Qt::UserRole, server);
    item->setText(0, topic);
    item->setText(1, QString("%1 BPM/%2").arg(bpm).arg(bpi));
    item->setText(2, QString("%1/%2").arg(numUsers).arg(maxUsers));
    item->setText(3, users.join(", "));
  }
}
