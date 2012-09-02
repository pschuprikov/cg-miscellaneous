#ifndef OPENGL_TEST_WIDGET_H
#define OPENGL_TEST_WIDGET_H

#include <QGLWidget>

class opengl_test_widget_t : public QGLWidget
{
    Q_OBJECT
public:
    explicit opengl_test_widget_t(QWidget *parent = 0);
signals:
    
public slots:

protected:
    void paintGL();
    void initializeGL();
    
};

#endif // OPENGL_TEST_WIDGET_H
