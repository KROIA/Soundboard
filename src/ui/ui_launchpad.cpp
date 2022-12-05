#include "ui_launchpad.h"
#include "ui_ui_launchpad.h"

UI_Launchpad::UI_Launchpad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UI_Launchpad)
{
    ui->setupUi(this);
    setButtonSize(50);
    ui->bottomAddButton->setIcon(QIcon(":/icons/document-add.png"));
    ui->topAddButton->setIcon(QIcon(":/icons/document-add.png"));
    m_gridSizeX = 0;
    m_gridSizeY = 0;
}

UI_Launchpad::~UI_Launchpad()
{
    delete ui;
}


void UI_Launchpad::setButtonSize(unsigned int bs)
{
    buttonSize=bs;
    for(size_t x=0;x<buttonArray.size(); x++)
    {
        for(size_t y=0;y<buttonArray[x].size(); y++)
        {
            buttonArray[x][y]->setMinimumSize(buttonSize,buttonSize);
        }
    }
}
bool UI_Launchpad::addSound(Sound *sound, bool overwrite)
{
    if(!sound)
        return false;
    Coord buttonPos = sound->getButtonCoord();
    if(buttonPos.x < 0 || buttonPos.y < 0)
        return false;

    if(m_gridSizeX < (size_t)buttonPos.x)
        m_gridSizeX = (size_t)buttonPos.x;
    if(m_gridSizeY < (size_t)buttonPos.y)
        m_gridSizeY = (size_t)buttonPos.y;

    QGridLayout *layout = dynamic_cast<QGridLayout*>  (ui->launchpadGridFrame->layout());

    while(buttonArray.size() <= m_gridSizeX)
    {
        buttonArray.push_back(std::vector<QPushButton*>());
    }
    for(size_t x=0; x<buttonArray.size(); ++x)
    {
        while(buttonArray[x].size() <= m_gridSizeY)
        {
            buttonArray[x].push_back(nullptr);
        }

        for(size_t y=0; y<buttonArray[x].size(); ++y)
        {
            if((x != (size_t)buttonPos.x || y != (size_t)buttonPos.y) && !buttonArray[x][y])
            {
                LaunchpadButton *tempButton = createNewButton(Coord{.x=(int)x,.y=(int)y});
                layout->addWidget(tempButton , y, x);
                buttonArray[x][y] = tempButton;
            }
        }
    }


    if(layout)
    {
        if(buttonArray[buttonPos.x][buttonPos.y])
        {
            if(overwrite)
            {
                layout->removeWidget(buttonArray[buttonPos.x][buttonPos.y]);
                delete buttonArray[buttonPos.x][buttonPos.y];
                buttonArray[buttonPos.x][buttonPos.y] = nullptr;

            }
            else
                return false;
        }
        LaunchpadButton *tempButton = createNewButton(buttonPos);
        tempButton->setSound(sound);
        layout->addWidget(tempButton ,buttonPos.y, buttonPos.x);
        buttonArray[buttonPos.x][buttonPos.y] = tempButton;
    }
    return true;
}
bool UI_Launchpad::addSound(const std::vector<Sound *> &sounds, bool overwrite)
{
    bool success = true;
    for(size_t i=0; i<sounds.size(); ++i)
        success &= addSound(sounds[i], overwrite);
    return success;
}

void UI_Launchpad::on_bottomAddButton_clicked()
{
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
            LaunchpadButton *tempButton = createNewButton(Coord{(int)x,(int)buttonArray[x].size()});
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
            LaunchpadButton *tempButton = createNewButton(Coord{(int)x,(int)y});
            layout->addWidget(tempButton ,y,x);
            buttonArray[x].push_back(tempButton);
        }
    }
}
LaunchpadButton *UI_Launchpad::createNewButton(Coord pos)
{
    //QGridLayout *layout = dynamic_cast<QGridLayout*>  (ui->launchpadGridFrame->layout());
    LaunchpadButton *tempButton = new LaunchpadButton(this);
    tempButton->setArrayPos(pos);
    tempButton->setMinimumSize(buttonSize,buttonSize);
    //layout->addWidget(tempButton ,(unsigned int)pos.y, (unsigned int)pos.x);
    return tempButton;
}

