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
#include "vcalendario.h"

#include "estilocalendario.h"

VCalendario::VCalendario(QWidget *parent) :
    QGraphicsView(new QGraphicsScene(), parent)
{
 pEstilo = new EstiloCalendario();
 _modoMostrar = MostrarSemanasCompletas;

 pPanelContenido = new ItemCalendario();
 scene()->addItem( pPanelContenido );

 pCabecera = new ItemCalendario();

 scene()->addItem( pCabecera );
 scene()->setBackgroundBrush( QColor( 127, 127, 127 ) );

 for( int i=1; i<=7; i++ ) {
     ItemCabeceraDiaSemana *item = new ItemCabeceraDiaSemana( this, i, pCabecera );
 }

 _diaSemanaExpandido = 0;
 _itemDiaSemanaExpandido = 0;

 _fechaExpandida = QDate( 0,0,0 );

 _contadorSemanas = 0;

 pCalendarios = new QList<Calendario *>();

 setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
 setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
 setFrameShape(QFrame::NoFrame);
 setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}

void VCalendario::setearModoMostrar( ModoMostrar modo )
{
    if( modo != _modoMostrar )
    {
        _modoMostrar = modo;
        setearCalendarios( _rangoInicio, _rangoFin );
    }
}

void VCalendario::setearCalendarios( const QDate &inicio, const QDate &fin )
{
  colapsarTodo();
  if( _semanas.cout() > 0 )
  {
      qDeleteAll(_semanas);
      _semanas.clear();
  }

  _rangoInicio = inicio;
  _rantoFin = fin;

  if( _rangoFin < _rangoInicio )
      _rangoFin = _rangoInicio;

  if( _rangoInicio.daysTo(_rangoFin) > (7*10)-1 )
      _rangoFin = _rangoInicio.addDays( (7*10)-1 );
  if( _modoMostrar == MostrarSemanasCompletas )
  {
      _rangoInicio = _rangoInicio.addDays( -(_rangoInicio.dayOfWeek() - 1 ) );
      _rangoFin = _rangoFin.addDays( 7-_rangoFin.dayOfWeek() );

      _contadorSemanas = (_rangoInicio.daysTo(_rangoFin) + 1 ) / 7;

      for( int i=0; i<_contadorSemanas; i++ )
      {
          ItemSemana *semana;
          if( i == 0 )
          {
              semana = new ItemSemana( this, _rangoInicio, _rangoFin, pPanelContenido );
          }
          else
          {
              semana = new ItemSemana( this, _rangoInicio.addDays(i*7), _rangoFin, pPanelContenido );
          }

          _semanas.append(semana);
      }
      dataChanged();

      if( _contadorSemanas == 1 )
          expandirSemana( _semanas.at(0));
      else
          layoutChanged();

  }
  else if( _modoMostrar == MostrarRango )
  {
    _fechaInicio = _rangoInicio;


    if( _rangoFin.daysTo(_rangoFin) > 13 )
        _rangoFin = _rangoInicio.addDays(13);

    _fechaFin = _rangoFin;

    ItemSemana *semana = new ItemSemana( this, _rangoInicio, _rangoFin, pPanelContenido );
    _semanas.append(semana);

    _contadorSemanas = 1;
    dataChanged();
    expandirSemana(semana);
  }
}

void VCalendario::setearMes( int ano, int mes )
{
 QDate inicio( ano, mes, 1);
 QDate fin = start.addDays( inicio.daysInMonth() - 1 );

 setearRango( inicio, fin );
}

void VCalendario::setearCalendarios( QList<Calendarios *>* cal )
{
   pCalendarios = cal;
}

void VCalendario::expandirFecha( const QDate &fecha )
{
 bool semanaCambiada = false;

 if( fecha != _fechaExpandida )
 {
     QListIterator <ItemSemana *> i(_semanas);
     while( i.hasNext())
     {
         ItemSemana *semana = i.next();

         int diaDeSemana = semana->diaDeSemana(fecha);
         if( diaDeSemana >= 0 )
         {
             if( _itemSemanaExpandido != semana )
             {
                 semanaCambiada = true;
             }

             _itemSemanaExpandido = semana;
             _DiaSemanaExpandido = diaDeSemana;
             _fechaExpandida = fecha;
             i.toBack();

             emit fechaExpandida();
         }
     }
 }
 else
 {
     _DiaSemanaExpandido = 0;
     _fechaExpandida = QDate( 0, 0, 0 );
 }

 layoutChanged();

 if( _itemSemanaExpandido != 0 && semanaCambiada )
     _itemSemanaExpandido->ptrScrollArea->scrollTo( pEstilo->quarterHeight * 4 * 7 );
}

void VCalendario::expandirSemana( int numero )
{
    QListIterator<ItemSemana *> i(_semanas);
    while(i.hasNext())
    {
        ItemSemana *semana = i.next();

        if(semana->myDate.weekNumber() == numero)
        {
            expandirSemana( semana );
            i.toBack();
        }
    }
}

void VCalendario::expandirSemana(ItemSemana *semana)
{
    if(semana != _itemSemanaExpandido)
    {
        _itemSemanaExpandido = semana;
    }else
    {
        if(_semanas.count() > 1)
        {
            _itemSemanaExpandido = 0;
            _DiaSemanaExpandido = 0;
            _fechExpandida = QDate(0,0,0);
        }
    }

    layoutChanged();

    if(_itemSemanaExpandido != 0)
        _itemSemanaExpandido->ptrScrollArea->scrollTo(pEstilo->quarterHeight * 4 * 7);
}

int VCalendario::expandirDiaDeSemana() const
{
    if(_itemSemanaExpandido != 0)
        return _itemSemanaExpandido->myDate.numeroSemana();
    else
        return 0;
}

void VCalendario::colapsarTodo()
{
    if(_itemSemanaExpandido != 0)
    {
        if(_semanas.count() > 1)
        {
            _itemSemanaExpandido = 0;
            _DiaSemanaExpandido = 0;
            _fechaExpandida = QDate(0,0,0);
            layoutChanged();
        }
    }
}

void VCalendario::resizeEvent(QResizeEvent *event)
{  layoutChanged(); }

void VCalendario::layoutChanged()
{
    if(_semanas.count() == 0)
        return;

    int ancho = this->width();
    int alto = this->height();


    setSceneRect( 0, 0, ancho, alto );

    // Calculate day widths
    int anchoAreaTrabajo = ancho - pEstilo->weekLeftMargin - pEstilo->weekRightMargin;

    for( int i=0; i<21; i++ )
        _anchoDias[i] = 0;

    int contadorDias;
    int primerDia = 0;

    if( _modoMostrar == MostrarSemanasEnteras)
        contadorDias = 7;
    else if(_modoMostrar == MostrarRango)
    {
        primerDia = _fechaInicio.dayOfWeek() - 1;
        contadorDias = _fechaInicio.daysTo(_fechaFin) + 1;
    }

    if(contadorDias > 1)
    {
        if(_DiaSemanaExpandido != 0)
        {
            int expandedDayWidth = (workAreaWidth / 3) * 2;
            workAreaWidth -= expandedDayWidth;
            int dayWidth = workAreaWidth / (dayCount - 1);
            int mod = workAreaWidth % (dayCount - 1);

            for(int i=firstDay;i<firstDay+dayCount;i++)
            {
                if(i == firstDay + _DiaSemanaExpandido - 1)
                {
                    _anchoDias[i] = expandedDayWidth + mod;
                }else
                {
                    _anchoDias[i] = dayWidth;
                }
            }
        }else
        {
            int dayWidth = workAreaWidth / dayCount;
            int mod = workAreaWidth % dayCount;

            for(int i=firstDay;i<firstDay+dayCount;i++)
            {
                _anchoDias[i] = dayWidth;
            }
            _anchoDias[firstDay] += mod;
        }
    }else
    {
        _anchoDias[firstDay] = workAreaWidth;
    }

//    for(int i=0;i<21;i++)
//    {
//        qDebug(qPrintable("W: [" + QString::number(i) + "] = " + QString::number(_anchoDias[i])));
//    }

    int weekTop = 0;
    int weekHeight = 0;
    int expandedWeekHeight = 0;

    if(_contadorSemanas > 1)
    {
        int headerLeft = 0;
        int headerCount = 0;
        int headerHeight = 40 + (height - 40)%_semanas.count();

        pCabecera->setPos(pEstilo->weekLeftMargin, 0);
        pCabecera->setSize(width, headerHeight);
        pCabecera->setVisible(true);

        QListIterator <QGraphicsItem *> i(pCabecera->childItems());
        while(i.hasNext())
        {
            WeekDayHeaderItem *item = (WeekDayHeaderItem *)i.next();
            item->setPos(headerLeft, 0);
            item->setSize(_anchoDias[headerCount], headerHeight);
            item->layoutChanged();

            headerLeft += _anchoDias[headerCount];

            headerCount++;
        }

        weekTop = headerHeight;
    }else
    {
        pCabecera->setVisible(false);
    }

    if(_itemSemanaExpandido != 0)
    {
        expandedWeekHeight = (height - weekTop) - ((_contadorSemanas - 1) *
                                  pEstilo->collapsedWeekHeight());
        weekHeight = pEstilo->collapsedWeekHeight();
    }else
    {
        weekHeight = (height - weekTop)/_semanas.count();
    }

    for(int i=0;i<_semanas.count();i++)
    {
        ItemSemana *semana = _semanas.at(i);

        semana->setPos(0, weekTop);
        if(semana == _itemSemanaExpandido)
        {
            semana->setSize(width, expandedWeekHeight);
            weekTop += expandedWeekHeight;
        }else
        {
            semana->setSize(width, weekHeight);
            weekTop += weekHeight;
        }

        semana->layoutChanged();
    }

    //update();
}

void VCalendario::showAppointmentForm(Cita *Cita)
{
    bool someSelected = false;

    for(int i=0;i<pCalendarios->count();i++)
    {
        if(pCalendarios->at(i)->isSelected())
            someSelected = true;
    }

    if(!someSelected)
    {
        QMessageBox::warning(0, QObject::tr("Calendar error"), QObject::tr("Select at least one calendar first!"));
        return;
    }

    if(pCalendarios->count() > 0)
    {
        AppointmentDetailsForm *form = new AppointmentDetailsForm(Cita,
                                                                  pCalendarios);

        connect(form, SIGNAL(onClose(Cita*)), this, SLOT(onFormClosed(Cita*)));

        if(Cita->key() == 0)
            form->deleteAppointmentButton->hide();

        form->setGeometry(300,300,400,250);
        form->show();

    }
}

void VCalendario::dataChanged()
{
    QListIterator <ItemSemana *> i(_semanas);
    while(i.hasNext())
    {
        ItemSemana *semana = i.next();
        semana->dataChanged();
    }
}

void VCalendario::onFormClosed(Cita *Cita)
{
    if(Cita != 0)
    {
        dataChanged();
        layoutChanged();
    }
}

void VCalendario::expandDayOfWeek(int dayOfWeek)
{
    if(_itemSemanaExpandido != 0)
    {
        if(dayOfWeek != _DiaSemanaExpandido)
            _DiaSemanaExpandido = dayOfWeek;
        else
            _DiaSemanaExpandido = 0;

        layoutChanged();
    }
}
