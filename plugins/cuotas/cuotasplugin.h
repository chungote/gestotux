#ifndef CUOTASPLUGIN_H
#define CUOTASPLUGIN_H

#include <QObject>
#include <eplugin.h>
#include <QtPlugin>

/**
 * \brief Plugin de Cuotas
 *
 * @author Esteban Zeller <juiraze@yahoo.com.ar>
 */
class CuotasPlugin : public QObject, public EPlugin
{
    Q_OBJECT
    Q_INTERFACES(EPlugin)

    public:
        QList<QActionGroup *> accionesBarra();
        QString nombre() const;
        QWidgetList formsPreferencias();
        bool inicializar();
        bool verificarTablas( QStringList tablas );
        int tipo() const;
        void crearMenu( QMenuBar *m );
        double version() const;
        static QStackedWidget *tabs();
        void crearToolBar( QToolBar *t );
        bool publicidad() { return true; }
        QAction *botonPantallaInicial() { return new QAction( this ); }

    public slots:
        void seCierraGestotux();

    signals:
        void agregarVentana( QWidget * );
        void agregarDockWidget(Qt::DockWidgetArea area, QDockWidget *ventana);

    private slots:
        void verCuotas();
        void emitirVentaEnCuotas( int id_cliente, double total, int id_factura );
        void generarComprobantes();
        void simularCuotas();

    private:
        QAction *ActVerCuotas;
        QAction *ActGenerarComprobantes;
        QAction *ActSimular;

};

#endif // CUOTASPLUGIN_H
