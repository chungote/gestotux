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
#include "dsino.h"
#include <QCheckBox>

DSiNo::DSiNo(QObject *parent)
 : QItemDelegate(parent)
{
}


DSiNo::~DSiNo()
{
}


QWidget* DSiNo::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
 QCheckBox *editor = new QCheckBox( parent );
 editor->setText( index.model()->headerData( index.column(), Qt::Horizontal ).toString() );
 editor->setTristate( false );
 editor->setPalette( option.palette );
 editor->setFont( option.font );
 editor->setBackgroundRole( QPalette::Background );
 return editor;
}

void DSiNo::setEditorData(QWidget* editor, const QModelIndex& index) const
{
 qobject_cast<QCheckBox *>(editor)->setChecked( index.data( Qt::EditRole ).toBool() );
}

void DSiNo::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
 model->setData( index, qobject_cast<QCheckBox *>(editor)->isChecked(), Qt::EditRole );
}

