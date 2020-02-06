#include <QApplication>
#include <QFile>
#include "container_qt5.h"
// #include "context.h"
#include <QDebug>

int main (int argc, char **argv) {
    QApplication app(argc, argv);
    
    litehtml::context ctxt;
    QFile master_css_fh("/home/snoopy/projects/litehtml-qt/include/master.css");
    master_css_fh.open(QIODevice::ReadOnly);
    QByteArray master_css = master_css_fh.readAll();
    //ctxt.load_master_stylesheet("/home/pierre/projects/litehtml/include/master.css");
    qDebug() << master_css;
    ctxt.load_master_stylesheet(master_css.constData());
    
    container_qt5 c;
    //auto doc = litehtml::document::createFromUTF8("<html><body><ul><li>One</li><li>Zwei</li><li>Trois</li></ul></body></html>", &c, &ctxt);
    //auto doc = litehtml::document::createFromUTF8("<html><body><p>Line1.1 Line1.2<br />Line2</p><ul><li>One</li><li>Zwei</li><li>Trois</li></ul></body></html>", &c, &ctxt);
    auto doc = litehtml::document::createFromUTF8("<html><body><a href=\"http://linuxfr.org/\">DLFP</a></body></html>", &c, &ctxt);
    //auto doc = litehtml::document::createFromUTF8("<html><body><table><tr><th>H1</th><th>H2</th></tr><tr><td>C1.1</td><td>C1.2</td></tr><tr><td>C2.1</td><td>C2.2</td></tr></table></body></html>", &c, &ctxt);
    c.set_document(doc);

    c.show();

    return app.exec();
}
