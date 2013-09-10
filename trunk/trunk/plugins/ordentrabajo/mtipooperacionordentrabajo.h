#ifndef MTIPOORDENTRABAJO_H
#define MTIPOORDENTRABAJO_H

#include <QSqlTableModel>

class MTipoOperacionOrdenTrabajo : public QSqlTableModel
{
    Q_OBJECT

public:

    enum TipoOperacionOrdenTrabajo {
        CambioTecnico = 1,
        CambioCliente = 2,
        CambioEquipamiento = 3
    };

    MTipoOperacionOrdenTrabajo(QObject *parent = 0);
    
    static bool existe( const QString nombre );
    bool tieneDatosRelacionados( const int id_tipo );

    bool agregarTipo( const QString nombre );
    bool modificar( const int row,  const QString nombre );
    
};

#endif // MTIPOORDENTRABAJO_H
