#include "Test.h"

Test::Test(TestObjects& testInitObjects)
{
    testObjects.entityManager   = testInitObjects.entityManager;
    testObjects.materialManager = testInitObjects.materialManager;
    testObjects.meshManager     = testInitObjects.meshManager;
}

void Test::initTestData()
{
    initMeshTestData();
    initMaterialtestData();
    initEntityTestData();
}

void Test::initMeshTestData()
{

}

void Test::initMaterialtestData()
{

}

void Test::initEntityTestData()
{

}