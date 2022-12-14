/***************************************************************************
 *   Copyright (C) 2021 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#ifndef STRINGPROP_H
#define STRINGPROP_H

#include "strprop.h"

template <class Comp>
class MAINMODULE_EXPORT StringProp : public StrProp
{
    public:
        StringProp( QString name, QString caption, QString unit, Comp* comp
                  , QString (Comp::*getter)(), void (Comp::*setter)(QString), QString type="string" )
        : StrProp( name, caption, unit, type )
        {
            m_comp = comp;
            m_getter = getter;
            m_setter = setter;
        }
        ~StringProp(){;}

        virtual void setValStr( QString val ) override
        {
            if( m_comp->showProp() == m_name ) m_comp->setValLabelText( val );
            (m_comp->*m_setter)( setStr( val ) ); // Comp setter can change valLabel
        }

        virtual QString getValStr() override
        { return (m_comp->*m_getter)(); }

        virtual QString toString() override { return getStr( (m_comp->*m_getter)() ); }

    private:
        Comp* m_comp;
        QString (Comp::*m_getter)();
        void    (Comp::*m_setter)(QString);
};

#endif
