#include "eserviciosdelegate.h"

#include <QComboBox>

EServiciosDelegate::EServiciosDelegate(QObject *parent) :
    QItemDelegate(parent)
{}

void EServiciosDelegate::setEditorData ( QWidget * editor, const QModelIndex & index ) const
{
    switch( index.column() ) {
        /* Para todos los Combobox, la estructura ingresada es pos con valor, texto, itemdata valor */
        case 6: // Periodo
        case 7: // Dia de cobro
        case 8: // Forma de pago incompleto
        {
            QComboBox *c = qobject_cast<QComboBox *>(editor);
            // pongo el item que corresponda segun el dato
            c->setCurrentIndex( c->findData( index.data( Qt::EditRole ).toInt() ) );
            break;
        }
        default:
        {  QItemDelegate::setEditorData( editor, index ); break; }
    }

}

void EServiciosDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch( index.column() ) {
        /* Para todos los Combobox, la estructura ingresada es pos con valor, texto, itemdata valor */
        case 6: // Periodo
        case 7: // Dia de cobro
        case 8: // Forma de pago incompleto
        {
            QComboBox *c = qobject_cast<QComboBox *>(editor);
            // pongo el item que corresponda segun el dato
            model->setData( index, c->itemData( c->currentIndex() ).toInt() );
            break;
        }
        default:
        {  QItemDelegate::setEditorData( editor, index ); break; }
    }
}
