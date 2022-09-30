#pragma once

#include <QMenu>
#include <string>
#include <QToolButton>
#include "ribbon.h"


using std::string;

struct SoundsButtons
{
    //QToolButton *load;
    //QToolButton *save;

    QToolButton *addNew;
};



class SoundboardRibbon : public QWidget
{
        Q_OBJECT
    public:
        SoundboardRibbon(Ribbon* ribbonWidget);
        ~SoundboardRibbon();

        static SoundsButtons getSoundButtons();


        static void selectTab(int tab);

    signals:
        void ribbonTabChanged(int index);
    private slots:
        void onRibbonTabChanged(int index);
    private:
        template<typename T>
        T *buttonFactory(const string &text, const string &toolTip,const string &iconName,
                                   bool enabled,const string &tab,const string &group);


        void buildButtons();
        void buildSoundButtons();

        static SoundboardRibbon *m_instance;

        Ribbon *m_ribbon;
        static const string m_externIconsPath;
        static const string m_externIconsExtention;
        static const string m_qIconBasePath;




        SoundsButtons m_soundButtons;
};

