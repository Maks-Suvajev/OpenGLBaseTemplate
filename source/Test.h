#ifndef TEST_H
#define TEST_H

#include "MeshManager.h"
#include "MaterialManager.h"
#include "EntityManager.h"

// Vertices and test positions for cube
#include "Cube.h"

struct TestObjects
{
    gfx::MeshManager*       meshManager;
    gfx::MaterialManager*   materialManager;
    EntityManager*          entityManager;
};

class Test
{
    public:
        Test(TestObjects& testObjects);
        void initTestData();

    private:
        TestObjects testObjects;
        void initMeshTestData();
        void initMaterialtestData();
        void initEntityTestData();

};


#endif