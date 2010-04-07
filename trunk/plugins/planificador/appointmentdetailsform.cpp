/*******************************************************************************

    Copyright (C) 2008 Jukka-Pekka Mäkelä.
    Contact: jpm@mehteenit.net

    This file is part of QuickCalendar.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QuickCalendar.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************/

#include <QtCore>
#include <QtGui>
#include "appointmentdetailsform.h"

/*!
    Constructor for AppointmentDetailsForm
*/
AppointmentDetailsForm::AppointmentDetailsForm(Appointment *appointment,
                                               QList <Calendar *> *calendars,
                                               QWidget *parent) :
    QWidget(parent), ptrAppointment(appointment)
{
    setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose, true);

    QRegExp subjectRx("^.{3,45}$");
    subjectEdit->setValidator(new QRegExpValidator(subjectRx, this));

    ptrCalendars = new QList <Calendar *>();

    // Create icons for calendar combobox.
    QListIterator <Calendar *> i(*calendars);
    int j = 0;
    while(i.hasNext())
    {
        Calendar *cal = i.next();

        if(cal->isSelected())
        {
            QPixmap map(16,16);
            map.fill(cal->color());
            QIcon icon(map);

            calendarCombo->addItem(icon, cal->name(), cal->key());

            ptrCalendars->append(cal);

            if(appointment->calendar() != 0)
                if(cal == appointment->calendar())
                    calendarCombo->setCurrentIndex(j);

            j++;
        }
    }

    startDateEdit->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    startDateEdit->setDate(appointment->startDate());
    startTimeEdit->setTime(appointment->startTime());

    endDateEdit->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    endDateEdit->setDate(appointment->endDate());
    endTimeEdit->setTime(appointment->endTime());

    subjectEdit->setText(appointment->subject());
    placeEdit->setText(appointment->place());
    descriptionEdit->setPlainText(appointment->description());

    if(ptrAppointment->key() == 0)
        deleteAppointmentButton->hide();    

    connect(startDateEdit, SIGNAL(dateTimeChanged(const QDateTime &)),
            this, SLOT(startDateTimeChanged(const QDateTime &)));
    connect(startTimeEdit, SIGNAL(dateTimeChanged(const QDateTime &)),
            this, SLOT(startDateTimeChanged(const QDateTime &)));
    connect(endDateEdit, SIGNAL(dateTimeChanged(const QDateTime &)),
            this, SLOT(endDateTimeChanged(const QDateTime &)));
    connect(endTimeEdit, SIGNAL(dateTimeChanged(const QDateTime &)),
            this, SLOT(endDateTimeChanged(const QDateTime &)));

    connect(saveChangesButton, SIGNAL(clicked()), this, SLOT(onSaveChanges()));
    connect(discardChangesButton, SIGNAL(clicked()), this, SLOT(onDiscardChanges()));
    connect(deleteAppointmentButton, SIGNAL(clicked()), this, SLOT(onDeleteAppointment()));

    connect(subjectEdit, SIGNAL(returnPressed()), this, SLOT(onSaveChanges()));
    connect(placeEdit, SIGNAL(returnPressed()), this, SLOT(onSaveChanges()));
}

/*!
    If form data is valid saves changes.
*/
void AppointmentDetailsForm::onSaveChanges()
{
    // Validate subject
    QString subject = subjectEdit->text();
    int pos = 0;
    if(subjectEdit->validator()->validate(subject, pos) != QValidator::Acceptable)
    {
        QMessageBox::warning(0, QObject::tr("Invalid data!"), QObject::tr("Subject must be 3-45 characters long!"));
        return;
    }

    QDateTime start(startDateEdit->date(), startTimeEdit->time());
    QDateTime end(endDateEdit->date(), endTimeEdit->time());

    ptrAppointment->setDateTimes(start, end);
    ptrAppointment->setSubject(subjectEdit->text());
    ptrAppointment->setPlace(placeEdit->text());
    ptrAppointment->setDescription(descriptionEdit->toPlainText());

    if(ptrAppointment->key() == 0) 
    {
        Calendar *cal = ptrCalendars->at(calendarCombo->currentIndex());
        cal->insertAppointment(ptrAppointment);
    }

    this->close();
}

/*!
    Discards all changes.
*/
void AppointmentDetailsForm::onDiscardChanges()
{
    this->close();
}

/*!
    Deletes appointment.
*/
void AppointmentDetailsForm::onDeleteAppointment()
{
    Calendar *cal = ptrAppointment->calendar();
    cal->removeAppointment(ptrAppointment);
    this->close();
}

/*!
    Event handler for start date and time changes.
*/
void AppointmentDetailsForm::startDateTimeChanged(const QDateTime &datetime)
{
    if (startDateEdit->date() > endDateEdit->date())
    {
        endDateEdit->setDate(startDateEdit->date());
    }

    if (startDateEdit->date() == endDateEdit->date() &&
        startTimeEdit->time() > endTimeEdit->time().addSecs(-3600))
    {
        if(endTimeEdit->time() < QTime(23,0,0))
        {
            endTimeEdit->setTime(startTimeEdit->time().addSecs(3600));
        }else
        {            
            endTimeEdit->setTime(QTime(23,59,59));

            if(startTimeEdit->time() > QTime(23,0,0))
                startTimeEdit->setTime(QTime(23,0,0));
        }
    }
}

/*!
    Event handler for end date and time changes.
*/
void AppointmentDetailsForm::endDateTimeChanged(const QDateTime &datetime)
{
    if (endDateEdit->date() < startDateEdit->date())
    {
        startDateEdit->setDate(endDateEdit->date());
    }

    if ((startDateEdit->date() == endDateEdit->date() &&
        endTimeEdit->time() < startTimeEdit->time().addSecs(3600)) ||
        (startDateEdit->date() == endDateEdit->date() &&
       startTimeEdit->time() == QTime(23,0,0) &&
       endTimeEdit->time() < QTime(23,59,59)))
    {
        if(startTimeEdit->time() >= QTime(1,0,0))
        {
            startTimeEdit->setTime(endTimeEdit->time().addSecs(-3600));
        }else
        {
            startTimeEdit->setTime(QTime(0,0,0));

            if(endTimeEdit->time() < QTime(1,0,0))
                endTimeEdit->setTime(QTime(1,0,0));
        }
    }
}

/*!
    Event handler form close.
*/
void AppointmentDetailsForm::closeEvent(QCloseEvent *event)
{
    emit onClose(ptrAppointment);
}
