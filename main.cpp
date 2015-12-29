#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QTranslator>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("MD5Checker"); //TODO: better name.
    QApplication::setApplicationVersion("♪ ora con una icona"); //TODO: to change at first release.
    QApplication::setOrganizationName("D-25");
    QApplication::setOrganizationDomain("http://d-25.net");
    QApplication::setWindowIcon(QIcon(":/icons/ico_windows")); //TODO: temporary icon?
                                                               //TODO: what about Mac OSX icon?

    /*
     * Load a new language.
     * To make it happen, the language inside the Resource file MUST BE
     * named with an alias (for example: language_en_EN, language_fr_FR).
     * It automatically change during startup of the application based off the system settings.
     *
     * To make a new language, first edit the .pro file, then make a new language using the tools of QT Creator.
     *
     */

    QSettings settings("D-25" ,"MD5Checker");

    int languageSelected = settings.value("language", 0).toInt();
    QTranslator language;

    switch (languageSelected)
    {
        case 1: // Italian.
        {
            language.load(":/languages/language_it_IT.qm");
            a.installTranslator(&language);
            break;
        }

        case 2: // English.
        {
            language.load(":/languages/language_en_EN.qm");
            a.installTranslator(&language);
            break;
        }

        default: // Detected by system settings or unknown value.
        {
            language.load(":/languages/language_" + QLocale::system().name() + ".qm");
            a.installTranslator(&language);

            qDebug() << "Language loaded: qrc://languages/language_" + QLocale::system().name() + ".qm";
            break;
        }
    }

    MainWindow w;
    w.show();

    return a.exec();
}
