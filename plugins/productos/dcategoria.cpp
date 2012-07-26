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
#include "dcategoria.h"

#include <QComboBox>

DCategoria::DCategoria(QObject *parent)
 : QItemDelegate(parent)
{
}


DCategoria::~DCategoria()
{
}


QWidget* DCategoria::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
 switch( index.column() )
 {
  case 3:
  {
	QComboBox *combo = new QComboBox( parent );
	combo->insertItem( 0, "Ventas" );
	combo->insertItem( 1, "Compras"  );
	combo->insertItem( 2, "Gastos" );
	return combo;
	break;
  }
  default:
  {
	return QItemDelegate::createEditor(parent, option, index);
	break;
  }
 }
}

void DCategoria::setEditorData( QWidget* editor, const QModelIndex& index ) const
{
 switch( index.column() )
 {
  case 3:
  {
	QComboBox *combo = qobject_cast<QComboBox *>(editor);
	combo->setCurrentIndex( index.data( Qt::EditRole ).toInt() );
	break;
  }
  default:
  {
	QItemDelegate::setEditorData(editor, index);
	break;
  }
 }
 return;
}

void DCategoria::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
 switch( index.column() )
 {
  case 3:
  {
	QComboBox *combo = qobject_cast<QComboBox *>(editor);
	model->setData( index, combo->currentIndex() );
	break;
  }
  default:
  {
	QItemDelegate::setModelData(editor, model, index);
	break;
  }
 }
 return;
}

void DCategoria::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  QItemDelegate::updateEditorGeometry(editor, option, index);
}

