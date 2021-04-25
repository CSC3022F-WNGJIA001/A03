#include "ConnectedComponent.h"
#include "catch.hpp"

TEST_CASE("ConnectedComponent \"Big 6\" Unit Tests") {
    using namespace WNGJIA001;
	SECTION( "Default Constructor" ) {
		ConnectedComponent cc_dc = ConnectedComponent();

        REQUIRE(cc_dc.getID() == 0);
		REQUIRE(cc_dc.getSize() == 0);
        REQUIRE(cc_dc.emptyComponent() == 0);
	}
	SECTION( "Custom Constructor" ) {
        int random_id = 3;
		ConnectedComponent cc_cc = ConnectedComponent(3);

        REQUIRE(cc_cc.getID() == random_id);
		REQUIRE(cc_cc.getSize() == 0);
        REQUIRE(cc_cc.emptyComponent() == 0);
	}
	SECTION( "Copy Constructor" ) {
		ConnectedComponent cc_cc1 = ConnectedComponent(1);
        cc_cc1.addPixel(2);
        REQUIRE(cc_cc1.getID() == 1);
        REQUIRE(cc_cc1.getSize() == 1);
        ConnectedComponent cc_cc2 = cc_cc1;

        REQUIRE(cc_cc2.getID() == cc_cc1.getID());
        REQUIRE(&cc_cc2.getIDr() != &cc_cc1.getIDr());
		REQUIRE(cc_cc2.getSize() == cc_cc1.getSize());
        REQUIRE(cc_cc2.getSize() == 1);
        REQUIRE(cc_cc2.emptyComponent() == cc_cc1.emptyComponent());
        REQUIRE(cc_cc2.getSize() == cc_cc2.emptyComponent());
	}
    SECTION( "Move Constructor" ) {
		ConnectedComponent cc_mc1 = ConnectedComponent(1);
        cc_mc1.addPixel(2);
        cc_mc1.addPixel(3);
        REQUIRE(cc_mc1.getID() == 1);
        REQUIRE(cc_mc1.getSize() == 2);
        ConnectedComponent cc_mc2 = std::move(cc_mc1);

        REQUIRE(cc_mc1.getID() == 0);
        REQUIRE(cc_mc2.getID() == 1);
        REQUIRE(&cc_mc2.getIDr() != &cc_mc1.getIDr());
		REQUIRE(cc_mc2.getSize() != cc_mc1.getSize());
        REQUIRE(cc_mc1.getSize() == 0);
        REQUIRE(cc_mc2.getSize() == 2);
        REQUIRE(cc_mc2.getSize() == cc_mc2.emptyComponent());
        REQUIRE(cc_mc2.getSize() != cc_mc1.emptyComponent());
        REQUIRE(cc_mc2.emptyComponent() == 2);
        REQUIRE(cc_mc1.emptyComponent() == 0);
	}
    SECTION( "Copy Assignment Operator" ) {
		ConnectedComponent cc_ca1 = ConnectedComponent(1);
        cc_ca1.addPixel(2);
        cc_ca1.addPixel(3);
        ConnectedComponent cc_ca2;
        cc_ca2 = cc_ca1;

        REQUIRE(cc_ca2.getID() == cc_ca1.getID());
        REQUIRE(&cc_ca2.getIDr() != &cc_ca1.getIDr());
		REQUIRE(cc_ca2.getSize() == cc_ca1.getSize());
        REQUIRE(cc_ca2.getSize() == 2);
        REQUIRE(cc_ca2.emptyComponent() == cc_ca1.emptyComponent());
        REQUIRE(cc_ca2.getSize() == cc_ca2.emptyComponent());
	}
    SECTION( "Move Assignment Operator" ) {
		ConnectedComponent cc_ma1 = ConnectedComponent(1);
        cc_ma1.addPixel(2);
        cc_ma1.addPixel(3);
        ConnectedComponent cc_ma2;
        cc_ma2 = std::move(cc_ma1);

        REQUIRE(cc_ma1.getID() == 0);
        REQUIRE(cc_ma2.getID() == 1);
        REQUIRE(&cc_ma2.getIDr() != &cc_ma1.getIDr());
		REQUIRE(cc_ma2.getSize() != cc_ma1.getSize());
        REQUIRE(cc_ma1.getSize() == 0);
        REQUIRE(cc_ma2.getSize() == 2);
        REQUIRE(cc_ma2.getSize() == cc_ma2.emptyComponent());
        REQUIRE(cc_ma2.getSize() != cc_ma1.emptyComponent());
        REQUIRE(cc_ma2.emptyComponent() == 2);
        REQUIRE(cc_ma1.emptyComponent() == 0);
	}
}