#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opengl_test_widget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    opengl_test_widget_t * glwidget;
};

#endif // MAINWINDOW_H
