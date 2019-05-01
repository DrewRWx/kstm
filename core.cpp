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
#include "core.h"
using namespace kstm;

connection::connection()
{
    hostname="localhost";
    username="root";
    port=22;
    allowRemote=false;
    alias = QString::null;
}
connection::connection(QString Alias)
{
    hostname="localhost";
    username="root";
    port=22;
    allowRemote=false;
    alias = Alias;
}
connection::~connection()
{
    proc.kill();
    proc.close();
}
void connection::connectssh()
{
    proc.start(getConnectionString(),QIODevice::ReadOnly);
}
void connection::disconnectssh(bool force)
{
    proc.terminate();
    proc.close();
}
void connection::setHostname(QString Hostname)
{
    hostname = Hostname;
}
void connection::setUsername(QString Username)
{
    username = Username;
}
void connection::setAlias(QString Alias)
{
    alias = Alias;
}
void connection::setAllowRemote(bool AllowRemote)
{
    allowRemote = AllowRemote;
}
void connection::setPort(int Port)
{
    port = Port;
}
QString connection::getConnectionString()
{
    QString tmp;
    tmp = "/usr/bin/ssh " + username + "@" + hostname + " -p " + QString::number(port);
    if (allowRemote)
    {
        tmp = tmp + " -g";
    }
    for (int i = 0; i < tunnels.size(); ++i)
    {
        tmp = tmp + " -L0.0.0.0:" + QString::number((tunnels.operator [](i)).getPort()) + ":" + (tunnels.operator [](i)).getHostname() + ":" + QString::number((tunnels.operator [](i)).getToPort());
    }

    return(tmp);
}
QString connection::getHostname()
{
    return (hostname);
}
QString connection::getUsername()
{
    return (username);
}
QString connection::getAlias()
{
    return (alias);
}
bool connection::getAllowRemote()
{
    return (allowRemote);
}
int connection::getPort()
{
    return (port);
}

tunnel::tunnel()
{
    alias = QString::null;
    port=1024;
    hostname="localhost";
    toPort=22;
    connectionType=local;
}
tunnel::tunnel(QString Alias)
{
    alias = Alias;
    port=1024;
    hostname="localhost";
    toPort=22;
    connectionType=local;
}
tunnel::tunnel(QString Alias, int Port, QString Hostname, int ToPort, int ConnectionType)
{
    alias = Alias;
    port=Port;
    hostname=Hostname;
    toPort=ToPort;
    connectionType=ConnectionType;
}
tunnel::~tunnel()
{
}
void tunnel::setAlias(QString Alias)
{
    alias = Alias;
}
void tunnel::setPort(int Port)
{
    port=Port;
}
void tunnel::setHostname(QString Hostname)
{
    hostname=Hostname;
}
void tunnel::setToPort(int ToPort)
{
    toPort=ToPort;
}
void tunnel::setConnectionType(int ConnectionType)
{
    connectionType=ConnectionType;
}
QString tunnel::getAlias()
{
    return (alias);
}
int tunnel::getPort()
{
    return(port);
}
QString tunnel::getHostname()
{
    return(hostname);
}
int tunnel::getToPort()
{
    return(toPort);
}
int tunnel::getConnectionType()
{
    return(connectionType);
}

configWriter::configWriter(QList<kstm::connection*> Connections)
{
    connections=Connections;
    setAutoFormatting(true);
}
bool configWriter::writeFile(QIODevice *device)
{
    setDevice(device);
    writeStartDocument();
    writeDTD("<!DOCTYPE kstm>");
    writeStartElement("kstm");
    for (int i = 0; i < connections.size(); ++i)
    {
        writeStartElement("connection");
            writeAttribute("alias",(connections.operator [](i))->getAlias());
            if ((connections.operator [](i))->getAllowRemote())
            {
                writeAttribute("allowRemote","true");
            }
            else
            {
                 writeAttribute("allowRemote","false");
            }
            writeAttribute("hostname",(connections.operator [](i))->getHostname());
            writeAttribute("port",QString::number((connections.operator [](i))->getPort()));
            writeAttribute("username",(connections.operator [](i))->getUsername());
            for (int j = 0; j < (connections.operator [](i))->tunnels.size(); ++j)
            {
                writeStartElement("tunnel");
                    writeAttribute("alias",((connections.operator [](i))->tunnels.operator [](j)).getAlias());
                    writeAttribute("connectionType",QString::number(((connections.operator [](i))->tunnels.operator [](j)).getConnectionType()));
                    writeAttribute("hostname",((connections.operator [](i))->tunnels.operator [](j)).getHostname());
                    writeAttribute("port",QString::number(((connections.operator [](i))->tunnels.operator [](j)).getPort()));
                    writeAttribute("toPort",QString::number(((connections.operator [](i))->tunnels.operator [](j)).getToPort()));
                writeEndElement();
            }
        writeEndElement();
    }
    writeEndElement();
    writeEndDocument();
    return (true);
}

configReader::configReader(QList<kstm::connection*> *Connections)
{
    connections = Connections;
}
bool configReader::readFile(QIODevice *device)
{
    for (int i = 0; i < connections->size(); ++i) //we clean and close all connections (if there are)
    {
        (connections->operator [](i))->disconnectssh(true);
    }
    connections->clear();

    setDevice(device);
    if (!atEnd())
    {
        readNext();
    }
    while (!atEnd())
    {
        if (isStartElement() && name() == "connection")
        {
            connection *tmpConn = new connection(attributes().value("alias").toString());
            if (attributes().value("allowRemote").toString() == "true")
            {
                tmpConn->setAllowRemote(true);
            }
            else
            {
                tmpConn->setAllowRemote(false);
            }
            tmpConn->setHostname(attributes().value("hostname").toString());
            tmpConn->setPort(attributes().value("port").toString().toInt());
            tmpConn->setUsername(attributes().value("username").toString());
            while (!atEnd())
            {
                readNext();
                if (isEndElement() && name() != "tunnel")
                {
                    break;
                }
                if (isStartElement() && name() == "tunnel")
                {
                    tunnel tmpTun(attributes().value("alias").toString());
                    tmpTun.setConnectionType(attributes().value("connectionType").toString().toInt());
                    tmpTun.setHostname(attributes().value("hostname").toString());
                    tmpTun.setPort(attributes().value("port").toString().toInt());
                    tmpTun.setToPort(attributes().value("toPort").toString().toInt());
                    tmpConn->tunnels.append(tmpTun);
                }
            }
            &connections->operator <<(tmpConn);
        }
        readNext();
     }
     return !error();
}
