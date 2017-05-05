//
// Created by sergio on 03/05/17.
//

#include "StationDomainTest.h"

TEST_F(StationDomainTest, ProperlyInitialised) {
    ASSERT_TRUE(halte.properlyInitialised());
    ASSERT_TRUE(metrostation.properlyInitialised());
}

TEST_F(StationDomainTest, IsHalte) {
    ASSERT_TRUE(halte.isHalte());
    ASSERT_FALSE(metrostation.isHalte());
}


TEST_F(StationDomainTest, IsMetrostation) {
    ASSERT_TRUE(metrostation. isMetrostation());
    ASSERT_FALSE(halte.isMetrostation());
}


TEST_F(StationDomainTest, SpoorBezet) {
    ASSERT_DEATH(halte.spoorBezet(spoor), "Station bevat het gegeven spoor niet bij aanroep van spoorBezet.");
    ASSERT_DEATH(metrostation.spoorBezet(spoor),
                 "Station bevat het gegeven spoor niet bij aanroep van spoorBezet.");
}

TEST_F(StationDomainTest, bezetSpoor) {
    halte.bezetSpoor(spoor, false);
    ASSERT_FALSE(halte.spoorBezet(spoor));
    halte.bezetSpoor(spoor, true);
    ASSERT_TRUE(halte.spoorBezet(spoor));

    metrostation.bezetSpoor(spoor, false);
    ASSERT_FALSE(metrostation.spoorBezet(spoor));
    metrostation.bezetSpoor(spoor, true);
    ASSERT_TRUE(metrostation.spoorBezet(spoor));
}