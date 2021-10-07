#include "loadingbutton.h"
#include <QHBoxLayout>
#include <QLabel>
#include "buttonicon.h"

LoadingButton::LoadingButton(QWidget* parent)
    : QPushButton(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);

    m_buttonIcon = new ButtonIcon;
    m_textLabel = new QLabel();

    m_textLabel->setAlignment(Qt::AlignLeft);
    m_textLabel->setAlignment(Qt::AlignVCenter);

    layout->addWidget(m_buttonIcon);
    layout->addWidget(m_textLabel);
    layout->setSpacing(20);
    layout->setContentsMargins(10, 0, 10, 0);

    setLayout(layout);
}

void LoadingButton::showLoading(bool bShow)
{
    if (bShow) {
        m_buttonIcon->showLoadingAnimation();
    } else {
        m_buttonIcon->hideLoadingAnimation();
    }
}

void LoadingButton::setIcon(const QString &url)
{
    m_buttonIcon->setIcon(url);
}

void LoadingButton::setLoadingPng(const QString &url, int pngWidthPx, int pngHeightPx)
{
    m_buttonIcon->setLoadingPng(url, pngWidthPx, pngHeightPx);
}

void LoadingButton::setText(const QString &text)
{
    m_textLabel->setText(text);
}
