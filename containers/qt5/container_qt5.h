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

#ifndef CONTAINER_QT5_H
#define CONTAINER_QT5_H

#include "../../include/litehtml.h"
#include <QWidget>

/**
 * @todo write docs
 */
class container_qt5 : public litehtml::document_container, public QWidget
{
private:
    std::shared_ptr< litehtml::document > _doc;

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

public:
    /**
     * Default constructor
     */
    container_qt5(QWidget *parent = nullptr);

    /**
     * Destructor
     */
    ~container_qt5();

    void set_document(std::shared_ptr<litehtml::document> doc);
    
    /**
     * @todo write docs
     *
     * @param language TODO
     * @param culture TODO
     * @return TODO
     */
    virtual void get_language(litehtml::tstring& language, litehtml::tstring& culture) const override;

    /**
     * @todo write docs
     *
     * @param media TODO
     * @return TODO
     */
    virtual void get_media_features(litehtml::media_features& media) const override;

    /**
     * @todo write docs
     *
     * @param tag_name TODO
     * @param attributes TODO
     * @param doc TODO
     * @return TODO
     */
    virtual std::shared_ptr< litehtml::element > create_element(const litehtml::tchar_t* tag_name, const litehtml::string_map& attributes, const std::shared_ptr< litehtml::document >& doc) override;

    /**
     * @todo write docs
     *
     * @param client TODO
     * @return TODO
     */
    virtual void get_client_rect(litehtml::position& client) const override;

    /**
     * @todo write docs
     *
     * @return TODO
     */
    virtual void del_clip() override;

    /**
     * @todo write docs
     *
     * @param pos TODO
     * @param bdr_radius TODO
     * @param valid_x TODO
     * @param valid_y TODO
     * @return TODO
     */
    virtual void set_clip(const litehtml::position& pos, const litehtml::border_radiuses& bdr_radius, bool valid_x, bool valid_y) override;

    /**
     * @todo write docs
     *
     * @param text TODO
     * @param url TODO
     * @param baseurl TODO
     * @return TODO
     */
    virtual void import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl) override;

    /**
     * @todo write docs
     *
     * @param text TODO
     * @param tt TODO
     * @return TODO
     */
    virtual void transform_text(litehtml::tstring& text, litehtml::text_transform tt) override;

    /**
     * @todo write docs
     *
     * @param cursor TODO
     * @return TODO
     */
    virtual void set_cursor(const litehtml::tchar_t* cursor) override;

    /**
     * @todo write docs
     *
     * @param url TODO
     * @param el TODO
     * @return TODO
     */
    virtual void on_anchor_click(const litehtml::tchar_t* url, const litehtml::element::ptr& el) override;

    /**
     * @todo write docs
     *
     * @param doc TODO
     * @param el TODO
     * @return TODO
     */
    virtual void link(const std::shared_ptr< litehtml::document >& doc, const litehtml::element::ptr& el) override;

    /**
     * @todo write docs
     *
     * @param base_url TODO
     * @return TODO
     */
    virtual void set_base_url(const litehtml::tchar_t* base_url) override;

    /**
     * @todo write docs
     *
     * @param caption TODO
     * @return TODO
     */
    virtual void set_caption(const litehtml::tchar_t* caption) override;

    /**
     * @todo write docs
     *
     * @param hdc TODO
     * @param borders TODO
     * @param draw_pos TODO
     * @param root TODO
     * @return TODO
     */
    virtual void draw_borders(litehtml::uint_ptr hdc, const litehtml::borders& borders, const litehtml::position& draw_pos, bool root) override;

    /**
     * @todo write docs
     *
     * @param hdc TODO
     * @param bg TODO
     * @return TODO
     */
    virtual void draw_background(litehtml::uint_ptr hdc, const litehtml::background_paint& bg) override;

    /**
     * @todo write docs
     *
     * @param src TODO
     * @param baseurl TODO
     * @param sz TODO
     * @return TODO
     */
    virtual void get_image_size(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, litehtml::size& sz) override;

    /**
     * @todo write docs
     *
     * @param src TODO
     * @param baseurl TODO
     * @param redraw_on_ready TODO
     * @return TODO
     */
    virtual void load_image(const litehtml::tchar_t* src, const litehtml::tchar_t* baseurl, bool redraw_on_ready) override;

    /**
     * @todo write docs
     *
     * @param hdc TODO
     * @param marker TODO
     * @return TODO
     */
    virtual void draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker) override;

    /**
     * @todo write docs
     *
     * @return TODO
     */
    virtual const litehtml::tchar_t* get_default_font_name() const override;

    /**
     * @todo write docs
     *
     * @return TODO
     */
    virtual int get_default_font_size() const override;

    /**
     * @todo write docs
     *
     * @param pt TODO
     * @return TODO
     */
    virtual int pt_to_px(int pt) override;

    /**
     * @todo write docs
     *
     * @param hdc TODO
     * @param text TODO
     * @param hFont TODO
     * @param color TODO
     * @param pos TODO
     * @return TODO
     */
    virtual void draw_text(litehtml::uint_ptr hdc, const litehtml::tchar_t* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos) override;

    /**
     * @todo write docs
     *
     * @param text TODO
     * @param hFont TODO
     * @return TODO
     */
    virtual int text_width(const litehtml::tchar_t* text, litehtml::uint_ptr hFont) override;

    /**
     * @todo write docs
     *
     * @param hFont TODO
     * @return TODO
     */
    virtual void delete_font(litehtml::uint_ptr hFont) override;

    /**
     * @todo write docs
     *
     * @param faceName TODO
     * @param size TODO
     * @param weight TODO
     * @param italic TODO
     * @param decoration TODO
     * @param fm TODO
     * @return TODO
     */
    virtual litehtml::uint_ptr create_font(const litehtml::tchar_t* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm) override;

};

#endif // CONTAINER_QT5_H
