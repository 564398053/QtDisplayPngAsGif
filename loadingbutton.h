#ifndef LOADINGBUTTON_H
#define LOADINGBUTTON_H

#include <QPushButton>
#include <QObject>

class ButtonIcon;
class QLabel;
class LoadingButton : public QPushButton
{
public:
    LoadingButton(QWidget* parent = nullptr);

    void showLoading(bool bShow);

    void setIcon(const QString& url);

    void setLoadingPng(const QString& url, int pngWidthPx, int pngHeightPx);

    void setText(const QString &text);

private:
    ButtonIcon* m_buttonIcon;
    QLabel* m_textLabel;
};

#endif // LOADINGBUTTON_H
