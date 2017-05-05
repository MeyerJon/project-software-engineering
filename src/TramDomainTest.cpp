//
// Created by sergio on 03/05/17.
//

#include "TramDomainTest.h"

TEST_F(TramDomainTest, ProperlyInitialised) {
    ASSERT_TRUE(albatros.properlyInitialised());
    ASSERT_TRUE(pcc.properlyInitialised());
}

TEST_F(TramDomainTest, IsAlbatros) {
    ASSERT_TRUE(albatros.isAlbatros());
    ASSERT_FALSE(pcc.isAlbatros());
}

TEST_F(TramDomainTest, IsPCC) {
    ASSERT_FALSE(albatros.isPCC());
    ASSERT_TRUE(pcc.isPCC());
}

TEST_F(TramDomainTest, BevatPassagier) {
    ASSERT_TRUE(albatros.properlyInitialised());
    ASSERT_TRUE(passagier.properlyInitialised());
    ASSERT_FALSE(albatros.bevatPassagier(&passagier));

    ASSERT_TRUE(pcc.properlyInitialised());
    ASSERT_TRUE(passagier.properlyInitialised());
    ASSERT_FALSE(pcc.bevatPassagier(&passagier));
}

TEST_F(TramDomainTest, AddPassagier) {
    ASSERT_TRUE(albatros.properlyInitialised());
    ASSERT_TRUE(passagier.properlyInitialised());
    albatros.addPassagier(&passagier);
    ASSERT_TRUE(albatros.bevatPassagier(&passagier));

    ASSERT_TRUE(pcc.properlyInitialised());
    ASSERT_TRUE(passagier.properlyInitialised());
    pcc.addPassagier(&passagier);
    ASSERT_TRUE(pcc.bevatPassagier(&passagier));
}

TEST_F(TramDomainTest, RemovePassagier) {
    ASSERT_TRUE(albatros.properlyInitialised());
    ASSERT_TRUE(passagier.properlyInitialised());
    albatros.addPassagier(&passagier);
    ASSERT_TRUE(albatros.bevatPassagier(&passagier));
    albatros.removePassagier(&passagier);
    ASSERT_FALSE(albatros.bevatPassagier(&passagier));

    ASSERT_TRUE(pcc.properlyInitialised());
    ASSERT_TRUE(passagier.properlyInitialised());
    pcc.addPassagier(&passagier);
    ASSERT_TRUE(pcc.bevatPassagier(&passagier));
    pcc.removePassagier(&passagier);
    ASSERT_FALSE(pcc.bevatPassagier(&passagier));
}

TEST_F(TramDomainTest, VerplaatsTram) {
    ASSERT_TRUE(albatros.properlyInitialised());
    Exporter* exp = new Exporter();
    std::ostream dummy(0);
    albatros.verplaatsTram("dummy", exp, dummy);
    ASSERT_TRUE(albatros.getHuidigStation() == "dummy");

    ASSERT_TRUE(pcc.properlyInitialised());
    pcc.verplaatsTram("dummy", exp, dummy);
    ASSERT_TRUE(pcc.getHuidigStation() == "dummy");
    delete exp;
}

TEST_F(TramDomainTest, OpstappenAfstappenNormaal){
    Passagier pas1("a", "dummy", "dummy", 3);
    Passagier pas2("b", "dummy", "dummy", 6);
    Passagier pas3("c", "dummy", "dummy", 0);

    albatros.opstappen(&pas1);
    ASSERT_EQ(albatros.getBezettePlaatsen(), 3);
    ASSERT_TRUE(albatros.opstappen(&pas2));
    ASSERT_EQ(albatros.getBezettePlaatsen(), 9);
    ASSERT_TRUE(albatros.afstappen(&pas1));
    ASSERT_EQ(albatros.getBezettePlaatsen(), 6);
    ASSERT_TRUE(albatros.afstappen(&pas2));
    ASSERT_EQ(albatros.getBezettePlaatsen(), 0);
    ASSERT_TRUE(albatros.opstappen(&pas3));
    ASSERT_EQ(albatros.getBezettePlaatsen(), 0);

}

TEST_F(TramDomainTest, OpstappenAfstappenOverflow){
    int max = std::numeric_limits<int>::max();
    Passagier pas1("a", "dummy", "dummy", 101);
    Passagier pas2("b", "dummy", "dummy", 50);
    Passagier pas3("c", "dummy", "dummy", 51);
    Passagier pas4("a", "dummy", "dummy", max);

    // Meer op- en afstappen dan max
    albatros.opstappen(&pas1);
    ASSERT_FALSE(albatros.bevatPassagier(&pas1));
    albatros.opstappen(&pas2);
    ASSERT_TRUE(albatros.bevatPassagier(&pas2));
    albatros.opstappen(&pas3);
    ASSERT_FALSE(albatros.bevatPassagier(&pas3));
    albatros.opstappen(&pas4);
    ASSERT_FALSE(albatros.bevatPassagier(&pas4));
}
