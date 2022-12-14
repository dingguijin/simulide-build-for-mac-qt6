/***************************************************************************
 *   Copyright (C) 2020 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#ifndef MCU_H
#define MCU_H

//#include <QHash>

#include "e_mcu.h"
#include "chip.h"

enum deviceType_t{
    typeNONE=0,
    typeIOU,
    typeMPU,
    typeMCU
};

class LibraryItem;
class MCUMonitor;

class MAINMODULE_EXPORT Mcu : public Chip
{
        Q_OBJECT

        friend class McuCreator;

    public:
        Mcu( QObject* parent, QString type, QString id );
        ~Mcu();

 static Mcu* self() { return m_pSelf; }
 static Component* construct( QObject* parent, QString type, QString id );
 static LibraryItem* libraryItem();

        void setup( QString type );

        virtual bool setPropStr( QString prop, QString val ) override;

        QString program() { return m_eMcu.getFileName(); }
        void setProgram( QString pro );

        bool autoLoad() { return m_autoLoad; }
        void setAutoLoad( bool al ) { m_autoLoad = al; }

        double freq() { return m_eMcu.m_freq; }
        void setFreq( double freq ) { m_eMcu.setFreq( freq ); }

        bool rstPinEnabled();
        void enableRstPin( bool en );

        bool extOscEnabled() { return m_extClock; }
        void enableExtOsc( bool en );

        bool wdtEnabled();
        void enableWdt( bool en );

        QString varList();
        void setVarList( QString vl );

        QString cpuRegs();
        void setCpuRegs( QString vl );

        void setEeprom( QString eep );
        QString getEeprom();

        int serialMon() { return m_serialMon; }
        void setSerialMon( int s );

        virtual void initialize() override;
        virtual void stamp() override;
        virtual void updateStep() override;
        virtual void voltChanged() override;
        virtual void remove() override;

        QString device() { return m_device; }

        void reset() { m_eMcu.hardReset( true ); }

        bool load( QString fileName );

        virtual void addPin( QString id, QString type, QString label,
                             int pos, int xpos, int ypos, int angle , int length=8) override;

        //void createCfgWord( QString name, uint16_t addr, uint16_t v );

        virtual QStringList getEnumUids( QString ) override;
        virtual QStringList getEnumNames( QString ) override;

        virtual void paint( QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget ) override;

    public slots:
        void slotmain();
        void slotLoad();
        void slotReload();
        void slotOpenTerm( int num );
        void slotOpenMcuMonitor();

        void loadEEPROM();
        void saveEEPROM();

    protected:
 static Mcu* m_pSelf;

        virtual void contextMenu( QGraphicsSceneContextMenuEvent* event, QMenu* menu ) override;
        virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

        deviceType_t m_deviceType;

        bool m_autoLoad;
        bool m_extClock;

        int m_serialMon;

        QString m_subcDir;      // Subcircuit Path
        QString m_lastFirmDir;  // Last firmware folder used
        QString m_dataFile;
        QString m_device;       // Name of device

        eMcu m_eMcu;

        IoPin*  m_resetPin;
        McuPin* m_portRstPin;
        McuPin* m_clkPin[2];

        QList<Pin*> m_pinList;

        MCUMonitor* m_mcuMonitor;
};

#endif
