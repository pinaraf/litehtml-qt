/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2019  Pierre <pinaraf@pinaraf.info>
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
 */

#include "container_qt5.h"
#include "types.h"
#include <QDebug>
#include <QFont>
#include <QFontMetrics>
#include <QPainter>
#include <QMouseEvent>
#include <QDesktopServices>


/**
 * Simple conversion functions
 */
static QRect getRect(const litehtml::position &position) {
    return QRect(position.x, position.y, position.width, position.height);
}

static QColor getColor(const litehtml::web_color &color) {
    return QColor(color.red, color.green, color.blue, color.alpha);
}


// Now for the real stuff

container_qt5::container_qt5(QWidget *parent)
    : litehtml::document_container(), QWidget(parent)
{
    setMouseTracking(true);
}

container_qt5::~container_qt5()
{

}

void container_qt5::set_document(std::shared_ptr< litehtml::document > doc)
{
    _doc = doc;
}

void container_qt5::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    qDebug() << __FUNCTION__ << width();
    _doc->render(width());
    _doc->draw(&painter, 0, 0, nullptr);
}

void container_qt5::mouseMoveEvent(QMouseEvent *event)
{
    litehtml::position::vector vec;
    if (_doc->on_mouse_over(event->x(), event->y(), event->x(), event->y(), vec))
        repaint();
}

void container_qt5::mousePressEvent(QMouseEvent *event)
{
    litehtml::position::vector vec;
    if (_doc->on_lbutton_down(event->x(), event->y(), event->x(), event->y(), vec))
        repaint();
}

void container_qt5::mouseReleaseEvent(QMouseEvent *event)
{
    litehtml::position::vector vec;
    if (_doc->on_lbutton_up(event->x(), event->y(), event->x(), event->y(), vec))
        repaint();
}

void container_qt5::get_language(litehtml::tstring& language, litehtml::tstring& culture) const
{
    qDebug() << "get_language";
}

void container_qt5::get_media_features(litehtml::media_features& media) const
{
    qDebug() << "get_media_features";
    media.width = width();
    media.height = height();
    media.device_width = width();
    media.device_height = height();
    media.type = litehtml::media_type_screen;
    
    qDebug() << "=> " << media.width << "x" << media.height;
}

std::shared_ptr< litehtml::element > container_qt5::create_element(const litehtml::tchar_t* tag_name, const litehtml::string_map& attributes, const std::shared_ptr< litehtml::document >& doc)
{
    qDebug() << __FUNCTION__ << " this one can be 0";
    return 0;
}

void container_qt5::get_client_rect(litehtml::position& client) const
{
    //qDebug() << "get_client_rect";
    // No scroll yet
    client.move_to(0, 0);
    client.width = width();
    client.height = height();
    //qDebug() << "==> " << client.width << "x" << client.height;
}

void container_qt5::del_clip()
{
    qDebug() << "del_clip";
}

void container_qt5::set_clip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius, bool valid_x, bool valid_y)
{
    qDebug() << "set_clip";
}

void container_qt5::import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl)
{
    qDebug() << "import_css";
}

void container_qt5::transform_text(litehtml::tstring& text, litehtml::text_transform tt)
{
    qDebug() << "transform_text";
}

void container_qt5::set_cursor(const litehtml::tchar_t* cursor_)
{
    QString cursor(cursor_);
    if (cursor == "auto")
        setCursor(Qt::IBeamCursor);
    else if (cursor == "pointer")
        setCursor(Qt::PointingHandCursor);
    else
        qDebug() << __FUNCTION__ << cursor;
}

void container_qt5::on_anchor_click(const litehtml::tchar_t* url, const litehtml::element::ptr& el)
{
    qDebug() << __FUNCTION__ << url;
    QDesktopServices::openUrl(QUrl(url));
}

void container_qt5::link(const std::shared_ptr< litehtml::document >& doc, const litehtml::element::ptr& el)
{
    qDebug() << __FUNCTION__;
}

void container_qt5::set_base_url(const litehtml::tchar_t* base_url)
{
    qDebug() << __FUNCTION__;
}

void container_qt5::set_caption(const litehtml::tchar_t* caption)
{
    qDebug() << __FUNCTION__;
}

static void setPenForBorder(QPainter *painter, const litehtml::border &border)
{
    QPen pen(painter->pen());
    pen.setWidth(border.width);
    pen.setColor(getColor(border.color));
    /*
    border_style_none,
    border_style_hidden,
    border_style_dotted,
    border_style_dashed,
    border_style_solid,
    border_style_double,
    border_style_groove,
    border_style_ridge,
    border_style_inset,
    border_style_outset
    */
    switch (border.style) {
        case litehtml::border_style_none:
        case litehtml::border_style_hidden: pen.setStyle(Qt::NoPen); break;
        case litehtml::border_style_dotted: pen.setStyle(Qt::DotLine); break;
        case litehtml::border_style_dashed: pen.setStyle(Qt::DashLine); break;
        default: pen.setStyle(Qt::SolidLine); break;
    }
    painter->setPen(pen);
}

void container_qt5::draw_borders(litehtml::uint_ptr hdc, const litehtml::borders& borders, const litehtml::position& draw_pos, bool root)
{
    //qDebug() << __FUNCTION__ << " for root = " << root;
    QPainter *painter = (QPainter *) hdc;
    painter->save();
    QRect area = getRect(draw_pos);
    if (root) {
        painter->setPen(Qt::NoPen);
        painter->fillRect(area, Qt::white);
    } else {
        if (borders.top.style != litehtml::border_style_none) {
            setPenForBorder(painter, borders.top);
            painter->drawLine(area.topLeft(), area.topRight());
        }
        if (borders.bottom.style != litehtml::border_style_none) {
            setPenForBorder(painter, borders.bottom);
            painter->drawLine(area.bottomLeft(), area.bottomRight());
        }
        if (borders.left.style != litehtml::border_style_none) {
            setPenForBorder(painter, borders.left);
            painter->drawLine(area.topLeft(), area.bottomLeft());
        }
        if (borders.right.style != litehtml::border_style_none) {
            setPenForBorder(painter, borders.right);
            painter->drawLine(area.topRight(), area.bottomRight());
        }
    }
    painter->restore();
}

void container_qt5::draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint& bg)
{
    qDebug() << __FUNCTION__;
}

void container_qt5::get_image_size(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, litehtml::size& sz)
{
    qDebug() << __FUNCTION__;
}

void container_qt5::load_image(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, bool redraw_on_ready)
{
    qDebug() << __FUNCTION__;
}

void container_qt5::draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker)
{
    qDebug() << __FUNCTION__;
    qDebug() << marker.marker_type << marker.pos.x << "x" << marker.pos.y << marker.pos.left() << marker.pos.right();
    qDebug() << marker.baseurl << QString::fromStdString(marker.image);
    QPainter *painter = (QPainter *) hdc;
    QRect position = getRect(marker.pos);
    QColor color = getColor(marker.color);
    painter->save();
    painter->setPen(color);
    switch (marker.marker_type) {
        case litehtml::list_style_type_none: break;
        case litehtml::list_style_type_circle: painter->drawEllipse(position); break;
        case litehtml::list_style_type_disc: painter->setBrush(color); painter->drawEllipse(position); break;
        case litehtml::list_style_type_square: painter->fillRect(position, getColor(marker.color)); break;
        // How to implement numeral markers ??
        default: break;
    }
    painter->restore();
}
/*
		list_style_type_none,
		list_style_type_circle,
		list_style_type_disc,
		list_style_type_square,
		list_style_type_armenian,
		list_style_type_cjk_ideographic,
		list_style_type_decimal,
		list_style_type_decimal_leading_zero,
		list_style_type_georgian,
		list_style_type_hebrew,
		list_style_type_hiragana,
		list_style_type_hiragana_iroha,
		list_style_type_katakana,
		list_style_type_katakana_iroha,
		list_style_type_lower_alpha,
		list_style_type_lower_greek,
		list_style_type_lower_latin,
		list_style_type_lower_roman,
		list_style_type_upper_alpha,
		list_style_type_upper_latin,
		list_style_type_upper_roman,
*/

const litehtml::tchar_t* container_qt5::get_default_font_name() const
{
    qDebug() << __FUNCTION__;
    return "Noto Sans";
}

int container_qt5::get_default_font_size() const
{
    qDebug() << __FUNCTION__;
    return 12;
}

int container_qt5::pt_to_px(int pt)
{
    qDebug() << __FUNCTION__;
}

void container_qt5::draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos)
{
    //qDebug() << __FUNCTION__;
    QPainter *painter = (QPainter *) hdc;
    QFont *font = (QFont *) hFont;
    painter->setFont(*font);
    painter->setPen(getColor(color));
    //painter->setBrush(QColor(color.red, color.green, color.blue, color.alpha));
    QFontMetrics metrics(*font);
    
    //qDebug() << "Paint " << text << " at " << pos.x << "x" << pos.y;
    painter->drawText(pos.x, pos.bottom() - metrics.descent(), text);
}

int container_qt5::text_width(const litehtml::tchar_t* text, litehtml::uint_ptr hFont)
{
    qDebug() << __FUNCTION__;
    QFont *font = (QFont *) hFont;
    QFontMetrics metrics(*font);
    QString txt(text);
    qDebug() << "For" << txt << metrics.boundingRect(txt);
    if (txt == " ") {
        return metrics.boundingRect("x").width();
    }
    return metrics.boundingRect(txt).width();
}

void container_qt5::delete_font(litehtml::uint_ptr hFont)
{
    qDebug() << __FUNCTION__;
    QFont *font = (QFont *) hFont;
    delete(font);
}

litehtml::uint_ptr container_qt5::create_font(const litehtml::tchar_t* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm)
{
    //TODO: decoration
    qDebug() << __FUNCTION__ << " for " << faceName << size << weight;
    QFont *font = new QFont(faceName, size, weight, italic == litehtml::fontStyleItalic);
    font->setUnderline(decoration & litehtml::font_decoration_underline);
    font->setOverline(decoration & litehtml::font_decoration_overline);
    font->setStrikeOut(decoration & litehtml::font_decoration_linethrough);
    QFontMetrics metrics(*font);
    fm->height = metrics.ascent() + metrics.descent() + 2;
    fm->ascent = metrics.ascent();
    fm->descent = metrics.descent();
    fm->x_height = metrics.boundingRect("x").height();
    return font;
}
