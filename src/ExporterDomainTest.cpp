//
// Created by sergio on 03/05/17.
//

#include "ExporterDomainTest.h"

TEST_F(ExporterDomainTest, ProperlyInitialised) {
    ASSERT_TRUE(exp->properlyInitialised());
}


TEST_F(ExporterDomainTest, Write) {
    ASSERT_FALSE(exp->isDocumentStarted());

    exp->write(dummy_str, dummy);

    ASSERT_TRUE(exp->isDocumentStarted());
}

TEST_F(ExporterDomainTest, Finish) {
    ASSERT_FALSE(exp->isDocumentStarted());
    ASSERT_DEATH(exp->finish(dummy), "Document was niet aangemaakt voor de aanroep van finish.");

    exp->write(dummy_str, dummy);

    ASSERT_TRUE(exp->isDocumentStarted());

    exp->finish(dummy);

    ASSERT_TRUE(exp->isDocumentStarted());
}
