#include "feedbackplugin.h"

#include <QString>
#include <QIcon>
#include <QAction>
#include <QMenuBar>
#include <QList>
#include <QStackedWidget>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

/*!
    \fn FeedbackPlugin::accionesBarra()
        Retorna las acciones que tiene la barra lateral para este plugin
        @return Lista de acciones
 */
QList<QActionGroup *> FeedbackPlugin::accionesBarra()
{ return QList<QActionGroup*>(); }


bool FeedbackPlugin::inicializar()
{
 //Q_INIT_RESOURCE(FeedbackPlugin);

/* ActBackup = new QAction( this );
 ActBackup->setText( "Backup Remoto" );
 ActBackup->setStatusTip( "Genera una copia de seguridad y la envía al servidor remoto" );
 ActBackup->setIcon( QIcon( ":/imagenes/backup.png" ) );
 connect( ActBackup, SIGNAL( triggered() ), this, SLOT( hacerBackup() ) );*/

 return true;
}

/*!
    \fn FeedbackPlugin::formsPreferencias()
 */
QWidgetList FeedbackPlugin::formsPreferencias()
{ return QWidgetList(); }

/*!
    \fn FeedbackPlugin::nombre() const
 */
QString FeedbackPlugin::nombre() const
{ return "feedback"; }


/*!
    \fn FeedbackPlugin::tipo() const
 */
int FeedbackPlugin::tipo() const
{ return EPlugin::comun; }


/*!
    \fn FeedbackPlugin::crearMenu( QMenuBar *m )
 */
void FeedbackPlugin::crearMenu( QMenuBar */*m*/ )
{
 return;
 /*QMenu *menuHer = m->findChild<QMenu *>( "menuArchivo" );
 menuHer->addSeparator();
 menuHer->addAction( ActBackup );*/
}

bool FeedbackPlugin::verificarTablas( QStringList )
{
 /*if( !QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).tables( QSql::Tables ).contains( "recibos" ) )
 {qWarning( "Error al buscar las tablas del plugin hi comp - recibos" ); return false; }*/
 return true;
}


/*!
    \fn FeedbackPlugin::version() const
 */
double FeedbackPlugin::version() const
{  return 0.1; }

/*!
    \fn FeedbackPlugin::crearToolBar( QToolBar *t )
 */
void FeedbackPlugin::crearToolBar( QToolBar */*t*/ )
{}


/*!
    \fn FeedbackPlugin::seCierraGestotux()
 */
void FeedbackPlugin::seCierraGestotux()
{
 //Q_CLEANUP_RESOURCE(backupremoto);
}

QAction *FeedbackPlugin::botonPantallaInicial()
{
    return ( new QAction( this ) );
}

Q_EXPORT_PLUGIN2( feedback, FeedbackPlugin )
