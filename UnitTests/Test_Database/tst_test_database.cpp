#include <QtTest>

// add necessary includes here
#include "database.h"
#include "fruitBasket.h"

using std::string;

//DATABASE_USE_OBJECT(FruitBasket)

class Test_Database : public QObject
{
        Q_OBJECT

    public:
        Test_Database();
        ~Test_Database();

    private slots:
        void test_init();
        void test_addObject();
        void test_removeObject();

        void test_save();


    private:
        string m_jsonFile1;
        string m_jsonFile2;
        string m_jsonFile3;

        size_t m_objCount;

        Database *m_database;

        FruitBasket *m_giselasBasket;
        FruitBasket *m_petersBasket;
        FruitBasket *m_mariannesBasket;

        FruitBasket *m_ORGgiselasBasket;
        FruitBasket *m_ORGpetersBasket;
        FruitBasket *m_ORGmariannesBasket;
};

Test_Database::Test_Database()
{
    m_jsonFile1  = "m_jsonFile1.json";
    m_jsonFile2  = "m_jsonFile2.json";
    m_jsonFile3  = "m_jsonFile3.json";

    m_objCount = 10;

    m_database = nullptr;

    m_giselasBasket = new FruitBasket();
    m_petersBasket = new FruitBasket();
    m_mariannesBasket = new FruitBasket();

    m_ORGgiselasBasket = m_giselasBasket;
    m_ORGpetersBasket = m_petersBasket;
    m_ORGmariannesBasket = m_mariannesBasket;

    m_giselasBasket->m_owner = "Gisela";
    m_petersBasket->m_owner = "Peter";
    m_mariannesBasket->m_owner = "Marianne";

    Apple *apple = new Apple();
    apple->m_radius = 3;
    apple->m_color = "red2";
    m_giselasBasket->m_fruits.push_back(apple);
    m_giselasBasket->m_fruits.push_back(new Apple());

    m_petersBasket->m_fruits.push_back(new Apple());
    m_petersBasket->m_fruits.push_back(new PineApple());
    m_petersBasket->m_fruits.push_back(new PineApple());

    PineApple *pineApple = new PineApple();
    pineApple->m_radius = 10;
    pineApple->m_height = 10;
    pineApple->m_color = "orange";
    pineApple->m_name = "StrangePineApple";
    m_mariannesBasket->m_fruits.push_back(pineApple);

    pineApple = new PineApple();
    pineApple->m_radius = 6;
    pineApple->m_height = 1;
    pineApple->m_color = "blue";
    pineApple->m_name = "FlatPineApple";
    m_mariannesBasket->m_fruits.push_back(pineApple);
}

Test_Database::~Test_Database()
{
    delete m_database;
}

void Test_Database::test_init()
{
    m_database = new Database();
    m_database->defineSaveableObject<FruitBasket>();
    m_database->defineSaveableObject<Apple>();


    if(m_database->load(m_jsonFile1))
    {
        QVERIFY(m_database->getObjectCount() == 3);

        std::vector<FruitBasket*> baskets = m_database->getObjects<FruitBasket>();
        QVERIFY(baskets.size() == 3);
        for(size_t i=0; i<baskets.size(); ++i)
        {
            if(baskets[i]->m_owner == m_giselasBasket->m_owner)
            {
                m_giselasBasket = baskets[i];
                m_giselasBasket->print();
                m_ORGgiselasBasket->print();
                QVERIFY(m_giselasBasket->operator==(*m_ORGgiselasBasket));
            }else if(baskets[i]->m_owner == m_petersBasket->m_owner)
            {
                m_petersBasket = baskets[i];
                QVERIFY(m_petersBasket->operator==(*m_ORGpetersBasket));
            }else if(baskets[i]->m_owner == m_mariannesBasket->m_owner)
            {
                m_mariannesBasket = baskets[i];
                QVERIFY(m_mariannesBasket->operator==(*m_ORGmariannesBasket));
            }else
            {
                QFAIL(("Unbekannter Besitzer: "+baskets[i]->m_owner).c_str());
            }
        }
    }
    else
    {
        QVERIFY(m_database->getObjectCount() == 0);

        m_database->addObject(m_giselasBasket);
        m_database->addObject(m_petersBasket);
        m_database->addObject(m_mariannesBasket);
    }

    QVERIFY(m_database->getObjectCount() == 3);
}
void Test_Database::test_addObject()
{
    PineApple *pineApple = new PineApple();
    pineApple->m_height = rand()%10;
    pineApple->m_radius = rand()%10;
    pineApple->m_calories = rand()%100;
    pineApple->m_color = "Black";
    pineApple->m_name = "UnitTestPineapple";
    QVERIFY(m_database->addObject(pineApple) == false); // shuld be false, because we need to add the
    // PineApple as class to the database:
    m_database->defineSaveableObject<PineApple>();
    QVERIFY(m_database->addObject(pineApple) == true);

    QVERIFY(m_database->save(m_jsonFile2));

    // Create a new Database to load:
    Database newDatabase;
    QVERIFY(newDatabase.defineSaveableObject<FruitBasket>());
    QVERIFY(newDatabase.defineSaveableObject<Apple>());
    QVERIFY(newDatabase.defineSaveableObject<PineApple>());
    QVERIFY(newDatabase.load(m_jsonFile2));
    QCOMPARE(newDatabase.getObjectCount(), m_database->getObjectCount());

    std::vector<PineApple*> apples = newDatabase.getObjects<PineApple>();
    std::vector<FruitBasket*> baskets = newDatabase.getObjects<FruitBasket>();

    string id;
    QVERIFY(apples.size() == 1);
    QVERIFY(baskets.size() == m_database->getObjectCount<FruitBasket>());
    id = apples[0]->getID();

    PineApple *loaded = newDatabase.getObject<PineApple>(id);
    QVERIFY(loaded != nullptr);
    QVERIFY(loaded->operator==(*pineApple));

    QVERIFY(newDatabase.objectExists(loaded));
    QVERIFY(newDatabase.objectExists(loaded->getID()));
    QVERIFY(newDatabase.addObject(loaded) == false); // Shuld not add the already existing object
}
void Test_Database::test_removeObject()
{
    Database newDatabase;
    newDatabase.defineSaveableObject<FruitBasket>();
    newDatabase.defineSaveableObject<Apple>();
    newDatabase.defineSaveableObject<PineApple>();
    QVERIFY(newDatabase.load(m_jsonFile2));

    std::vector<PineApple*> apples = newDatabase.getObjects<PineApple>();
    QVERIFY(apples.size() == 1);
    string id = apples[0]->getID();

    PineApple *loaded = newDatabase.getObject<PineApple>(id);
    QVERIFY(loaded != nullptr);
    newDatabase.removeObject(loaded);
    QVERIFY(newDatabase.objectExists(loaded) == false);
    loaded = newDatabase.getObject<PineApple>(id);
    QVERIFY(loaded == nullptr);

    QVERIFY(newDatabase.objectExists(id) == false);

    QVERIFY(newDatabase.load(m_jsonFile2));
    QVERIFY(newDatabase.objectExists(loaded) == false);
    QVERIFY(newDatabase.objectExists(id) == true);
    loaded = newDatabase.getObject<PineApple>(id);
    QVERIFY(newDatabase.objectExists(loaded) == true);
    QVERIFY(newDatabase.objectExists(loaded->getID()) == true);
    QVERIFY(loaded != nullptr);
    PineApple *copy = loaded->clone();
    QVERIFY(loaded->operator==(*copy));

    newDatabase.removeObject(id);
    loaded = newDatabase.getObject<PineApple>(id);
    QVERIFY(loaded == nullptr);

    Database db;
    QVERIFY(db.defineSaveableObject<PineApple>());
    QVERIFY(db.addObject(copy));
    QVERIFY(db.save(m_jsonFile3));
    QVERIFY(db.getObjectCount() == 1);
    PineApple *pineApple = db.getObjects<PineApple>()[0];
    QVERIFY(pineApple != nullptr);
    delete pineApple;
    QVERIFY(db.getObjectCount() == 0);
}
void Test_Database::test_save()
{
    QVERIFY(m_database->save(m_jsonFile1));
}

QTEST_APPLESS_MAIN(Test_Database)

#include "tst_test_database.moc"
