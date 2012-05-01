#include "nouvellesserveur.h"
#include "ui_nouvellesserveur.h"

NouvellesServeur::NouvellesServeur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NouvellesServeur)
{
    connect(&http, SIGNAL(readyRead(const QHttpResponseHeader &)), this,
               SLOT(readData(const QHttpResponseHeader &)));

    ui->setupUi(this);

    //ui->TW->setColumnHidden(1, true);
    //ui->TW->setColumnHidden(2, true);
    QUrl url("http://affaires.lapresse.ca/rss/2343.xml");


    http.setHost(url.host());
    connectionId = http.get(url.path());


    //ui->WV->load(QUrl(url));
    //ui->WV->show();

}

NouvellesServeur::~NouvellesServeur()
{
    delete ui;
}

void NouvellesServeur::readData(const QHttpResponseHeader &resp)
 {
     if (resp.statusCode() != 200)
         http.abort();
     else {
         xml.addData(http.readAll());
         parseXml();
     }

 }

void NouvellesServeur::parseXml()
 {

     while (!xml.atEnd()) {
         xml.readNext();
         if (xml.isStartElement()) {

             if (xml.name() == "item"){

                 if (titleString!=""){
                    feed = new QTreeWidgetItem;
                    feed->setText(0, titleString);
                    feed->setText(2, linkString);
                    ui->TW->addTopLevelItem(feed);

                 }

                 linkString.clear();
                 titleString.clear();
                 dateString.clear();
             }

             currentTag = xml.name().toString();
         } else if (xml.isEndElement()) {
              if (xml.name() == "item") {

                 QTreeWidgetItem *item = new QTreeWidgetItem(feed);
                 item->setText(0, titleString);
                 item->setText(1, dateString);
                 item->setText(2, linkString);
                 ui->TW->addTopLevelItem(item);

                 titleString.clear();
                 linkString.clear();
                 dateString.clear();
             }

         } else if (xml.isCharacters() && !xml.isWhitespace()) {
             if (currentTag == "title")
                 titleString += xml.text().toString();
             else if (currentTag == "link")
                 linkString += xml.text().toString();
             else if (currentTag == "pubDate")
                 dateString += xml.text().toString();
         }
     }
     if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {
         qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
         http.abort();
     }
 }

/*void NouvellesServeur::itemActivated(QTreeWidgetItem * item)
{
    ui->WV->load(QUrl(item->text(2)));
    ui->WV->show();

}*/

void NouvellesServeur::on_TW_itemActivated(QTreeWidgetItem *item)
{
    ui->WV->load(QUrl(item->text(2)));
    ui->WV->show();
}
