/***************************************************************************
                                  main.cpp
                             -------------------
    update               : 2014 - 01 - 12
    copyright            : (C) 2013 by Pramita Winata
    email                : pramita.winata@gmail.com
 *                                                                         *
 *   Description:
 *   This project is done as part of Software Engineering course.
 *   The aim of this project is to show basic Laplace specral representation
 *                                                                          *
 ***************************************************************************/

#include <QApplication>
#include <iostream>
#include "mainwindow.h"

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainwindow;
    mainwindow.show();
    mainwindow.setWindowTitle("Spectral Mesh Representation");
    mainwindow.setWindowIcon(QIcon("E:/VIBOT.jpg"));
    return a.exec();
}
