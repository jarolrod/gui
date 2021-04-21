// Copyright (c) 2018-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <QApplication>
#include <QMessageBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <QTimer>
#include <QWidget>

void ConfirmMessage(QString* text, int msec)
{
    QTimer::singleShot(msec, [text]() {
        for (QWidget* widget : QApplication::topLevelWidgets()) {
            if (widget->inherits("QMessageBox")) {
                QMessageBox* messageBox = qobject_cast<QMessageBox*>(widget);
                if (text) *text = messageBox->text();
                messageBox->defaultButton()->click();
            }
        }
    });
}

int GetTextSize(QString text)
{
	QRegularExpression re("font-size:(\\d+)pt", QRegularExpression::MultilineOption);
	QRegularExpressionMatch match = re.match(text);
	if (match.hasMatch()) return match.captured(1).toInt();
	else return 0;
}
