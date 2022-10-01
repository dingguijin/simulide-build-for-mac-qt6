/***************************************************************************
 *   Copyright (C) 2022 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#ifndef SCR_H
#define SCR_H

#include "component.h"
#include "e-element.h"

class LibraryItem;
class eDiode;
class eResistor;

class MAINMODULE_EXPORT SCR : public Component, public eElement
{
        Q_OBJECT
    public:
        SCR( QObject* parent, QString type, QString id );
        ~SCR();

 static Component* construct( QObject* parent, QString type, QString id );
 static LibraryItem* libraryItem();

        virtual void initialize() override;
        virtual void stamp() override;
        virtual void voltChanged() override;

        double gateRes() { return m_gateRes; }
        void setGateRes( double r ) { m_gateRes = r; }

        double trigCurr() { return m_trigCurr; }
        void setTrigCurr( double c ) { m_trigCurr = c; }

        double holdCurr() { return m_holdCurr; }
        void setHoldCurr( double v ) { m_holdCurr = v; }

        virtual void paint( QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget ) override;

    private:
        double m_gateRes;
        double m_trigCurr;
        double m_holdCurr;

        bool m_state;

        eNode*     m_midEnode;
        eResistor* m_resistor;
        eResistor* m_resistGa;
        eDiode*    m_diode;
};

#endif
