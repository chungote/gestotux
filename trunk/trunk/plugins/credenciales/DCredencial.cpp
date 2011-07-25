#include "DCredencial.h"

#include "EReporte.h"
#include "MCredenciales.h"
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlField>

DCredencial::DCredencial(QWidget *parent) :
    QDialog(parent), Ui::DCredencialBase()
{
    setupUi(this);
    this->setAttribute( Qt::WA_DeleteOnClose );
    this->setObjectName( "agregarcredencial" );
    this->setWindowTitle( "Crear Credencial" );
    this->equipo = "";
    this->id_equipo = -1;
    this->reporte = new EReporte( this );
    this->reporte->especial( "credencial-union", ParameterList() );
    this->modelo = new MCredenciales( this );
}

void DCredencial::accept()
{
    if( this->equipo.isEmpty() || this->id_equipo == -1 ) {
        qDebug( "Equipo no seteado" ); return;
    }
    // Verificaciones
    if( this->LEMedio->text().isEmpty() ) {
        QMessageBox::warning( this, "Error", "Por favor ingrese un medio para esta credencial" );
        return;
    }
    if( this->LENombre->text().isEmpty() ) {
        QMessageBox::warning( this, "Error", "Por favor ingrese un Nombre para esta credencial" );
        return;
    }
    if( this->LEDNI->text().isEmpty() ) {
        QMessageBox::warning( this, "Error", "Por favor ingrese un DNI para esta credencial" );
        return;
    }
    if( !this->CkBAcc1->isChecked() && !this->CkBAcc2->isChecked() && !this->CkBAcc3->isChecked() && !this->CkBAcc4->isChecked() && !this->CkBAcc5->isChecked() ) {
        QMessageBox::warning( this, "Error", "Por favor, elija un nivel de acceso para esta credencial" );
        return;
    }
    // Guardo el registro
    QSqlRecord rec = this->modelo->record();
    rec.remove( 0 );
    rec.setValue( "equipo_id", this->id_equipo );
    rec.setValue( "nombre", this->LENombre->text() );
    rec.setValue( "dni", this->LEDNI->text() );
    rec.setValue( "medio", this->LEMedio->text() );
    rec.setValue( "acc1", this->CkBAcc1->isChecked() );
    rec.setValue( "acc2", this->CkBAcc2->isChecked() );
    rec.setValue( "acc3", this->CkBAcc3->isChecked() );
    rec.setValue( "acc4", this->CkBAcc4->isChecked() );
    rec.setValue( "acc5", this->CkBAcc5->isChecked() );
    rec.setValue( "acc6", this->CkBAcc6->isChecked() );
    /*for( int i = 0; i<rec.count(); i++ ) {
        qDebug( QString( "%1: %2 - %3").arg( i ).arg( rec.fieldName( i ) ).arg( rec.value( i ).toString() ).toLocal8Bit() );
    }*/
    if( this->modelo->insertRecord( -1, rec ) ) {
        qDebug( "Registro insertado" );
        // imprimo la tarjeta
        ParameterList lista;
        lista.append( Parameter( "id", rec.value( "id_credencial" ) ) );
        if( this->reporte->hacer( lista ) ) {
            QMessageBox::information( this, "listo", "Credencial #%1 creada e impresa correctamente" );
            this->limpiarDatos();
        } else {
            qDebug( "No se pudo realizar el reporte" );
        }
    } else {
        qDebug( "Error al insertar los datos" );
        qDebug( this->modelo->lastError().text().toLocal8Bit() );
    }
}

void DCredencial::setearEquipo( const int id_equipo, const QString equipo ) {
    //qDebug( QString( "Union vs. %1").arg( equipo ).toLocal8Bit() );
    LPartido->setText( QString( "Union vs. %1" ).arg( equipo ) );
    this->equipo = equipo;
    this->id_equipo = id_equipo;
}

void DCredencial::limpiarDatos() {
    this->LENombre->setText( "" );
    this->LEDNI->setText( "" );
    this->LEMedio->setText( "" );
    this->CkBAcc1->setChecked( false );
    this->CkBAcc2->setChecked( false );
    this->CkBAcc3->setChecked( false );
    this->CkBAcc4->setChecked( false );
    this->CkBAcc5->setChecked( false );
    this->CkBAcc6->setChecked( false );
}
