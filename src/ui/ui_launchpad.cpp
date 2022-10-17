#include "ui_launchpad.h"
#include "ui_ui_launchpad.h"

UI_Launchpad::UI_Launchpad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UI_Launchpad)
{
    ui->setupUi(this);
    setButtonSize(50);
}

UI_Launchpad::~UI_Launchpad()
{
    delete ui;
}


void UI_Launchpad::setButtonSize(unsigned int bs)
{
    buttonSize=bs;
    for(int x=0;x<buttonArray.size();x++)
    {
        for(int y=0;y<buttonArray[x].size();y++)
        {
            buttonArray[x][y]->setMinimumSize(buttonSize,buttonSize);
        }
    }
}

void UI_Launchpad::on_bottomAddButton_clicked()
{
    /*
    chliiZumUsprobiere = new QPushButton(this);
    QGridLayout *layout = dynamic_cast<QGridLayout*>  (ui->launchpadGridFrame->layout());
    if(layout)
        layout->addWidget(chliiZumUsprobiere,1,1);
*/



    /*
    if (buttonCount>0)
    {
        buttonArray[0][0]
    }
    */

    if(buttonArray.size()==0)
    {
        buttonArray.push_back(std::vector<QPushButton*>());
    }
    unsigned int buttonCount = buttonArray.size();
    QGridLayout *layout = dynamic_cast<QGridLayout*>  (ui->launchpadGridFrame->layout());
    if(layout)
    {
        for (unsigned int x=0;x<buttonCount;x++)
        {
            QPushButton *tempButton = new QPushButton(this);
            tempButton->setMinimumSize(buttonSize,buttonSize);

                layout->addWidget(tempButton ,buttonArray[x].size(),x);
            buttonArray[x].push_back(tempButton);
        }
    }








}


void UI_Launchpad::on_topAddButton_clicked()
{
    unsigned int buttonCount = 1;
    if(buttonArray.size()>0)
    {
        buttonCount = buttonArray[0].size();
    }

    QGridLayout *layout = dynamic_cast<QGridLayout*>  (ui->launchpadGridFrame->layout());
    if(layout)
    {
        buttonArray.push_back(std::vector<QPushButton*>());
        unsigned int x = buttonArray.size()-1;
        for (unsigned int y=0;y<buttonCount;y++)
        {
            QPushButton *tempButton = new QPushButton(this);
            tempButton->setMinimumSize(buttonSize,buttonSize);
            layout->addWidget(tempButton ,y,x);
            buttonArray[x].push_back(tempButton);
        }
    }
}

