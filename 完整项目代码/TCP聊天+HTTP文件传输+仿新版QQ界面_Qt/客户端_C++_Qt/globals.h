#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>
#include <QSet>
#include <QRgb>
#include <QImage>
#include <QImage>
#include <qmath.h>
#include <QVector>
#include <QProcess>

extern QString MATCH_KEY; // 匹配密钥,确认是在发送文件
extern QSet<QString> valid_download_link;

void GaussiamBlur(int r, qreal variance, QImage &img); // 参数说明：模糊半径r，方差variance，QImage图像

// 启动py脚本下载文件
void starDoload(QString args1, QString args2); // 保存路径，url

#endif // GLOBALS_H
