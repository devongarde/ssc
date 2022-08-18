COMMENT =	static site checker, an opinionated website nitpicker
DISTNAME =	ssc-v0.1.0
CATEGORIES =	www
HOMEPAGE =	https://ssc.lu/
MAINTAINER =	Dylan Harris <mail@dylanharris.org>
PERMIT_PACKAGE =	Yes
MASTER_SITES =		https://ssc.lu/src/
EXTRACT_SUFX =		.tgz
COMPILER =		base-clang ports-gcc
MODULES =	devel/cmake \
		lang/clang
LIB_DEPENDS =	devel/boost \
		devel/microsoft-gsl \
		textproc/icu4c \
		textproc/hunspell
RUN_DEPENDS =	net/curl
CONFIGURE_STYLE =	cmake
WRKBUILD =		${WRKSRC}/recipe/tea
WRKCONF =		${WRKSRC}/recipe/tea

.include <bsd.port.mk>
