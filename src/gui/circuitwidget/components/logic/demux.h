/***************************************************************************
 *   Copyright (C) 2016 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#ifndef DEMUX_H
#define DEMUX_H

#include "logiccomponent.h"

class LibraryItem;

class MAINMODULE_EXPORT Demux : public LogicComponent
{
        Q_OBJECT
    public:
        Demux( QObject* parent, QString type, QString id );
        ~Demux();

        static Component* construct( QObject* parent, QString type, QString id );
        static LibraryItem* libraryItem();

        virtual void stamp() override;
        virtual void voltChanged() override;
        virtual void runEvent() override{ IoComponent::runOutputs(); }

        int addrBits() { return m_addrBits; }
        void setAddrBits( int bits );
        
        virtual QPainterPath shape() const override;
        virtual void paint( QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget ) override;

    private:
        int m_addrBits;
};

#endif

