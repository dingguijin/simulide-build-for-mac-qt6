/***************************************************************************
 *   Copyright (C) 2012 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

class QTextDocument;

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

    public:
        Highlighter( QTextDocument* parent = 0);
        ~Highlighter();

        void readsyntaxFile( const QString &fileName );

        void addRegisters( QStringList patterns );

    protected:
        void highlightBlock(const QString &text);

    private:
        struct HighlightRule
        {
            QRegularExpression pattern;
            QTextCharFormat format;
        };
        void addRule( QTextCharFormat, QString );
        void processRule( HighlightRule rule, QString lcText );

        bool m_multiline;
        
        QVector<HighlightRule> m_rules;

        QRegularExpression m_multiStart;
        QRegularExpression m_multiEnd;
        QTextCharFormat m_multiFormat;
};

#endif
