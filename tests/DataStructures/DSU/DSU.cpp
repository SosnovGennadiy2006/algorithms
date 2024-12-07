#include <algorithms/DataStructures/DSU/DSU.h>

#include <gtest/gtest.h>

using namespace algorithms::data_structures;

TEST(DSU_test, test1) {
    DSU dsu;
    dsu.insert();
    dsu.insert();
    EXPECT_EQ(dsu.size(), 2);
    EXPECT_EQ(dsu.components(), 2);
    dsu.merge(0, 1);
    EXPECT_EQ(dsu.components(), 1);
    EXPECT_EQ(dsu.subsetSize(0), 2);
    EXPECT_EQ(dsu.subsetSize(1), 2);
    EXPECT_EQ(dsu.isSame(0, 1), true);
    dsu.insert();
    EXPECT_EQ(dsu.isSame(0, 2), false);
    EXPECT_EQ(dsu.size(), 3);
    EXPECT_EQ(dsu.components(), 2);
}