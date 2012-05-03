#include "nouvellesserveur.h"
#include "ui_nouvellesserveur.h"

NouvellesServeur::NouvellesServeur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NouvellesServeur)
{

    connect(&http, SIGNAL(readyRead(const QHttpResponseHeader &)), this,
               SLOT(readData(const QHttpResponseHeader &)));

    ui->setupUi(this);
    //Lien du signal RSS
    QUrl url("http://affaires.lapresse.ca/rss/2343.xml");

    //Connection au signal RSS
    http.setHost(url.host());
    connectionId = http.get(url.path());

}

NouvellesServeur::~NouvellesServeur()
{
    delete ui;
}

void NouvellesServeur::readData(const QHttpResponseHeader &resp)
 {
    //Lis le contenu du signal RSS
     if (resp.statusCode() != 200)
         http.abort();
     else {
         xml.addData(http.readAll());
         parseXml();
     }

 }
//Addition et affichage dans l'arbre des nouvelles
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
     //Ouvre le premier élément du QTreeWidget
     ui->TW->expandItem(ui->TW->itemAt(0,0));
     //Affiche la première nouvelle
     ui->WV->load(QUrl(ui->TW->itemAt(100,25)->text(2)));
     //Redimensionne les 2 premières colonnes
     ui->TW->resizeColumnToContents(0);
     ui->TW->resizeColumnToContents(1);
 }
//Lorsqu'une nouvelle est sélectionnée elle est affichée
void NouvellesServeur::on_TW_itemActivated(QTreeWidgetItem *item)
{
    ui->WV->load(QUrl(item->text(2)));
    ui->WV->show();
}


