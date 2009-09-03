/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar   						   *
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
#include "dproductostotales.h"
#include <QLineEdit>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QCompleter>
#include <QComboBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include "edsbprecio.h"
#include "../plugins/productos/mproductos.h"
#include "preferencias.h"

DProductosTotales::DProductosTotales(QWidget *parent)
 : QItemDelegate(parent)
{
 setClipping( false );
}


DProductosTotales::~DProductosTotales()
{
}

QWidget* DProductosTotales::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
 switch( index.column() )
 {
	//Producto
	case 0:
	{
		QComboBox *combo = new QComboBox( parent );
		// Rellenar los items
		QSqlQuery cola( "SELECT nombre, id FROM producto WHERE habilitado = 1" );
		while( cola.next() )
		{
			combo->addItem( cola.record().value("nombre").toString(), cola.record().value( "id" ) );
		}
		combo->setSizeAdjustPolicy( QComboBox::AdjustToMinimumContentsLengthWithIcon );
		combo->setEditable( true );
		combo->completer()->setCompletionMode( QCompleter::PopupCompletion );
		return combo;
	}
	// Precio Unitario
	case 1:
	{
		EDSBPrecio *e = new EDSBPrecio( parent );
		e->setPrefix( "$" );
		e->setSingleStep( 1 );
		e->setRange( 0.00, 9999.00 );
		return e;

	}
	// Cantidad
	case 2:
	{

		EDSBPrecio *e = new EDSBPrecio( parent );
		e->setRange( 0.0, 99999.9 );
		e->setPrefix("");
		/*if( preferencias::getInstancia()->value( "Preferencias/Productos/Stock/limitar", false ).toBool() )
		{
		 e->setMaximum( MProductos::stock( index.model()->data( index.model()->index( index.row(), 0 ), Qt::EditRole ).toInt() ) );
		}*/
		return e;
	}
	default:
	{
		// Los demas no deben ser editables
		return QItemDelegate::createEditor(parent, option, index);
	}
 }
}

void DProductosTotales::setEditorData(QWidget* editor, const QModelIndex& index) const
{
 switch( index.column() )
 {
	//Producto
	case 0:
	{
		QComboBox *combo = qobject_cast<QComboBox *>(editor);
		combo->setCurrentIndex( combo->findData(  index.model()->data(index, Qt::EditRole).toInt() ) );
		break;
	}
	// Precio Unitario
	case 1:
	// Cantidad
	case 2:
	{
		EDSBPrecio *e = qobject_cast<EDSBPrecio *>( editor );
		e->setValue( index.data( Qt::EditRole ).toDouble() );
		break;
	}
	default:
	{
		// Los demas no deben ser editables
		return QItemDelegate::setEditorData( editor, index);
	}
 }
}

void DProductosTotales::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
  switch( index.column() )
 {
	//Producto
	case 0:
	{
		QComboBox *combo = qobject_cast<QComboBox *>(editor);
		if( combo->itemData( combo->currentIndex() ) == QVariant::Invalid )
		{ qDebug( "ERROR" ); }
		model->setData( index, combo->itemData( combo->currentIndex() ) );
		break;
	}
	// Precio Unitario
	case 1:
	// Cantidad
	case 2:
	{
		EDSBPrecio *e = qobject_cast<EDSBPrecio *>( editor );
		model->setData( index, e->value() );
		break;
	}
	default:
	{
		// Los demas no deben ser editables
		return QItemDelegate::setEditorData( editor, index);
	}
 }
}

void DProductosTotales::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QItemDelegate::updateEditorGeometry(editor, option, index);
}

