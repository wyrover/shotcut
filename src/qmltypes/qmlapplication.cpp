/*
 * Copyright (c) 2013-2016 Meltytech, LLC
 * Author: Brian Matherly <pez4brian@yahoo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qmlapplication.h"
#include "mainwindow.h"
#include "mltcontroller.h"
#include <QApplication>
#include <QSysInfo>
#include <QCursor>
#include <QPalette>
#include <QStyle>
#ifdef Q_OS_WIN
#include <QLocale>
#else
#include <clocale>
#endif

QmlApplication& QmlApplication::singleton()
{
    static QmlApplication instance;
    return instance;
}

QmlApplication::QmlApplication() :
    QObject()
{
}

Qt::WindowModality QmlApplication::dialogModality()
{
#ifdef Q_OS_OSX
    return (QSysInfo::macVersion() >= QSysInfo::MV_10_8)? Qt::WindowModal : Qt::ApplicationModal;
#else
    return Qt::ApplicationModal;
#endif
}

QPoint QmlApplication::mousePos()
{
    return QCursor::pos();
}

QColor QmlApplication::toolTipBaseColor()
{
#if defined(Q_OS_UNIX) && !defined(Q_OS_MAC)
    if ("gtk+" == QApplication::style()->objectName())
        return QApplication::palette().highlight().color();
#endif
    return QApplication::palette().toolTipBase().color();
}

QColor QmlApplication::toolTipTextColor()
{
#if defined(Q_OS_UNIX) && !defined(Q_OS_MAC)
    if ("gtk+" == QApplication::style()->objectName())
        return QApplication::palette().highlightedText().color();
#endif
    return QApplication::palette().toolTipText().color();
}

QString QmlApplication::OS()
{
#if defined(Q_OS_OSX)
    return "OS X";
#elif defined(Q_OS_LINUX)
    return "Linux";
#elif defined(Q_OS_UNIX)
    return "UNIX";
#elif defined(Q_OS_WIN)
    return "Windows";
#else
    return "";
#endif
}

QString QmlApplication::numericLocale()
{
#ifdef Q_OS_WIN
    return QLocale::system().name();
#else
    return QString::fromLatin1(::setlocale(LC_NUMERIC, NULL));
#endif
}

QRect QmlApplication::mainWinRect()
{
    return MAIN.geometry();
}

bool QmlApplication::hasFiltersOnClipboard()
{
    return MLT.hasFiltersOnClipboard();
}

void QmlApplication::copyFilters()
{
    MLT.copyFilters();
    emit QmlApplication::singleton().filtersCopied();
}

void QmlApplication::pasteFilters()
{
    MLT.pasteFilters();
    MLT.refreshConsumer();
}

