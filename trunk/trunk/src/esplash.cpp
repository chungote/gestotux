/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   *
 *   juiraze@yahoo.com.ar   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "esplash.h"
#include <QFile>
#include <QDir>
#include <QApplication>

ESplash::ESplash(QWidget *parent)
 : QSvgWidget( parent )
{
 this->setWindowFlags( Qt::SplashScreen );
 if( QFile::exists( QApplication::applicationDirPath() + QDir::separator() + "splash.svg" ) )
 {
  this->load( QString( QApplication::applicationDirPath() + QDir::separator() + "splash.svg") );
 }
 else
 {
  this->load( QString(":/imagenes/splash.svg") );
 }
}


ESplash::~ESplash()
{
}


void ESplash::repaint()
{ }

void ESplash::setPixmap(const QPixmap& pixmap)
{ return; }

void ESplash::clearMessage()
{}

void ESplash::showMessage(const QString& message, int alignment, const QColor& color)
{}

void ESplash::show()
{ 
 QWidget::setVisible(true);
}
