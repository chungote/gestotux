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
#include "ncaboutdialog.h"

/*#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qtextbrowser.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>*/

NCAboutDialog::NCAboutDialog( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, modal, fl )
{
    if ( !name )
	setNameObjectName( "NCAboutDialog" );
    else
	setObjectName( name );

	NCAboutDialogLayout = new QVBoxLayout( this, 6, 6, "NCAboutDialogLayout");
    layTitle = new QHBoxLayout( 0, 0, 6, "layTitle");

    lblImage = new QLabel( this, "lblImage" );
    lblImage->setMaximumSize( QSize( 100, 32767 ) );
    layTitle->addWidget( lblImage );

    lblName = new QLabel( this, "lblName" );
    QFont lblName_font(  lblName->font() );
    lblName_font.setBold( TRUE );
    lblName->setFont( lblName_font );
    layTitle->addWidget( lblName );
    NCAboutDialogLayout->addLayout( layTitle );

    tabAbout = new QTabWidget( this, "tabAbout" );

    tab = new QWidget( tabAbout, "tab" );
    tabLayout = new QVBoxLayout( tab, 6, 6, "tabLayout");

    lblAbout = new QLabel( tab, "lblAbout" );
    lblAbout->setAlignment( int( QLabel::WordBreak | QLabel::AlignCenter ) );
    tabLayout->addWidget( lblAbout );
    tabAbout->insertTab( tab, QString::fromLatin1("") );

    TabPage = new QWidget( tabAbout, "TabPage" );
    TabPageLayout = new QVBoxLayout( TabPage, 6, 6, "TabPageLayout");

    lblAuthor = new QLabel( TabPage, "lblAuthor" );
    lblAuthor->setAlignment( int( QLabel::WordBreak | QLabel::AlignCenter ) );
    TabPageLayout->addWidget( lblAuthor );
    tabAbout->insertTab( TabPage, QString::fromLatin1("") );

    TabPage_2 = new QWidget( tabAbout, "TabPage_2" );
    TabPageLayout_2 = new QVBoxLayout( TabPage_2, 6, 6, "TabPageLayout_2");

    textLicence = new QTextBrowser( TabPage_2, "textLicence" );
    TabPageLayout_2->addWidget( textLicence );
    tabAbout->insertTab( TabPage_2, QString::fromLatin1("") );
    NCAboutDialogLayout->addWidget( tabAbout );

    layBtn = new QHBoxLayout( 0, 0, 6, "layBtn");
    spButtons = new QSpacerItem( 240, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layBtn->addItem( spButtons );

    btnOK = new QPushButton( this, "btnOK" );
    layBtn->addWidget( btnOK );
    NCAboutDialogLayout->addLayout( layBtn );
    languageChange();
    resize( QSize(456, 275).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( btnOK, SIGNAL( clicked() ), this, SLOT( accept() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
NCAboutDialog::~NCAboutDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void NCAboutDialog::languageChange()
{
    setCaption( tr( "About" ) );
    lblImage->setText( QString::null );
    lblName->setText( tr( "Name+Version" ) );
    lblAbout->setText( tr( "About <b>text</b>" ) );
    tabAbout->changeTab( tab, tr( "About" ) );
    lblAuthor->setText( tr( "<h2>Name of author</h2>\n"
"<h3>Company ...</h3>\n"
"<a href=\"mailto:name@company.com\">name@company.com</a>" ) );
    tabAbout->changeTab( TabPage, tr( "Author" ) );
    textLicence->setText( tr( "<h1>Licence</h1>\n"
"Licence..." ) );
    tabAbout->changeTab( TabPage_2, tr( "Licence" ) );
    btnOK->setText( tr( "Close" ) );
}

void NCAboutDialog::setAbout(const QString& about )
{
	lblAbout->setText( about );
}

void NCAboutDialog::setAuthor(const QString& auth )
{
	lblAuthor->setText( auth );
}

void NCAboutDialog::setLicence(const QString& lic )
{
	textLicence->setText( lic );
}

void NCAboutDialog::setName(const QString& name )
{
	lblName->setText( name );
}

void NCAboutDialog::setIcon(const QPixmap& pm )
{
	//image0 = img;
	lblImage->setPixmap( pm );
}

