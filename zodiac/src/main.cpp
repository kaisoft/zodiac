#include <QApplication>
#include <QFile>
#include <QDir>
//#include <QTextCodec>
#include <QTranslator>
#include "mainwindow.h"

void loadTranslations(QApplication* a, QString lang)
 {
  QDir dir("i18n");
  foreach (QString s, dir.entryList(QStringList("*" + lang + ".qm")))
   {
    QTranslator* t = new QTranslator;
    qDebug() << "load translation file" << s << ":"
             << (t->load(dir.absolutePath() + '/' + s) && a->installTranslator(t) ? "success" : "failed");
   }
 }

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Zodiac");
    a.setApplicationVersion("v0.6.2 (build 2014-03-24)");

    //QTextCodec* codec = QTextCodec::codecForName ( "CP1251" );
    //QTextCodec::setCodecForCStrings ( codec );
    //QTextCodec::setCodecForTr ( codec );
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("CP1251"));

    QDir::setCurrent(a.applicationDirPath());
    QString lang = "";
    if (!a.arguments().contains("nolocale"))
     {
      if (QLocale::system().name().contains("ru", Qt::CaseInsensitive))
       {
        loadTranslations(&a, "ru");
        lang = "ru";
       }
      else
        loadTranslations(&a, "en");
     }

    A::load(lang);
    MainWindow w;

    QFile cssfile ( "style/style.css" );
    cssfile.open  ( QIODevice::ReadOnly | QIODevice::Text );
    w.setStyleSheet  ( cssfile.readAll() );

    w.show();
    return a.exec();
}
