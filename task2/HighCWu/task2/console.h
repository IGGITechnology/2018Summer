#ifndef CONSOLE_H
#define CONSOLE_H

#include <QTextEdit>
#include <QTextStream>

/**
 * @class Console
 * @brief 用于打印日志到控制台
 * @return
 */
class Console
{
public:
    Console() {}
    Console(QTextEdit *consoleBox):m_consoleBox(consoleBox),flush_count(0) {} // Console构造函数，参数为Console输出文本的QTextEdit的头指针
    void log(const QString &text, const int &flush=0);
private:
    QTextEdit* m_consoleBox;
    int flush_count;
};

#endif // CONSOLE_H
