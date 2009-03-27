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
#include "dventacompra.h"
#include <QLineEdit>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QCompleter>

DVentaCompra::DVentaCompra(QObject *parent)
 : QSqlRelationalDelegate(parent)
{
 setClipping( false );
}


DVentaCompra::~DVentaCompra()
{
}

/*!
 *  \fn DVentaCompra::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
 *	Funcion que retorna un acosejamiento del tamaño para cierto campo.
 *	@param option Opcion de estilo
 *	@param index Indice de aconsjamiento
	@return Objeto <b>QSize</b> que tiene el tamano.
 */
QSize DVentaCompra::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
 if( index.column() == 2 )
 {
	QSize tam = QSqlRelationalDelegate::sizeHint( option, index );
	tam.setWidth( 300 );
	return tam;
 }
 else
 {
   return QSqlRelationalDelegate::sizeHint( option, index );
 }
}

QWidget* DVentaCompra::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
 switch( index.column() )
 {
	case 3:
	{
		QDoubleSpinBox *e = new QDoubleSpinBox( parent );
		e->setPrefix( "$" );
		e->setSingleStep( 1 );
		e->setRange( 0.00, 9999.00 );
		return e;
	}
	case 4:
	{
		QSpinBox *e = new QSpinBox( parent );
		e->setRange( 0, 99 );
		return e;
	}
/*	case 2:
	{
		QComboBox *combo = qobject_cast<QComboBox *>(QSqlRelationalDelegate::createEditor( parent, option, index ) );
		combo->setSizeAdjustPolicy( QComboBox::AdjustToContentsOnFirstShow );
		combo->setEditable( true );
		combo->completer()->setCompletionMode( QCompleter::PopupCompletion );
		return combo;
	}*/
	default:
	{
		return QSqlRelationalDelegate::createEditor(parent, option, index);
	}
 }
}

void DVentaCompra::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QSqlRelationalDelegate::setEditorData(editor, index);
}

void DVentaCompra::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
  switch( index.column() )
 {
	default:
	{
		QSqlRelationalDelegate::setModelData(editor, model, index);
		return;
	}
 }
}

void DVentaCompra::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QSqlRelationalDelegate::updateEditorGeometry( editor, option, index );
}
