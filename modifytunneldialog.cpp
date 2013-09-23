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
#include "modifytunneldialog.h"
#include "ui_modifytunneldialog.h"

modifyTunnelDialog::modifyTunnelDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::modifyTunnelDialog)
{
    m_ui->setupUi(this);
}

modifyTunnelDialog::~modifyTunnelDialog()
{
    delete m_ui;
}

void modifyTunnelDialog::loadTunnel(kstm::tunnel Tunnel)
{
    tunnel = Tunnel;
    m_ui->lineEdit_alias->setText(tunnel.getAlias());
    m_ui->lineEdit_hostname->setText(tunnel.getHostname());
    m_ui->spinBox_port->setValue(tunnel.getPort());
    m_ui->spinBox_toPort->setValue(tunnel.getToPort());
    m_ui->comboBox_type->setCurrentIndex(tunnel.getConnectionType());
}
void modifyTunnelDialog::accept()
{
    QString problems = "";
    if (m_ui->lineEdit_alias->text() == "")
    {
        problems = problems + "You have to specify the tunnel name.\n";
    }
    if (m_ui->lineEdit_hostname->text() == "")
    {
        problems = problems + "You have to provide the target hostname.\n";
    }
    if (problems == "")
    {
        tunnel.setAlias(m_ui->lineEdit_alias->text());
        tunnel.setHostname(m_ui->lineEdit_hostname->text());
        tunnel.setPort(m_ui->spinBox_port->value());
        tunnel.setToPort(m_ui->spinBox_toPort->value());
        done(1);
    }
    else
    {
        QMessageBox msgbox;
        msgbox.setText("Please, solve the following problems...");
        msgbox.setDetailedText(problems);
        msgbox.exec();
    }
}
void modifyTunnelDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

