#include "globals.h"

QString MATCH_KEY = "RbURpoNPc2MAcHknE1Gm";
QSet<QString> valid_download_link = QSet<QString>();

void GaussiamBlur(int r, qreal variance, QImage &img)
{
    if (variance < 0)
    {
        throw "variance must be greater than 0";
    }
    if (r == 0)
    {
        return;
    }

    // lambda函数说明：x：模糊半径，o：方差，返回：1维高斯函数的运算结果
    auto Gaussian1D = [](qreal x, qreal variance_) -> qreal
    { return (qExp(-(qPow(x, 2) / (2 * qPow(variance_, 2))))) / (variance_ * 2 * M_PI); };

    int imgw = img.width();
    int imgh = img.height();

    int kernelSize = 2 * r + 1;
    int twor = 2 * r;
    QVector<qreal> weight(kernelSize);
    qreal weightsum = 0.0;

    // 生成高斯核
    for (int i = 0; i <= twor; i++)
    {
        weight[i] = Gaussian1D(i - r, variance);
        weightsum += weight[i];
    }
    // 权重和归一化
    for (auto &i : weight)
    {
        i /= weightsum;
    }

    // 这部分使用快速高斯模糊算法：用一维高斯函数处理两次，降低时间复杂度
    // 边缘处理忽略，但在一个方向上至少会处理一次
    // 使用滑动窗口算法

    // 横向
    for (int y = 0; y < imgh; y++)
    {
        QVector<qreal> tempred(imgw);
        QVector<qreal> tempgreen(imgw);
        QVector<qreal> tempblue(imgw);
        qreal redsum = 0;
        qreal greensum = 0;
        qreal bluesum = 0;

        for (int x = 0; x < imgw; x++)
        {
            QColor color(img.pixel(x, y));
            int q = x % kernelSize;
            tempred[x] = color.red() * weight[q];
            tempgreen[x] = color.green() * weight[q];
            tempblue[x] = color.blue() * weight[q];

            redsum += tempred[x];
            greensum += tempgreen[x];
            bluesum += tempblue[x];

            if (x >= twor)
            {
                img.setPixel(x - r, y, qRgb(redsum, greensum, bluesum));
                redsum -= tempred[x - twor];
                greensum -= tempgreen[x - twor];
                bluesum -= tempblue[x - twor];
            }
        }
    }

    // 纵向
    for (int x = 0; x < imgw; x++)
    {
        QVector<qreal> tempred(imgw);
        QVector<qreal> tempgreen(imgw);
        QVector<qreal> tempblue(imgw);
        qreal redsum = 0;
        qreal greensum = 0;
        qreal bluesum = 0;

        for (int y = 0; y < imgh; y++)
        {
            QColor color(img.pixel(x, y));
            int q = y % kernelSize;
            tempred[y] = color.red() * weight[q];
            tempgreen[y] = color.green() * weight[q];
            tempblue[y] = color.blue() * weight[q];

            redsum += tempred[y];
            greensum += tempgreen[y];
            bluesum += tempblue[y];

            if (y >= twor)
            {
                img.setPixel(x, y - r, qRgb(redsum, greensum, bluesum));
                redsum -= tempred[y - twor];
                greensum -= tempgreen[y - twor];
                bluesum -= tempblue[y - twor];
            }
        }
    }
}

void starDoload(QString args1, QString args2)
{
    const QString executable = "./fileDownload.exe";
    const QStringList args = {args1, args2};

    // 使用 QProcess::startDetached 启动可执行文件
    QProcess::startDetached(executable, args);
}
