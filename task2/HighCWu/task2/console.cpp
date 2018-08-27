#include "console.h"
#include <QTextCursor>
#include <QTextBlock>

static int last_flush;

/**
 * @name log
 * @namespace Console
 * @brief 用于打印日志到控制台
 * @param  text 欲打印到控制台的内容
 * @param  flush 是否更新同一行的输出内容
 * @return void
 */
void Console::log(const QString &text, const int &flush)
{
    QTextCursor cursor=m_consoleBox->textCursor();
    if(flush && flush==last_flush && flush_count > 0) {
        int position = m_consoleBox->document()->findBlockByNumber(m_consoleBox->document()->blockCount()-2).position();
        cursor.setPosition(position);
        cursor.select(QTextCursor::BlockUnderCursor);
        cursor.removeSelectedText();
    }
    if(flush && flush==last_flush) flush_count++;
    else if(flush && flush!=last_flush) flush_count=1;
    else flush_count=0;
    m_consoleBox->setText(m_consoleBox->toPlainText()+text+'\n');
    //保持编辑器在光标最后一行
    cursor.movePosition(QTextCursor::End);
    m_consoleBox->setTextCursor(cursor);
    last_flush=flush;
}
