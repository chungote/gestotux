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
#include "formpreferencias.h"

#include <QListWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAction>
#include <QSplitter>

#include "preferencias.h"
#include "formprefhijo.h"
#include "fprefgeneral.h"
#include "gestotux.h"
#include "einfoprogramainterface.h"

FormPreferencias::FormPreferencias(QWidget *parent)
 : EVentana(parent)
{
    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setSpacing(12);
    contentsWidget->sizePolicy().setVerticalPolicy( QSizePolicy::MinimumExpanding );

    pagesWidget = new QStackedWidget;
    QListWidgetItem *configButton = new QListWidgetItem( contentsWidget );
    configButton->setIcon( QIcon( ":/imagenes/general.png" ) );
    configButton->setText( "Estilo" );
    configButton->setTextAlignment( Qt::AlignHCenter );
    configButton->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
     ////////////////////////////////////////////////////////////////////
     /// Agregar aqui los widgets de configuracion
     FPrefGeneral *formGeneral = new FPrefGeneral( this );
     connect( this, SIGNAL( aplicar() ), formGeneral, SLOT( aplicar() ) );
     connect( this, SIGNAL( cargar() ), formGeneral, SLOT( cargar() ) );
     connect( this, SIGNAL( guardar() ), formGeneral, SLOT( guardar() ) );
     pagesWidget->addWidget( formGeneral );
     if( !gestotux::plugin()->formsPreferencias().isEmpty() )
     {
	QWidget *form;
	foreach( form, gestotux::plugin()->formsPreferencias() )
	{
		// agrego el item a la lista
		QListWidgetItem *opciones = new QListWidgetItem( contentsWidget );
		opciones->setIcon( form->windowIcon() );
		opciones->setText( form->windowTitle() );
		opciones->setTextAlignment( Qt::AlignHCenter );
		opciones->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
		contentsWidget->addItem( opciones );
		// Agrego el formulario
		pagesWidget->addWidget( form );
		connect( this, SIGNAL( guardar() ), form, SLOT( guardar() ) );
		connect( this, SIGNAL( cargar() ), form, SLOT( cargar() ) );
		connect( this, SIGNAL( aplicar() ), form, SLOT( aplicar() ) );
	}
    }

    ActCerrar  = new QAction( "Cerrar", this );
    ActCerrar->setShortcut( QKeySequence( "Ctrl+r" ) );
    ActCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
    connect( ActCerrar, SIGNAL( triggered() ), this, SLOT( cancelar()) );

    ActAplicar = new QAction( "Ap&licar", this );
    ActAplicar->setShortcut( QKeySequence( "Ctrl+l" ) );
    ActAplicar->setIcon( QIcon( ":/imagenes/aplicar.png" ) );
    connect( ActAplicar, SIGNAL( triggered() ), this, SIGNAL( aplicar() ) );

    ActGuardar = new QAction( "&Guardar", this  );
    ActGuardar->setShortcut( QKeySequence( "Ctrl+g" ) );
    ActGuardar->setIcon( QIcon( ":/imagenes/guardar.png" ) );
    connect( ActGuardar, SIGNAL( triggered() ), this, SIGNAL( guardar() ) );

    addAction( ActGuardar );
    addAction( ActAplicar );
    addAction( ActCerrar );

    nombre_ventana  = "Configuracion";
    setNombreVentana( "Configuracion de " + gestotux::plugin()->nombrePrograma() );

    contentsWidget->setCurrentRow(0);

    Splitter = new QSplitter;
    Splitter->addWidget(contentsWidget);
    Splitter->addWidget(pagesWidget);
    Splitter->setCollapsible( 0, false );
    Splitter->setCollapsible( 1, false );

    QGridLayout *gl = new QGridLayout( this );
    gl->addWidget( Splitter );
    setLayout(gl);

    connect(contentsWidget, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(changePage(QListWidgetItem *, QListWidgetItem*)));

	connect( this, SIGNAL( guardar() ), this, SIGNAL( aplicar() ) );

	// Cargo la ultima pos de el spliter
	preferencias *p = preferencias::getInstancia();
	p->beginGroup( "Ventanas" );
	p->beginGroup( "Preferencias" );
	Splitter->restoreState( p->value( "spliter", QByteArray() ).toByteArray() );
	p->endGroup();
	p->endGroup();

	// Cargo las preferencias
	emit cargar();
}


FormPreferencias::~FormPreferencias()
{
	preferencias *p = preferencias::getInstancia();
	p->beginGroup( "Ventanas" );
	p->beginGroup( "Preferencias" );
	p->setValue( "spliter", Splitter->saveState() );
	p->endGroup();
	p->endGroup();
}


/*!
    \fn FormPreferencias::changePage(QListWidgetItem *current, QListWidgetItem *previous)
	Cambia la pagina de la configuracion
	@param current Item actual de la lista
	@param previous Item anterior en la lista
 */
void FormPreferencias::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}


/*!
    \fn FormPreferencias::cancelar()
 */
void FormPreferencias::cancelar()
{
 close();
}

