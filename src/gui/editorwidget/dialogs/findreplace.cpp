/***************************************************************************
 *   Copyright (C) 2021 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#include "findreplace.h"
#include "codeeditor.h"
#include "basedebugger.h"

FindReplace::FindReplace( QWidget* parent )
           : QDialog( parent )
{
    setupUi(this);
    m_editor = NULL;
}

/*void FindReplace::on_findEdit_textEdited( QString text )
{

}

void FindReplace::on_replaceEdit_textEdited( QString text )
{

}*/

void FindReplace::on_prevButton_clicked()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    m_editor->setFound( extraSelections );
    find( false );
}
void FindReplace::on_nextButton_clicked()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    m_editor->setFound( extraSelections );
    find( true );
}

void FindReplace::on_allButton_clicked()
{
    QTextCursor tc = m_editor->textCursor();
    int pos = tc.position();
    tc.setPosition( 0 );
    m_editor->setTextCursor( tc );
    QList<QTextEdit::ExtraSelection> extraSelections;

    int i=0;
    while( find( true ) )
    {
        QTextEdit::ExtraSelection extra;
        extra.cursor = m_editor->textCursor();
        extra.format.setBackground( QBrush(QColor(240,240,0)) );
        extraSelections.append( extra );
        i++;
    }
    showMsg( tr("Found %1 occurrence(s)").arg(i) );

    tc.setPosition( pos );
    m_editor->setTextCursor( tc );
    m_editor->setFound( extraSelections );
}

void FindReplace::on_replaceButton_clicked()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    m_editor->setFound( extraSelections );

    if( m_editor->textCursor().hasSelection() )
        m_editor->textCursor().insertText( replaceEdit->text() );
}

void FindReplace::on_replFindButton_clicked()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    m_editor->setFound( extraSelections );

    if( m_editor->textCursor().hasSelection() )
        m_editor->textCursor().insertText( replaceEdit->text() );
    find( true );
}

void FindReplace::on_replAllButton_clicked()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    m_editor->setFound( extraSelections );

    m_textCursor.setPosition( 0 );
    m_editor->setTextCursor( m_textCursor );

    int i=0;
    while( find( true ) )
    {
        m_editor->textCursor().insertText( replaceEdit->text() );
        i++;
    }
    showMsg( tr("Replaced %1 occurrence(s)").arg(i) );
}

void FindReplace::on_closeButton_clicked()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    m_editor->setFound( extraSelections );
    hide();
}

void FindReplace::on_caseS_toggled( bool  )
{

}

void FindReplace::on_whole_toggled( bool  )
{

}

void FindReplace::on_regexp_toggled( bool )
{

}

bool FindReplace::find( bool next )
{
    if( !m_editor ) return false;

    bool result = false;
    QString toSearch = findEdit->text();

    QTextDocument::FindFlags flags;

    if( !next )               flags |= QTextDocument::FindBackward;
    if( caseS->isChecked() )  flags |= QTextDocument::FindCaseSensitively;
    if( whole->isChecked() )  flags |= QTextDocument::FindWholeWords;
    if( regexp->isChecked() )
    {
        /* FIXME: DDING
        QRegularExpression reg( toSearch, (caseS->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive) );

        m_textCursor = m_editor->document()->find( reg, m_textCursor, flags );
        m_editor->setTextCursor( m_textCursor );
        result = !m_textCursor.isNull();
        */
    }
    else result = m_editor->find( toSearch, flags );

    return result;
}

void FindReplace::showMsg( QString )
{

}
