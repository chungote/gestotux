/***************************************************************************
 *   Copyright (C) 2006 by Norbert Szabo                                   *
 *   nszabo@helta.hu                                                       *
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
#ifndef NCABOUTDIALOG_H
#define NCABOUTDIALOG_H

#include <QVariant>
#include <QDialog>
#include <QPixmap>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QTabWidget;
class QWidget;
class QTextBrowser;
class QPushButton;

class NCAboutDialog : public QDialog
{
    Q_OBJECT

public:
    NCAboutDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~NCAboutDialog();

    QLabel* lblImage;
    QLabel* lblName;
    QTabWidget* tabAbout;
    QWidget* tab;
    QLabel* lblAbout;
    QWidget* TabPage;
    QLabel* lblAuthor;
    QWidget* TabPage_2;
    QTextBrowser* textLicence;
    QPushButton* btnOK;

    virtual void setAbout( const QString& );
    virtual void setAuthor( const QString& );
    virtual void setLicence( const QString& );
    virtual void setName( const QString& );
    virtual void setIcon( const QPixmap& );

protected:
    QVBoxLayout* NCAboutDialogLayout;
    QHBoxLayout* layTitle;
    QVBoxLayout* tabLayout;
    QVBoxLayout* TabPageLayout;
    QVBoxLayout* TabPageLayout_2;
    QHBoxLayout* layBtn;
    QSpacerItem* spButtons;

protected slots:
    virtual void languageChange();

private:
    //QPixmap image0;

};

#endif // NCABOUTDIALOG_H
