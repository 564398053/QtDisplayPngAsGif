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
#ifndef BUTTON_ICON_H
#define BUTTON_ICON_H

#include <QWidget>
#include <QImage>
#include <QIcon>

class QTimer;


class ButtonIcon : public QWidget
{
    Q_OBJECT

public:
    struct Data {
        int framesCount = 1;
        int animationInterval = 50;
        QPixmap animationPixmap;
    };
    explicit ButtonIcon(QWidget* parent = 0);

    void updateIcon();

    void setIcon(const QString& url);
    void setLoadingPng(const QString& url, int width, int height);

private:
    Data *data();

signals:
    void resized();

public slots:
    void showLoadingAnimation();
    void hideLoadingAnimation();

private slots:
    void updateAnimationFrame();

private:
    void show();
    void hide();
    bool shouldBeVisible() const;

    void paintEvent(QPaintEvent* event) override;

    QIcon m_icon;
    QTimer* m_updateTimer;
    QTimer* m_hideTimer;
    QPixmap m_buttonPixmap;
    int m_currentFrame;
    bool m_animationRunning;

    Data* m_data;

    int m_iconSize = 16;
};

#endif // BUTTON_ICON_H
