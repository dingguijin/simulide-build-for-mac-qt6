/***************************************************************************
 *   Copyright (C) 2018 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#ifndef AUDIOOUT_H
#define AUDIOOUT_H

#include <QAudioOutput>
#include <QAudioDevice>
#include <QAudioSink>

#include "e-resistor.h"
#include "component.h"

class LibraryItem;

class AudioOut : public Component, public eResistor
{
        Q_OBJECT
    public:
        AudioOut( QObject* parent, QString type, QString id );
        ~AudioOut();
    
 static Component* construct( QObject* parent, QString type, QString id );
 static LibraryItem* libraryItem();

        virtual void initialize() override;
        virtual void stamp() override;
        virtual void runEvent() override;

        bool buzzer() { return m_buzzer; }
        void setBuzzer( bool b ) { m_buzzer = b; }
        
        virtual QPainterPath shape() const override;
        virtual void paint( QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget ) override;

    //public slots:
    //    void stateChanged( QAudio::State state );

    private:
        QAudioDevice m_deviceinfo;
        QAudioFormat     m_format;  
        
        QAudioSink* m_audioOutput;
        QIODevice*    m_audioBuffer;
        QByteArray    m_dataBuffer;

        int m_dataSize;
        int m_dataCount;

        bool m_started;
        bool m_buzzer;
};

#endif


