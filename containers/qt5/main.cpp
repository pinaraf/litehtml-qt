#include <QApplication>
#include "container_qt5.h"
#include "context.h"

int main (int argc, char **argv) {
    QApplication app(argc, argv);
    
    litehtml::context ctxt;
    ctxt.load_master_stylesheet("/home/pierre/projects/litehtml/include/master.css");
    
    container_qt5 c;
    auto doc = litehtml::document::createFromUTF8("<html><body><p>Hello world</p></body></html>", &c, &ctxt);
    doc->render(120);
    
    return app.exec();
}
