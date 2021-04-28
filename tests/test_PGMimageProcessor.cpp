#include "PGMimageProcessor.h"
#include "catch.hpp"

TEST_CASE("PGMimageProcessor Big 6 Unit Tests") {
	using namespace WNGJIA001;
	SECTION( "Default Constructor" ) {
		PGMimageProcessor ip_dc = PGMimageProcessor();
		REQUIRE(ip_dc.getWidth() == 0);
		REQUIRE(ip_dc.getHeight() == 0);
		REQUIRE(ip_dc.getComponentCount() == 0);
	}

	SECTION( "Custom Constructor" ) {
		PGMimageProcessor ip_cc = PGMimageProcessor("chess.pgm");
		REQUIRE(ip_cc.getWidth() == 609);
		REQUIRE(ip_cc.getHeight() == 252);
		REQUIRE(ip_cc.getComponentCount() == 0);
	}

	SECTION( "Copy Constructor" ) {
		PGMimageProcessor ip_cc1 = PGMimageProcessor("chess.pgm");
		unsigned char threshold = 200;
		int min = 3;
		ip_cc1.extractComponents(threshold, min);
        REQUIRE(ip_cc1.getWidth() == 609);
		REQUIRE(ip_cc1.getHeight() == 252);
		REQUIRE(ip_cc1.getComponentCount() == 6);

        PGMimageProcessor ip_cc2(ip_cc1);
		REQUIRE(ip_cc2.getWidth() == ip_cc1.getWidth());
		REQUIRE(ip_cc2.getHeight() == ip_cc1.getHeight());
		REQUIRE(ip_cc2.getComponentCount() == ip_cc1.getComponentCount());
	}

    SECTION( "Move Constructor" ) {
		PGMimageProcessor ip_mc1 = PGMimageProcessor("chess.pgm");
		unsigned char threshold = 200;
		int min = 3;
		ip_mc1.extractComponents(threshold, min);
        REQUIRE(ip_mc1.getWidth() == 609);
		REQUIRE(ip_mc1.getHeight() == 252);
		REQUIRE(ip_mc1.getComponentCount() == 6);

        PGMimageProcessor ip_mc2 = std::move(ip_mc1);
		REQUIRE(ip_mc2.getWidth() == 609);
		REQUIRE(ip_mc2.getHeight() == 252);
		REQUIRE(ip_mc2.getComponentCount() == 6);
		REQUIRE(ip_mc1.getComponentCount() == 0);
	}

    SECTION( "Copy Assignment Operator" ) {
		PGMimageProcessor ip_ca1 = PGMimageProcessor("chess.pgm");
		unsigned char threshold = 200;
		int min = 3;
		ip_ca1.extractComponents(threshold, min);
        PGMimageProcessor ip_ca2;
        ip_ca2 = ip_ca1;

        REQUIRE(ip_ca2.getWidth() == ip_ca1.getWidth());
		REQUIRE(ip_ca2.getHeight() == ip_ca1.getHeight());
		REQUIRE(ip_ca2.getComponentCount() == ip_ca1.getComponentCount());
	}

    SECTION( "Move Assignment Operator" ) {
		PGMimageProcessor ip_ma1 = PGMimageProcessor("chess.pgm");
		unsigned char threshold = 200;
		int min = 3;
		ip_ma1.extractComponents(threshold, min);
        PGMimageProcessor ip_ma2;
        ip_ma2 = std::move(ip_ma1);

        REQUIRE(ip_ma2.getWidth() == 609);
		REQUIRE(ip_ma2.getHeight() == 252);
		REQUIRE(ip_ma2.getComponentCount() != ip_ma1.getComponentCount());
		REQUIRE(ip_ma2.getComponentCount() == 6);
		REQUIRE(ip_ma1.getComponentCount() == 0);
	}
}

TEST_CASE("Component Extraction and Filtering Unit Tests") {
	using namespace WNGJIA001;
	PGMimageProcessor ip1 = PGMimageProcessor("chess.pgm");
	unsigned char threshold = 200;
	int min = 5000;
	int max = 7000;
	ip1.extractComponents(threshold, min);
	REQUIRE(ip1.getComponentCount() == 5);
	REQUIRE(ip1.getSmallestSize() == 5675);
	REQUIRE(ip1.getLargestSize() == 7901);

	ip1.filterComponentsBySize(min, max);
	REQUIRE(ip1.getComponentCount() == 2);
	REQUIRE(ip1.getSmallestSize() == 5675);
	REQUIRE(ip1.getLargestSize() == 6440);
}