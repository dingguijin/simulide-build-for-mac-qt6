/***************************************************************************
 *   Copyright (C) 2019 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#ifndef SUBPACKAGE_H
#define SUBPACKAGE_H

#include "chip.h"

class LibraryItem;
class QAction;

class MAINMODULE_EXPORT SubPackage : public Chip
{
    Q_OBJECT

    public:
        SubPackage( QObject* parent, QString type, QString id );
        ~SubPackage();
        
    static Component* construct( QObject* parent, QString type, QString id );
    static LibraryItem* libraryItem();

        int width() { return m_width; }
        void setWidth( int width );
        
        int height() { return m_height; }
        void setHeight( int height );
        
        QString  package();
        void setPackage( QString package );

        void savePackage( QString fileName );
        virtual void setSubcTypeStr( QString s ) override;
        virtual void setLogicSymbol( bool ls ) override;
        virtual void remove() override;

        virtual void paint( QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget ) override;

    public slots:
        virtual void contextMenu( QGraphicsSceneContextMenuEvent* event, QMenu* menu ) override;
        void invertPin( bool invert );
        void setPinId( QString id );
        void setPinName( QString name );
        void setPinType( QString type );
        void setPinAngle( int i);
        void boardMode();
        void savingCirc();
        void mainComp() { Component::m_selMainCo = true; }
    
    private slots:
        void loadPackage();
        void movePin();
        void editPin();
        void deleteEventPin();
        void unusePin( bool unuse );
        void pointPin( bool point );
        void slotSave();
        void editFinished( int r );

    protected:
        void mousePressEvent( QGraphicsSceneMouseEvent* event ) override;
        void mouseMoveEvent( QGraphicsSceneMouseEvent* event ) override;
        void hoverMoveEvent( QGraphicsSceneHoverEvent* event ) override;
        void hoverLeaveEvent( QGraphicsSceneHoverEvent* event ) override;
        
        virtual void contextMenuEvent( QGraphicsSceneContextMenuEvent* event ) override;

    private:
        QString pinEntry( Pin* pin );
        QString adjustSize( QString str, int size );

        void setBoardMode();

 static QString m_lastPkg;

        bool m_movePin;
        bool m_fakePin; // Data for drawing pin when hovering
        
        int m_angle;  
        int m_p1X;
        int m_p1Y;
        int m_p2X;
        int m_p2Y;

        bool m_circPosSaved;
        bool m_boardMode;
        QAction* m_boardModeAction;

        Pin* m_eventPin;
};

#include <QDialog>

class QLabel;
class QLineEdit;
class QCheckBox;
class QComboBox;

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    EditDialog( SubPackage* pack, Pin* eventPin, QWidget* parent = 0 );

private slots:
    void invertPin( bool invert );

private:
    SubPackage* m_package;

    QLabel*    m_nameLabel;
    QLineEdit* m_nameLineEdit;

    QLabel*    m_idLabel;
    QLineEdit* m_idLineEdit;

    QLabel*    m_typeLabel;
    QLineEdit* m_typeLineEdit;

    QLabel*    m_angleLabel;
    QComboBox* m_angleBox;

    QCheckBox* m_invertCheckBox;
    QCheckBox* m_unuseCheckBox;
    QCheckBox* m_pointCheckBox;
};

#endif

