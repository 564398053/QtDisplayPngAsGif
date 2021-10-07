/* ============================================================
* QupZilla - Qt web browser
* Copyright (C) 2014-2018 David Rosca <nowrep@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#include "buttonicon.h"

#include <QTimer>
#include <QToolTip>
#include <QMouseEvent>
#include <QPainter>


ButtonIcon::ButtonIcon(QWidget* parent)
    : QWidget(parent)
    , m_currentFrame(0)
    , m_animationRunning(false)
    , m_data(nullptr)
{
    setObjectName(QStringLiteral("buttonICon"));

    m_updateTimer = new QTimer(this);
    m_updateTimer->setInterval(data()->animationInterval);
    connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(updateAnimationFrame()));

    m_hideTimer = new QTimer(this);
    m_hideTimer->setInterval(250);
    connect(m_hideTimer, &QTimer::timeout, this, &ButtonIcon::hide);

    resize(m_iconSize, m_iconSize);
}

void ButtonIcon::showLoadingAnimation()
{
    m_currentFrame = 0;

    updateAnimationFrame();
    show();
}

void ButtonIcon::hideLoadingAnimation()
{
    m_animationRunning = false;

    m_updateTimer->stop();
    updateIcon();
}

void ButtonIcon::updateIcon()
{
    m_buttonPixmap = m_icon.pixmap(m_iconSize);
    if (m_buttonPixmap.isNull()) {
        hide();
    } else {
        show();
    }
    update();
}

void ButtonIcon::setIcon(const QString &url)
{
    m_icon = QIcon(url);
}

void ButtonIcon::setLoadingPng(const QString &url, int width, int height)
{
    data()->animationPixmap = QIcon(url).pixmap(width, height);

    if (data()->animationPixmap.height() != 0) {
        data()->framesCount = data()->animationPixmap.width() / data()->animationPixmap.height();
    } else {
        data()->framesCount = 1;
    }

    m_iconSize = height;
     setFixedSize(m_iconSize, qMax(minimumHeight(), m_iconSize));
}

ButtonIcon::Data *ButtonIcon::data()
{
    if (!m_data) {
        m_data = new ButtonIcon::Data;
        m_data->animationInterval = 40;
        if (m_data->animationPixmap.height() != 0) {
            m_data->framesCount = m_data->animationPixmap.width() / m_data->animationPixmap.height();
        } else {
            m_data->framesCount = 1;
        }
    }
    return m_data;
}

void ButtonIcon::updateAnimationFrame()
{
    if (!m_animationRunning) {
        m_updateTimer->start();
        m_animationRunning = true;
    }

    update();
    m_currentFrame = (m_currentFrame + 1) % data()->framesCount;
}

void ButtonIcon::show()
{
    if (!shouldBeVisible()) {
        return;
    }

    m_hideTimer->stop();

    if (isVisible()) {
        return;
    }

    setFixedSize(m_iconSize, qMax(minimumHeight(), m_iconSize));
    emit resized();
    QWidget::show();
}

void ButtonIcon::hide()
{
    if (shouldBeVisible() || isHidden()) {
        return;
    }

    emit resized();
    setFixedSize(1, qMax(minimumHeight(), m_iconSize));
    QWidget::hide();
}

bool ButtonIcon::shouldBeVisible() const
{
    return !m_buttonPixmap.isNull() || m_animationRunning;
}

void ButtonIcon::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const int size = m_iconSize;
    const int pixmapSize = qRound(size * data()->animationPixmap.devicePixelRatioF());

    // Center the pixmap in rect
    QRect r = rect();
    r.setX((r.width() - size) / 2);
    r.setY((r.height() - size) / 2);
    r.setWidth(size);
    r.setHeight(size);

    if (m_animationRunning) {
        p.drawPixmap(r, data()->animationPixmap, QRect(m_currentFrame * pixmapSize, 0, pixmapSize, pixmapSize));
    }  else if (!m_buttonPixmap.isNull()) {
        p.drawPixmap(r, m_buttonPixmap);
    }
}
