#include "QGCodeSyntaxHighlighter.h"

#include <QSyntaxHighlighter>

#include "QGCodeEditor.h"

QGCodeSyntaxHighlighter::QGCodeSyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {
    HighlightingRule rule;

    //  The escape sequence \s should denote a space and it says so in the docs
    //  but if you use it you get a 'unrecognised escape char' warning so use \x20 instead

    M_WordFormat.setForeground(Qt::red);
    M_WordFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("[mMtT][^\x20]*");
    rule.format = M_WordFormat;
    highlightingRules.append(rule);

    G_WordFormat.setForeground(Qt::green);
    G_WordFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("[gG][^\x20]*");
    rule.format = G_WordFormat;
    highlightingRules.append(rule);

    F_WordFormat.setForeground(Qt::yellow);
    F_WordFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("[fF][^\x20 ]*");
    rule.format = F_WordFormat;
    highlightingRules.append(rule);

    S_WordFormat.setForeground(Qt::magenta);
    S_WordFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("[sS][^\x20 ]*");
    rule.format = S_WordFormat;
    highlightingRules.append(rule);

    PQ_WordFormat.setForeground(Qt::green);
    PQ_WordFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("[pPqQ][^\x20 ]*");
    rule.format = PQ_WordFormat;
    highlightingRules.append(rule);

    XYZ_WordFormat.setForeground(Qt::yellow);
    XYZ_WordFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("[xXyYzZaAbBcCuUvVwW][^\x20 ]*");
    rule.format = XYZ_WordFormat;
    highlightingRules.append(rule);

    IJKR_WordFormat.setForeground(Qt::darkGray);
    IJKR_WordFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("[iIjJkKrR][^\x20 ]*");
    rule.format = IJKR_WordFormat;
    highlightingRules.append(rule);

    Param_WordFormat.setForeground(Qt::cyan);
    Param_WordFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("#[^\x20 ]*");
    rule.format = Param_WordFormat;
    highlightingRules.append(rule);

    // do comments last then won't get colouring of text containing M G F S T etc
    semicolonCommentFormat.setForeground(Qt::white);
    semicolonCommentFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(";[^\n]*");
    rule.format = semicolonCommentFormat;
    highlightingRules.append(rule);

    braceCommentFormat.setForeground(Qt::magenta);
    braceCommentFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("\\([^\n]*");
    rule.format = braceCommentFormat;
    highlightingRules.append(rule);
}

void QGCodeSyntaxHighlighter::highlightBlock(const QString &text) {
    foreach(const HighlightingRule &rule, highlightingRules) {
        QRegularExpression expression(rule.pattern);
        auto iter = expression.globalMatchView(text);
        while (iter.hasNext()) {
            auto match = iter.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    setCurrentBlockState(0);
}
