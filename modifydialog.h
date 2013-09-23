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
#ifndef MODIFYDIALOG_H
#define MODIFYDIALOG_H

#include <QtWidgets/QDialog>
#include "core.h"
#include <QList>

namespace Ui {
    class modifyDialog;
}

class modifyDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(modifyDialog)
public:
    explicit modifyDialog(QWidget *parent = 0);
    virtual ~modifyDialog();
    QList<kstm::tunnel> tunnels;
    void loadTunnels();
    void loadConnection(kstm::connection &Conn);
    void commitConnection(kstm::connection &Conn);
protected:
    virtual void changeEvent(QEvent *e);
    void accept();

private:
    Ui::modifyDialog *m_ui;

private slots:
    void on_listWidget_tunnels_currentRowChanged(int currentRow);
    void on_actionAdd_triggered();
    void on_actionDelete_triggered();
    void on_actionEdit_triggered();
};

#endif // MODIFYDIALOG_H
