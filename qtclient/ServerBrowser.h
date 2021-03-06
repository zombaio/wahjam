/*
    Copyright (C) 2012 Ikkei Shimomura (tea) <Ikkei.Shimomura@gmail.com>

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

#ifndef _SERVERBROWSER_H
#define _SERVERBROWSER_H


#include <QUrl>
#include <QString>
#include <QTextStream>

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <QNetworkAccessManager>
#include <QNetworkReply>


class ServerBrowser : public QTreeWidget
{
  Q_OBJECT

public:
  ServerBrowser(QNetworkAccessManager *manager_, QWidget *parent=0);
  virtual ~ServerBrowser() {}
  void loadServerList(const QUrl &url);
  virtual void parseServerList(QTextStream *stream) = 0;

signals:
  void serverItemSelected(const QString &hostname);
  void serverItemActivated(const QString &hostname);

private slots:
  void completeDownloadServerList();
  void onItemSelectionChanged();
  void onItemActivated(QTreeWidgetItem *item, int column);

protected:
  virtual QNetworkReply *sendNetworkRequest(const QUrl &url) = 0;
  virtual void selectBestItem();

  QNetworkAccessManager *netManager;

private:
  QNetworkReply *reply;
};

#endif
