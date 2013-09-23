/*
This file is part of KSTM.
KSTM is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

KSTM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with KSTM.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <QtCore>
#include <QList>
#include <QProcess>
#include <QThread>
#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#ifndef CORE_H
#define CORE_H

namespace kstm
{
    class tunnel
    {
        public:
            enum connectionTypes {local=0, remote=1, dynamic=2};
            tunnel();
            tunnel(QString Alias);
            tunnel(QString Alias, int Port, QString Hostname, int ToPort, int ConnectionType);
            ~tunnel();
            void setAlias(QString Alias);
            void setPort(int Port);
            void setHostname(QString Hostname);
            void setToPort(int ToPort);
            void setConnectionType(int ConnectionType);
            QString getAlias();
            int getPort();
            QString getHostname();
            int getToPort();
            int getConnectionType();
        private:
            QString alias;
            int port;
            QString hostname;
            int toPort;
            int connectionType;
    };
    class connection
    {
        public:
            connection();
            connection(QString Alias);
            ~connection();
            void connectssh();
            void disconnectssh(bool force);
            void setHostname(QString Hostname);
            void setUsername(QString Username);
            void setAlias(QString Alias);
            void setAllowRemote(bool AllowRemote);
            void setPort(int Port);
            QString getConnectionString();
            QString getHostname();
            QString getUsername();
            QString getAlias();
            bool getAllowRemote();
            int getPort();
            QProcess proc;
            QList<tunnel> tunnels;
        private:
            QString hostname;
            QString username;
            QString alias;
            bool allowRemote;
            int port;
    };
    class configWriter : public QXmlStreamWriter
    {
        public:
            configWriter(QList<kstm::connection*> Connections);
            bool writeFile(QIODevice *device);
        private:
            QList<kstm::connection*> connections;
    };
    class configReader : public QXmlStreamReader
    {
        public:
            configReader(QList<kstm::connection*> *Connections);
            bool readFile(QIODevice *device);
        private:
            QList<kstm::connection*> *connections;
    };
};
#endif // CORE_H
