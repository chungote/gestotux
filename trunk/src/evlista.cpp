/***************************************************************************
 *   Copyright (C) 2006 by Esteban Zeller & Daniel Sequeira		   *
 *   juiraze@yahoo.com.ar  - daniels@hotmail.com			   *
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
#include "evlista.h"
#include <QSplitter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QSqlTableModel>
#include <QTableView>
#include <QCheckBox>
#include <QHeaderView>
#include "preferencias.h"
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>


EVLista::EVLista( QWidget *parent,  bool vertical )
 : EVentana( parent )
{
////////////////////////////////////////////////////////////////////////////////////////
 // Genero el formulario

    splitter = new QSplitter(this);
    splitter->setObjectName(QString::fromUtf8("splitter"));
    if( vertical == false )
    {
     boxLayoutgeneral = new QHBoxLayout(this);
     splitter->setOrientation(Qt::Vertical);
    }
    else
    {
     boxLayoutgeneral = new QVBoxLayout(this);
     splitter->setOrientation(Qt::Horizontal);
    }
    boxLayoutgeneral->setSpacing(6);
    boxLayoutgeneral->setMargin(9);
    boxLayoutgeneral->setObjectName(QString::fromUtf8("LayoutGeneral"));
    frame = new QFrame(splitter);
    frame->setObjectName(QString::fromUtf8("FrameBotones"));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(13), static_cast<QSizePolicy::Policy>(3));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
    frame->setSizePolicy(sizePolicy);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);
    if( vertical == false )
    {
      boxLayout = new QHBoxLayout( frame );
      frame->setMaximumHeight( 80 );
    }
    else
    {
      boxLayout = new QVBoxLayout( frame );
      frame->setMaximumWidth( 300 );
    }
    boxLayout->setSpacing(6);
    boxLayout->setMargin(9);
    boxLayout->setObjectName(QString::fromUtf8("Layout_Botones"));
    PBAgregar = new QPushButton(frame);
    PBAgregar->setObjectName(QString::fromUtf8("PBAgregar"));

    boxLayout->addWidget(PBAgregar);

    PBEliminar = new QPushButton(frame);
    PBEliminar->setObjectName(QString::fromUtf8("PBEliminar"));

    boxLayout->addWidget(PBEliminar);

    if( vertical == true )
    {
	linea = new QFrame(frame);
        linea->setObjectName(QString::fromUtf8("linea"));
        linea->setFrameShape(QFrame::HLine);
        linea->setFrameShadow(QFrame::Sunken);

        boxLayout->addWidget(linea);
    }

    spacerItem = new QSpacerItem(414, 191, QSizePolicy::Minimum, QSizePolicy::Expanding);

    boxLayout->addItem(spacerItem);

    PBCerrar = new QPushButton(frame);
    PBCerrar->setObjectName(QString::fromUtf8("PBCerrar"));

    boxLayout->addWidget(PBCerrar);

    vista = new QTableView(splitter);
    vista->setObjectName(QString::fromUtf8("vista"));
    vista->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );

    if( vertical == false )
    {
      splitter->addWidget(vista);
      splitter->addWidget(frame);
      boxLayoutgeneral->addWidget(splitter);
    }
    else
    {
      splitter->addWidget(frame);
      splitter->addWidget(vista);
      boxLayoutgeneral->addWidget(splitter);
    }

 //////////////////////////////////////////////////////////////////////////////////////////
 // Cargo las imagenes en los botones
 ////////////////////////////////////////////////////////////////////////////////////////
 PBAgregar ->setIcon( QIcon( ":/imagenes/add.png" ) );
 PBAgregar ->setText( "&Agregar" );
 PBEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
 PBEliminar->setText( "&Eliminar" );
 PBCerrar  ->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
 PBCerrar  ->setText( "Cer&rar" );
 // Propiedades varias
 vista->setSelectionMode( QAbstractItemView::SingleSelection );
 vista->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
 vista->setTextElideMode( Qt::ElideRight );
 // Conecto las señales
 connect( PBCerrar   , SIGNAL( clicked() ), this, SLOT( cerrar()    ) );
 connect( PBAgregar  , SIGNAL( clicked() ), this, SLOT( agregar()   ) );
 connect( PBEliminar , SIGNAL( clicked() ), this, SLOT( eliminar()  ) );

 PBAgregar->setShortcut( QKeySequence( "Ctrl+a" ) );
 PBEliminar->setShortcut( QKeySequence( "Ctrl+e" ) );
 PBCerrar->setShortcut( QKeySequence( "Ctrl+r" ) );
  //redimensiono a la ultima posicion
 preferencias *p = preferencias::getInstancia();
 p->beginGroup( "Ventanas" );
 p->beginGroup( nombre_ventana );
 splitter->restoreState( p->value("dimensiones" ).toByteArray() );
 p->endGroup();
 p->endGroup();
}


EVLista::~EVLista()
{
}


/*!
    \fn EVLista::cerrar()
    Llamada cuando se presiona el boton cerrar, cierra la ventana
 */
void EVLista::cerrar()
{
 this->close();
}


/*!
    \fn EVLista::agregar()
	Agrega un nuevo registro mediante la vista al modelo
 */
void EVLista::agregar()
{
 QSqlRecord registro = modelo->record();
 registro.remove( 0 );
 if( !modelo->insertRecord( -1, registro ) )
 {
  qDebug( "Error al insertar el registro" );
  qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( modelo->lastError().type() ).arg( modelo->lastError().number() ).arg( modelo->lastError().text() ).toLocal8Bit() );
 }
}

/*!
    \fn EVLista::eliminar()
	Elimina los items seleccionados de la vista
 */
void EVLista::eliminar()
{
 //Preguntar al usuario si esta seguro
 QItemSelectionModel *selectionModel = vista->selectionModel();
 QModelIndexList indices = selectionModel->selectedIndexes();
 if( indices.size() < 1 )
 {
   QMessageBox::warning( this, "Seleccione un item",
                   "Por favor, seleccione un item para eliminar",
                   QMessageBox::Ok );
   return;
 }
 //Hacer dialogo de confirmacion..
 int ret;
 ret = QMessageBox::warning( this, "Esta seguro?",
                   QString( "Esta seguro de eliminar %1 item?").arg( indices.size() ),
                   "Si", "No" );
 if ( ret == 0 )
 {
	QModelIndex indice;
	foreach( indice, indices )
	{
		if( indice.isValid() )
		{
			modelo->removeRow( indice.row() );
		}
	}
 }
 return;
}

/*!
    \fn EVLista::closeEvent( QCloseEvent * c)
	Metodo llamado al cerrarse el form
	@param c evento de cierre
 */
void EVLista::closeEvent( QCloseEvent * c)
{
 delete vista;
 modelo->submitAll();
 delete modelo;
 //Guardo  las dimensiones
 preferencias *p = preferencias::getInstancia();
 p->beginGroup( "Ventanas" );
 p->beginGroup( nombre_ventana );
 p->setValue( "dimensiones", splitter->saveState() );
 p->endGroup();
 p->endGroup();
 EVentana::closeEvent( c );
}

/*!
 * \fn EVLista::imprimir()
 *	Por ahora no hace nada
 */
void EVLista::imprimir()
{
}
