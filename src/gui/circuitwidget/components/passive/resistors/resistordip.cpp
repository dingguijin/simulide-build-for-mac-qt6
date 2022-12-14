/***************************************************************************
 *   Copyright (C) 2016 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#include "resistordip.h"
#include "circuitwidget.h"
#include "itemlibrary.h"
#include "connector.h"
#include "simulator.h"
#include "circuit.h"
#include "pin.h"
#include "e-resistor.h"
#include "label.h"

#include "doubleprop.h"
#include "intprop.h"

Component* ResistorDip::construct( QObject* parent, QString type, QString id )
{ return new ResistorDip( parent, type, id ); }

LibraryItem* ResistorDip::libraryItem()
{
    return new LibraryItem(
        tr( "ResistorDip" ),
        tr( "Resistors" ),
        "resistordip.png",
        "ResistorDip",
        ResistorDip::construct);
}

ResistorDip::ResistorDip( QObject* parent, QString type, QString id )
           : Component( parent, type, id )
           , eElement( id )
{
    m_size = 0;
    setSize( 8 );

    setLabelPos(-24,-40, 0);
    setValLabelPos( 5,-26, 90 );
    m_valLabel->setAcceptedMouseButtons( Qt::NoButton );

    addPropGroup( { tr("Main"), {
new DoubProp<ResistorDip>( "Resistance", tr("Resistance"),"Ω"       , this, &ResistorDip::getRes, &ResistorDip::setRes ),
new IntProp <ResistorDip>( "Size"      , tr("Size")      ,"_Resist.", this, &ResistorDip::size,   &ResistorDip::setSize, "uint" )
    } } );

    setShowProp("Resistance");
    setPropStr( "Resistance", "100" );
}
ResistorDip::~ResistorDip(){}

void ResistorDip::createResistors( int c )
{
    int start = m_size;
    m_size = m_size+c;
    m_resistor.resize( m_size );
    m_pin.resize( m_size*2 );

    for( int i=start; i<m_size; i++ )
    {
        int index = i*2;
        QString reid = m_id;
        reid.append(QString("-resistor"+QString::number(i)));
        m_resistor[i] = new eResistor( reid );

        m_pin[index] = new Pin( 180, QPoint(-16,-32+8+i*8 ), reid+"-ePin"+QString::number(index), 0, this);
        m_resistor[i]->setEpin( 0, m_pin[index] );

        m_pin[index+1] = new Pin( 0, QPoint( 16,-32+8+i*8 ), reid+"-ePin"+QString::number(index+1), 0, this);
        m_resistor[i]->setEpin( 1, m_pin[index+1] );
}   }

void ResistorDip::deleteResistors( int d )
{
    if( d > m_size ) d = m_size;
    int start = m_size-d;

    for( int i=start*2; i<m_size*2; ++i )
    {
        m_pin[i]->removeConnector();
        delete m_pin[i];
    }
    for( int i=start; i<m_size; i++ ) delete m_resistor[i];
    m_size = m_size-d;
    m_resistor.resize( m_size );
    m_pin.resize( m_size*2 );
}

void ResistorDip::setRes( double resist )
{
    for( eResistor* res : m_resistor ) res->setRes( resist );
    m_resist = resist;
}

void ResistorDip::setSize( int size )
{
    if( Simulator::self()->isRunning() )  CircuitWidget::self()->powerCircOff();
    
    if( size == 0 ) size = 8;
    if     ( size < m_size ) deleteResistors( m_size-size );
    else if( size > m_size ) createResistors( size-m_size );
    
    m_area = QRect( -10, -30, 20, m_size*8+4 );
    Circuit::self()->update();
}

void ResistorDip::remove()
{
    deleteResistors( m_size );
    Component::remove();
}

void ResistorDip::paint( QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    Component::paint( p, option, widget );
    p->drawRoundedRect( QRect( -9, -28, 18, m_size*8 ), 2, 2 );
}
